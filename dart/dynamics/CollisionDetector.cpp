/*
 * Copyright (c) 2016, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Jeongseok Lee <jslee02@gmail.com>
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

#include "dart/dynamics/CollisionDetector.h"

#include "dart/dynamics/BodyNode.h"

namespace dart {
namespace dynamics {

//==============================================================================
bool BodyNodeCollisionFilter::needCollision(
    const collision::CollisionObject* object1,
    const collision::CollisionObject* object2) const
{
  if (object1 == object2)
    return false;

  auto castedObj1 = static_cast<const ShapeNodeCollisionObject*>(object1);
  auto castedObj2 = static_cast<const ShapeNodeCollisionObject*>(object2);

  auto bodyNode1 = castedObj1->getBodyNode();
  auto bodyNode2 = castedObj2->getBodyNode();

  if (!bodyNode1->isCollidable() || !bodyNode2->isCollidable())
    return false;

  if (bodyNode1->getSkeleton() == bodyNode2->getSkeleton())
  {
    auto skeleton = bodyNode1->getSkeleton();

    if (!skeleton->isEnabledSelfCollisionCheck())
      return false;

    if (!skeleton->isEnabledAdjacentBodyCheck())
    {
      if (isAdjacentBodies(bodyNode1, bodyNode2))
        return false;
    }
  }

  return true;
}

//==============================================================================
bool BodyNodeCollisionFilter::isAdjacentBodies(const BodyNode* bodyNode1,
                                               const BodyNode* bodyNode2) const
{
  if ((bodyNode1->getParentBodyNode() == bodyNode2)
      || (bodyNode2->getParentBodyNode() == bodyNode1))
  {
    assert(bodyNode1->getSkeleton() == bodyNode2->getSkeleton());
    return true;
  }

  return false;
}

//==============================================================================
const Eigen::Isometry3d ShapeNodeCollisionObject::getTransform() const
{
  return mShapeNode->getWorldTransform();
}

//==============================================================================
bool ShapeNodeCollisionObject::isEqual(
    const collision::CollisionObject* other) const
{
  if (this == other)
    return true;

  auto castedOther = dynamic_cast<const ShapeNodeCollisionObject*>(other);

  if (!castedOther)
    return false;

  if (mShape != castedOther->mShape)
    return false;

  if (mShapeNode != castedOther->mShapeNode)
    return false;

  // If castedOther has the same shape and body node then it must be the same
  // pointer with this as well because the collision detector doesn't allow to
  // create new collision objects for the same shape and body node.
  assert(this != other);

  return true;
}

//==============================================================================
ShapeNode* ShapeNodeCollisionObject::getShapeNode()
{
  return mShapeNode.get();
}

//==============================================================================
const ShapeNode* ShapeNodeCollisionObject::getShapeNode() const
{
  return mShapeNode.get();
}

//==============================================================================
BodyNode* ShapeNodeCollisionObject::getBodyNode()
{
  return mShapeNode->getBodyNodePtr().get();
}

//==============================================================================
const BodyNode* ShapeNodeCollisionObject::getBodyNode() const
{
  return mShapeNode->getBodyNodePtr().get();
}

//==============================================================================
ShapeNodeCollisionObject::ShapeNodeCollisionObject(
    const collision::CollisionDetectorPtr& collisionDetector,
    const ShapePtr& shape,
    const ShapeNodePtr& shapeNode)
  : collision::CollisionObject(collisionDetector, shape),
    mShapeNode(shapeNode)
{
  assert(collisionDetector);
  assert(shapeNode);
  assert(shapeNode->getShape());
  assert(shape == shapeNode->getShape());

  if (!mShapeNode->hasCollisionAddon())
  {
    dtwarn << "[ShapeFrameCollisionObject::constructor] Attempting to create "
           << "ShapeFrameCollisionObject with invalid pair of Shape and "
           << "BodyNode.\n";
    assert(false);
  }
}

//==============================================================================
ShapeNodeCollisionObjectPtr createShapeNodeCollisionObject(
    const collision::CollisionDetectorPtr& collisionDetector,
    const ShapeNodePtr& shapeNode)
{
  return collisionDetector->createCollisionObject<ShapeNodeCollisionObject>(
        shapeNode->getShape(), shapeNode);
}

//==============================================================================
std::vector<collision::CollisionObjectPtr> createShapeFrameCollisionObjects(
    const collision::CollisionDetectorPtr& collisionDetector,
    const SkeletonPtr& skel)
{
  std::vector<collision::CollisionObjectPtr> objects;

  auto numBodyNodes = skel->getNumBodyNodes();
  for (auto i = 0u; i < numBodyNodes; ++i)
  {
    auto bodyNode = skel->getBodyNode(i);
    auto collisionShapeNodes = bodyNode->getShapeNodesWith<CollisionAddon>();

    for (auto& shapeNode : collisionShapeNodes)
    {
      auto collObj
          = createShapeNodeCollisionObject(collisionDetector, shapeNode);

      objects.push_back(
            std::static_pointer_cast<collision::CollisionObject>(collObj));
    }
  }

  return objects;
}

//==============================================================================
collision::CollisionGroupPtr createShapeFrameCollisionGroup(
    const collision::CollisionDetectorPtr& collisionDetector,
    const SkeletonPtr& skel)
{
  auto collObjs = createShapeFrameCollisionObjects(collisionDetector, skel);
  auto group = collisionDetector->createCollisionGroup(collObjs);

  return group;
}

} // namespace dynamics
} // namespace dart
