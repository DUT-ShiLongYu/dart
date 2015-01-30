/*
 * Copyright (c) 2014-2015, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Michael X. Grey <mxgrey@gatech.edu>
 *
 * Georgia Tech Graphics Lab and Humanoid Robotics Lab
 *
 * Directed by Prof. C. Karen Liu and Prof. Mike Stilman
 * <karenliu@cc.gatech.edu> <mstilman@cc.gatech.edu>
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#include "dart/dynamics/Frame.h"
#include "dart/dynamics/Shape.h"
#include "dart/renderer/RenderInterface.h"
#include "dart/common/Console.h"

namespace dart {
namespace dynamics {

typedef std::set<Entity*> EntityPtrSet;
typedef std::set<Frame*> FramePtrSet;

//==============================================================================
Frame::Frame(Frame* _refFrame, const std::string &_name)
  : Entity(_refFrame, _name, false),
    mWorldTransform(Eigen::Isometry3d::Identity()),
    mVelocity(Eigen::Vector6d::Zero()),
    mAcceleration(Eigen::Vector6d::Zero()),
    mAmWorld(false)
{

}

//==============================================================================
Frame::~Frame()
{
  if(isWorld())
    return;

  changeParentFrame(NULL);

  // Inform all child entities that this Frame is disappearing by setting their
  // reference frames to the World frame.
  EntityPtrSet::iterator it=mChildEntities.begin(), end=mChildEntities.end();
  while( it != end )
    (*(it++))->changeParentFrame(Frame::World());
  // Note: When we instruct an Entity to change its parent Frame, it will erase
  // itself from this Frame's mChildEntities list. This would invalidate the
  // 'it' and clobber our attempt to iterate through the std::set if we applied
  // changeParentFrame(~) directly to the 'it' iterator. So instead we use the
  // post-increment operator to iterate 'it' forward and we apply
  // changeParentFrame(~) to the temporary iterator created by the
  // post-increment operator. Put simply: we increment 'it' forward once and
  // then apply changeParentFrame(~) to the pointer that 'it' held just before
  // it incremented.

  // Free the memory of the visualization shapes
  for(size_t i=0; i<mVizShapes.size(); ++i)
    delete mVizShapes[i];
  mVizShapes.clear();

  // The entity destructor takes care of informing the parent Frame that this
  // one is disappearing
}

//==============================================================================
Frame* Frame::World()
{
  static WorldFrame world;
  return &world;
}

//==============================================================================
const Eigen::Isometry3d& Frame::getWorldTransform() const
{
  if(mAmWorld)
    return mWorldTransform;

  if(mNeedTransformUpdate)
  {
    mWorldTransform = mParentFrame->getWorldTransform()*getRelativeTransform();
    mNeedTransformUpdate = false;
  }

  return mWorldTransform;
}

//==============================================================================
Eigen::Isometry3d Frame::getTransform(const Frame* _withRespectTo) const
{
  if(_withRespectTo->isWorld())
    return getWorldTransform();
  else if(_withRespectTo == mParentFrame)
    return getRelativeTransform();
  else if(_withRespectTo == this)
    return Eigen::Isometry3d::Identity();

  return _withRespectTo->getWorldTransform().inverse()*getWorldTransform();
}

//==============================================================================
const Eigen::Vector6d& Frame::getSpatialVelocity() const
{
  if(mAmWorld)
    return mVelocity;

  if(mNeedVelocityUpdate)
  {
    mVelocity = math::AdInvT(getRelativeTransform(),
                             getParentFrame()->getSpatialVelocity())
                + getRelativeSpatialVelocity();

    mNeedVelocityUpdate = false;
  }

  return mVelocity;
}

//==============================================================================
Eigen::Vector6d Frame::getSpatialVelocity(const Frame* _inCoordinatesOf) const
{
  if(this == _inCoordinatesOf)
    return getSpatialVelocity();

  if(_inCoordinatesOf->isWorld())
    return math::AdR(getWorldTransform(), getSpatialVelocity());

  return math::AdR(getTransform(_inCoordinatesOf), getSpatialVelocity());
}

//==============================================================================
Eigen::Vector6d Frame::getSpatialVelocity(const Frame* _relativeTo,
                                          const Frame* _inCoordinatesOf) const
{
  if(this == _relativeTo)
    return Eigen::Vector6d::Zero();

  if(_relativeTo->isWorld())
    return getSpatialVelocity(_inCoordinatesOf);

  const Eigen::Vector6d& result =
      getSpatialVelocity() - math::AdT(_relativeTo->getTransform(this),
                                       _relativeTo->getSpatialVelocity());

  if(this == _inCoordinatesOf)
    return result;

  return math::AdR(getTransform(_inCoordinatesOf), result);
}

//==============================================================================
Eigen::Vector3d Frame::getLinearVelocity(const Frame* _relativeTo,
                                         const Frame* _inCoordinatesOf) const
{
  return getSpatialVelocity(_relativeTo, _inCoordinatesOf).tail<3>();
}

//==============================================================================
Eigen::Vector3d Frame::getLinearVelocity(const Eigen::Vector3d& _offset,
                                         const Frame* _relativeTo,
                                         const Frame* _inCoordinatesOf) const
{
  const Eigen::Vector6d& V = getSpatialVelocity();

  if(this == _relativeTo)
    Eigen::Vector3d::Zero();

  if(Frame::World() == _relativeTo)
  {
    const Eigen::Vector3d& result = V.tail<3>() + V.head<3>().cross(_offset);

    if(this == _inCoordinatesOf)
      return result;

    return getTransform(_inCoordinatesOf).linear() * result;
  }

  const Eigen::Vector3d& result = V.tail<3>() + V.head<3>().cross(_offset)
                      - math::AdT(_relativeTo->getTransform(this),
                                  _relativeTo->getSpatialVelocity()).tail<3>();

  if(this == _inCoordinatesOf)
    return result;

  return getTransform(_inCoordinatesOf).linear() * result;
}

//==============================================================================
Eigen::Vector3d Frame::getAngularVelocity(const Frame* _relativeTo,
                                          const Frame* _inCoordinatesOf) const
{
  return getSpatialVelocity(_relativeTo,_inCoordinatesOf).head<3>();
}

//==============================================================================
const Eigen::Vector6d& Frame::getSpatialAcceleration() const
{
  if(mAmWorld)
    return mAcceleration;

  if(mNeedAccelerationUpdate)
  {
    mAcceleration = math::AdInvT(getRelativeTransform(),
                                 getParentFrame()->getSpatialAcceleration())
        + getPrimaryRelativeAcceleration()
        + getPartialAcceleration();

    mNeedAccelerationUpdate = false;
  }

  return mAcceleration;
}

//==============================================================================
Eigen::Vector6d Frame::getSpatialAcceleration(
    const Frame* _inCoordinatesOf) const
{
  if(this == _inCoordinatesOf)
    return getSpatialAcceleration();

  if(_inCoordinatesOf->isWorld())
    return math::AdR(getWorldTransform(), getSpatialAcceleration());

  return math::AdR(getTransform(_inCoordinatesOf), getSpatialAcceleration());
}

//==============================================================================
Eigen::Vector6d Frame::getSpatialAcceleration(
    const Frame* _relativeTo, const Frame* _inCoordinatesOf) const
{
  // Frame 2: this, Frame 1: _relativeTo, Frame O: _inCoordinatesOf
  // Acceleration of Frame 2 relative to Frame 1 in coordinates of O: a_21[O]
  // Total acceleration of Frame 2 in coordinates of Frame 2: a_2[2]
  // Velocity of Frame 2 relative to Frame 1 in coordinates of Frame 2: v_21[2]

  // a_21[O] = R_O2*( a_2[2] - X_21*a_1[1] - v_2[2] x v_21[2] )

  if(this == _relativeTo)
    return Eigen::Vector6d::Zero();

  if(_relativeTo->isWorld())
    return getSpatialAcceleration(_inCoordinatesOf);

  const Eigen::Vector6d& result =
      getSpatialAcceleration()
      - math::AdT(_relativeTo->getTransform(this),
                  _relativeTo->getSpatialAcceleration())
      - math::ad(getSpatialVelocity(),
                 getSpatialVelocity(_relativeTo, this));

  if(this == _inCoordinatesOf)
    return result;

  return math::AdR(getTransform(_inCoordinatesOf), result);
}

//==============================================================================
Eigen::Vector3d Frame::getLinearAcceleration(
    const Frame* _relativeTo, const Frame* _inCoordinatesOf) const
{
  if(this == _relativeTo)
    return Eigen::Vector3d::Zero();

  const Eigen::Vector6d& v_rel = getSpatialVelocity(_relativeTo,
                                                    _inCoordinatesOf);

  // r'' = a + w x v
  return getSpatialAcceleration(_relativeTo,_inCoordinatesOf).tail<3>()
         + v_rel.head<3>().cross(v_rel.tail<3>());
}

//==============================================================================
Eigen::Vector3d Frame::getLinearAcceleration(const Eigen::Vector3d& _offset,
                                             const Frame* _relativeTo,
                                             const Frame* _inCoordinatesOf) const
{
  if(this == _relativeTo)
    return Eigen::Vector3d::Zero();

  const Eigen::Vector3d& a_parent = getLinearAcceleration(Frame::World(), this);
  const Eigen::Vector3d& alpha = getAngularAcceleration(Frame::World(), this);
  const Eigen::Vector3d& w = getAngularVelocity(Frame::World(), this);

  // Compute linear acceleration of the point relative to the world, in the
  // coordinates of this Frame
  const Eigen::Vector3d& a =
      a_parent + alpha.cross(_offset) + w.cross(w.cross(_offset));

  if(_relativeTo->isWorld())
  {
    if(this == _inCoordinatesOf)
      return a;

    return getTransform(_inCoordinatesOf).linear() * a;
  }

  // Compute the relative linear acceleration of the point
  const Eigen::Vector3d& a_rel = a
      - _relativeTo->getLinearAcceleration(Frame::World(), this);

  if(this == _inCoordinatesOf)
    return a_rel;

  return getTransform(_inCoordinatesOf).linear() * a_rel;
}

//==============================================================================
Eigen::Vector3d Frame::getAngularAcceleration(
    const Frame* _relativeTo, const Frame* _inCoordinatesOf) const
{
  return getSpatialAcceleration(_relativeTo, _inCoordinatesOf).head<3>();
}

//==============================================================================
template <typename T>
static std::set<const T*> convertToConstSet(const std::set<T*>& _set)
{
  std::set<const T*> const_set;
  for(const auto& element : _set)
    const_set.insert(element);

  return const_set;
}

//==============================================================================
const std::set<Entity*>& Frame::getChildEntities()
{
  return mChildEntities;
}

//==============================================================================
const std::set<const Entity*> Frame::getChildEntities() const
{
  return convertToConstSet<Entity>(mChildEntities);
}

//==============================================================================
size_t Frame::getNumChildEntities() const
{
  return mChildEntities.size();
}

//==============================================================================
const std::set<Frame*>& Frame::getChildFrames()
{
  return mChildFrames;
}

//==============================================================================
std::set<const Frame*> Frame::getChildFrames() const
{
  return convertToConstSet<Frame>(mChildFrames);
}

//==============================================================================
size_t Frame::getNumChildFrames() const
{
  return mChildFrames.size();
}

//==============================================================================
bool Frame::isWorld() const
{
  return mAmWorld;
}

//==============================================================================
void Frame::draw(renderer::RenderInterface* _ri, const Eigen::Vector4d& _color,
                 bool _useDefaultColor, int _depth) const
{
  if(NULL == _ri)
    return;

  _ri->pushMatrix();

  // Use the relative transform of this Frame. We assume that we are being
  // called from the parent Frame's renderer.
  // TODO(MXG): This can cause trouble if the draw function is originally called
  // on an Entity or Frame which is not a child of the World Frame
  _ri->transform(getRelativeTransform());

  // _ri->pushName(???); TODO(MXG): What should we do about this for Frames?
  for(size_t i=0; i < mVizShapes.size(); ++i)
  {
    _ri->pushMatrix();
    mVizShapes[i]->draw(_ri, _color, _useDefaultColor);
    _ri->popMatrix();
  }
  // _ri.popName();

  // render the subtree
  for(Entity* entity : mChildEntities)
    entity->draw(_ri, _color, _useDefaultColor);

  _ri->popMatrix();
}

//==============================================================================
void Frame::notifyTransformUpdate()
{
  notifyVelocityUpdate(); // Global Velocity depends on the Global Transform

  // If we already know we need to update, just quit
  if(mNeedTransformUpdate)
    return;

  mNeedTransformUpdate = true;

  for(Entity* entity : mChildEntities)
    entity->notifyTransformUpdate();
}

//==============================================================================
void Frame::notifyVelocityUpdate()
{
  notifyAccelerationUpdate(); // Global Acceleration depends on Global Velocity

  // If we already know we need to update, just quit
  if(mNeedVelocityUpdate)
    return;

  mNeedVelocityUpdate = true;

  for(Entity* entity : mChildEntities)
    entity->notifyVelocityUpdate();
}

//==============================================================================
void Frame::notifyAccelerationUpdate()
{
  // If we already know we need to update, just quit
  if(mNeedAccelerationUpdate)
    return;

  mNeedAccelerationUpdate = true;

  for(Entity* entity : mChildEntities)
    entity->notifyAccelerationUpdate();
}

//==============================================================================
void Frame::changeParentFrame(Frame* _newParentFrame)
{
  if(_newParentFrame)
  {
    if(_newParentFrame->dependsOn(this))
    {
      if(!(this->isWorld() && _newParentFrame->isWorld()))
      // We make an exception here for the World Frame, because it's special/unique
      {
        dtwarn << "[Frame::changeParentFrame(~)] Attempting to create a circular "
               << "kinematic dependency by making Frame '" << getName()
               << "' a child of Frame '" << _newParentFrame->getName() << "'. "
               << "This will not be allowed.\n";
        return;
      }
    }
  }

  if(mParentFrame)
  {
    FramePtrSet::iterator it = mParentFrame->mChildFrames.find(this);
    if(it != mParentFrame->mChildFrames.end())
      mParentFrame->mChildFrames.erase(it);
  }

  if(NULL==_newParentFrame)
  {
    Entity::changeParentFrame(_newParentFrame);
    return;
  }

  Entity::changeParentFrame(_newParentFrame);
  if(!mAmQuiet)
    mParentFrame->mChildFrames.insert(this);
}

//==============================================================================
void Frame::processNewEntity(Entity*)
{
  // Do nothing
}

//==============================================================================
void Frame::processRemovedEntity(Entity*)
{
  // Do nothing
}

//==============================================================================
Frame::Frame()
  : Entity(this, "World", true),
    mWorldTransform(Eigen::Isometry3d::Identity()),
    mVelocity(Eigen::Vector6d::Zero()),
    mAcceleration(Eigen::Vector6d::Zero()),
    mAmWorld(true)
{

}

//==============================================================================
const Eigen::Isometry3d& WorldFrame::getRelativeTransform() const
{
  return mRelativeTf;
}

//==============================================================================
const Eigen::Vector6d& WorldFrame::getRelativeSpatialVelocity() const
{
  return mZero;
}

//==============================================================================
const Eigen::Vector6d& WorldFrame::getRelativeSpatialAcceleration() const
{
  return mZero;
}

//==============================================================================
const Eigen::Vector6d& WorldFrame::getPrimaryRelativeAcceleration() const
{
  return mZero;
}

//==============================================================================
const Eigen::Vector6d& WorldFrame::getPartialAcceleration() const
{
  return mZero;
}

//==============================================================================
WorldFrame::WorldFrame()
  : Entity(NULL, "World", true),
    Frame(),
    mRelativeTf(Eigen::Isometry3d::Identity()),
    mZero(Eigen::Vector6d::Zero())
{
  changeParentFrame(this);
}

} // namespace dart
} // namespace dynamics
