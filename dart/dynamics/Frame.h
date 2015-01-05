/*
 * Copyright (c) 2014, Georgia Tech Research Corporation
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

#ifndef DART_DYNAMICS_FRAME_H_
#define DART_DYNAMICS_FRAME_H_

#include "dart/dynamics/Entity.h"
#include <set>
#include "Eigen/Geometry"

namespace dart {
namespace dynamics {

typedef std::set<Entity*> EntityPtrSet;
typedef std::set<const Entity*> ConstEntityPtrSet;
typedef std::set<Frame*> FramePtrSet;
typedef std::set<const Frame*> ConstFramePtrSet;

/// The Frame class serves as the backbone of DART's kinematic tree structure.
///
/// Frame inherits Entity, so it exists within a reference Frame. This class
/// keeps track of both its local (relative) and global (world) transforms,
/// velocities, and accelerations. It also notifies every child Entity when
class Frame : public virtual Entity
{
public:
  friend class Entity;
  friend class WorldFrame;

  /// Constructor for typical usage
  explicit Frame(const Frame* _refFrame, const std::string& _name);

  /// Destructor
  virtual ~Frame();

  static const Frame* World();

  /// Get the transform of this Frame with respect to its parent Frame
  virtual const Eigen::Isometry3d& getRelativeTransform() const = 0;

  /// Get the transform of this Frame with respect to the World Frame
  const Eigen::Isometry3d& getWorldTransform() const;

  /// Get the transform of this Frame with respect to some other Frame
  Eigen::Isometry3d getTransform(const Frame* withRespectTo =
                                                  Frame::World()) const;

  /// Get a container with the Entities that are children of this Frame.
  /// std::set is used because Entities may be arbitrarily added and removed
  /// from a parent Frame, and each entry should be unique.
  const EntityPtrSet& getChildEntities();

  /// Get a container with the Entities that are children of this Frame. Note
  /// that this is version is less efficient than the non-const version because
  /// it needs to rebuild a set so that the entries are const.
  ConstEntityPtrSet getChildEntities() const;

  /// Get the number of Entities that are currently children of this Frame.
  size_t getNumChildEntities() const;

  /// Get a container with the Frames that are children of this Frame.
  /// std::set is used because Frames may be arbitrarily added and removed
  /// from a parent Frame, and each entry should be unique.
  const FramePtrSet& getChildFrames();

  /// Get a container with the Frames that are children of this Frame. Note
  /// that this version is less efficient than the non-const version because
  /// it needs to rebuild a set so that the entries are const.
  ConstFramePtrSet getChildFrames() const;

  /// Get the number of Frames that are currently children of this Frame.
  size_t getNumChildFrames() const;

  /// Returns true if this Frame is the World Frame
  bool isWorld() const;

  // Render this Frame as well as any Entities it contains
  virtual void draw(renderer::RenderInterface *_ri = NULL,
                    const Eigen::Vector4d &_color = Eigen::Vector4d::Ones(),
                    bool _useDefaultColor = true, int _depth = 0) const;

protected:
  /// Notify this Frame and all its children that its pose has changed
  virtual void notifyTransformUpdate();

  /// Notify this Frame and all its children that its velocity has changed
  virtual void notifyVelocityUpdate();

  /// Notify this Frame and all its children that its acceleration has changed
  virtual void notifyAccelerationUpdate();

  // Documentation inherited
  virtual void changeParentFrame(const Frame* _newParentFrame);

private:
  /// Constructor for World Frame
  explicit Frame();

protected:
  /// World transform of this Frame. This object is mutable to enable
  /// auto-updating to happen in the const member getWorldTransform() function
  mutable Eigen::Isometry3d mWorldTransform;

  /// Container of this Frame's child Frames. This object is mutable to enable
  /// children to be added to const Frames. Receiving a new child does not
  /// affect any properties of the parent Frame.
  mutable FramePtrSet mChildFrames;

  /// Container of this Frame's child Entities. This object is mutable to enable
  /// children to be added to const Frames. Receiving a new child does not
  /// affect any properties of the parent Frame.
  mutable EntityPtrSet mChildEntities;

private:
  /// Contains whether or not this is the World Frame
  bool mAmWorld;

};

class WorldFrame : public Frame
{
public:
  friend class Frame;

  /// Always returns the Identity Transform
  const Eigen::Isometry3d& getRelativeTransform() const;

private:
  /// This may only be constructed by the Frame class
  explicit WorldFrame();

protected:
  /// This is set to Identity and never changes
  Eigen::Isometry3d mRelativeTf;

};

class PureFrame : public Frame, public Detachable
{
public:
  /// Constructor
  explicit PureFrame(const Frame* _refFrame, const std::string& _name,
                     const Eigen::Isometry3d& _relativeTransform =
                                        Eigen::Isometry3d::Identity());

  /// Destructor
  virtual ~PureFrame();

  /// Set the relative transform of this PureFrame
  void setRelativeTransform(const Eigen::Isometry3d& _newRelTransform);

  const Eigen::Isometry3d& getRelativeTransform() const;

protected:
  /// Relative Transform of this Frame
  Eigen::Isometry3d mRelativeTf;

};

} // namespace dynamics
} // namespace dart

#endif // DART_DYNAMICS_FRAME_H_
