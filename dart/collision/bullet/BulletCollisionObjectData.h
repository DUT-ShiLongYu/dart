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

#ifndef DART_COLLISION_BULLET_BULLETCOLLISIONOBJECTDATA_H_
#define DART_COLLISION_BULLET_BULLETCOLLISIONOBJECTDATA_H_

#include <cstddef>
#include <Eigen/Dense>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <btBulletCollisionCommon.h>
#include <bullet/BulletCollision/Gimpact/btGImpactShape.h>
#include "dart/collision/CollisionObjectData.h"

namespace dart {
namespace collision {

class CollisionObject;

struct BulletCollisionObjectUserData
{
  CollisionObject* collisionObject;

  CollisionDetector* collisionDetector;
  CollisionGroup* group;

  BulletCollisionObjectUserData(CollisionObject* collisionObject,
                                CollisionDetector* collisionDetector,
                                CollisionGroup* collisionGroup);
};

class BulletCollisionObjectData : public CollisionObjectData
{
public:

  friend class BulletCollisionDetector;

  // Documentation inherited
  void updateTransform(const Eigen::Isometry3d& tf) override;

  // Documentation inherited
  void update() override;

  /// Return FCL collision object
  btCollisionObject* getBulletCollisionObject() const;

protected:

  /// Constructor
  BulletCollisionObjectData(CollisionDetector* collisionDetector,
                            CollisionObject* parent,
                            btCollisionShape* bulletCollisionShape);

protected:

  /// Bullet collision geometry user data
  std::unique_ptr<BulletCollisionObjectUserData> mBulletCollisionObjectUserData;

  /// Bullet collision object
  std::unique_ptr<btCollisionObject> mBulletCollisionObject;

};

}  // namespace collision
}  // namespace dart

#endif  // DART_COLLISION_BULLET_BULLETCOLLISIONOBJECTDATA_H_
