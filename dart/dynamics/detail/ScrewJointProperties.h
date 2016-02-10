/*
 * Copyright (c) 2015, Georgia Tech Research Corporation
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

#ifndef DART_DYNAMICS_DETAIL_SCREWJOINTPROPERTIES_H_
#define DART_DYNAMICS_DETAIL_SCREWJOINTPROPERTIES_H_

#include <string>

#include <Eigen/Dense>

#include "dart/dynamics/SingleDofJoint.h"
#include "dart/dynamics/Addon.h"

namespace dart {
namespace dynamics {

class ScrewJoint;

namespace detail {

//==============================================================================
struct ScrewJointUniqueProperties
{
  /// Rotational axis
  Eigen::Vector3d mAxis;

  /// Translational pitch
  double mPitch;

  ScrewJointUniqueProperties(
      const Eigen::Vector3d& _axis = Eigen::Vector3d::UnitZ(),
      double _pitch = 0.1);

  virtual ~ScrewJointUniqueProperties() = default;
};

//==============================================================================
struct ScrewJointProperties : SingleDofJoint::Properties,
                    ScrewJointUniqueProperties
{
  ScrewJointProperties(
      const SingleDofJoint::Properties& _singleDofProperties =
          SingleDofJoint::Properties(),
      const ScrewJointUniqueProperties& _screwProperties =
          ScrewJointUniqueProperties());

  virtual ~ScrewJointProperties() = default;
};

//==============================================================================
class ScrewJointAddon final :
    public AddonWithProtectedPropertiesInSkeleton<
        ScrewJointAddon, ScrewJointUniqueProperties, ScrewJoint,
        detail::JointPropertyUpdate<ScrewJointAddon> >
{
public:
  DART_DYNAMICS_JOINT_ADDON_CONSTRUCTOR( ScrewJointAddon )

  void setAxis(const Eigen::Vector3d& _axis);
  const Eigen::Vector3d& getAxis() const;

  DART_DYNAMICS_SET_GET_ADDON_PROPERTY(double, Pitch)
};

//==============================================================================
using ScrewJointBase = common::AddonManagerJoiner<
    SingleDofJoint, common::RequiresAddon<ScrewJointAddon> >;

} // namespace detail
} // namespace dynamics
} // namespace dart

#endif // DART_DYNAMICS_DETAIL_SCREWJOINTPROPERTIES_H_
