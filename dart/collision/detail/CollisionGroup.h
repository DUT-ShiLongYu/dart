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

#ifndef DART_COLLISION_DETAIL_COLLISIONGROUP_H_
#define DART_COLLISION_DETAIL_COLLISIONGROUP_H_

#include "dart/collision/CollisionGroup.h"

#include "dart/dynamics/BodyNode.h"
#include "dart/dynamics/Skeleton.h"

namespace dart {
namespace collision {

//==============================================================================
template <typename... Others>
void CollisionGroup::addShapeFramesOf(
    const dynamics::ShapeFrame* shapeFrame, const Others*... others)
{
  addShapeFrame(shapeFrame);

  addShapeFramesOf(others...);
}

//==============================================================================
template <typename... Others>
void CollisionGroup::addShapeFramesOf(
    const std::vector<const dynamics::ShapeFrame*>& shapeFrames,
    const Others*... others)
{
  addShapeFrames(shapeFrames);

  addShapeFramesOf(others...);
}

//==============================================================================
template <typename... Others>
void CollisionGroup::addShapeFramesOf(
    const CollisionGroup* otherGroup, const Others*... others)
{
  assert(otherGroup);

  if (otherGroup && this != otherGroup)
  {
    for (const auto& shapeFrame : otherGroup->mShapeFrames)
      addShapeFrame(shapeFrame);
  }

  addShapeFramesOf(others...);
}

//==============================================================================
template <typename... Others>
void CollisionGroup::addShapeFramesOf(
    const dynamics::BodyNode* bodyNode, const Others*... others)
{
  assert(bodyNode);

  auto collisionShapeNodes
      = bodyNode->getShapeNodesWith<dynamics::CollisionAddon>();

  for (auto& shapeNode : collisionShapeNodes)
    addShapeFrame(shapeNode);

  addShapeFramesOf(others...);
}

//==============================================================================
template <typename... Others>
void CollisionGroup::addShapeFramesOf(
    const dynamics::Skeleton* skel, const Others*... others)
{
  assert(skel);

  auto numBodyNodes = skel->getNumBodyNodes();
  for (auto i = 0u; i < numBodyNodes; ++i)
    addShapeFramesOf(skel->getBodyNode(i));

  addShapeFramesOf(others...);
}

//==============================================================================
template <typename... Others>
void CollisionGroup::removeShapeFramesOf(
    const dynamics::ShapeFrame* shapeFrame, const Others*... others)
{
  removeShapeFrame(shapeFrame);

  removeShapeFramesOf(others...);
}

//==============================================================================
template <typename... Others>
void CollisionGroup::removeShapeFramesOf(
    const std::vector<const dynamics::ShapeFrame*>& shapeFrames,
    const Others*... others)
{
  removeShapeFrames(shapeFrames);

  removeShapeFramesOf(others...);
}

//==============================================================================
template <typename... Others>
void CollisionGroup::removeShapeFramesOf(
    const CollisionGroup* otherGroup, const Others*... others)
{
  assert(otherGroup);

  if (otherGroup)
  {
    if (this == otherGroup)
    {
      unregisterAllShapeFrames();
      return;
    }

    for (const auto& shapeFrame : otherGroup->mShapeFrames)
      removeShapeFrame(shapeFrame);
  }

  removeShapeFramesOf(others...);
}

//==============================================================================
template <typename... Others>
void CollisionGroup::removeShapeFramesOf(
    const dynamics::BodyNode* bodyNode, const Others*... others)
{
  assert(bodyNode);

  auto collisionShapeNodes
      = bodyNode->getShapeNodesWith<dynamics::CollisionAddon>();

  for (auto& shapeNode : collisionShapeNodes)
    removeShapeFrame(shapeNode);

  removeShapeFramesOf(others...);
}

//==============================================================================
template <typename... Others>
void CollisionGroup::removeShapeFramesOf(
    const dynamics::Skeleton* skel, const Others*... others)
{
  assert(skel);

  auto numBodyNodes = skel->getNumBodyNodes();
  for (auto i = 0u; i < numBodyNodes; ++i)
    removeShapeFramesOf(skel->getBodyNode(i));

  removeShapeFramesOf(others...);
}

}  // namespace collision
}  // namespace dart

#endif  // DART_COLLISION_DETAIL_COLLISIONGROUP_H_
