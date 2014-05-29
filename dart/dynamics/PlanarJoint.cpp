/*
 * Copyright (c) 2014, Georgia Tech Research Corporation
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

#include "dart/dynamics/PlanarJoint.h"

#include <string>

#include "dart/common/Console.h"
#include "dart/math/Geometry.h"
#include "dart/math/Helpers.h"

namespace dart {
namespace dynamics {

//==============================================================================
PlanarJoint::PlanarJoint(const std::string& _name)
  : MultiDofJoint(_name)
{
  // TODO(JS): Deprecated
  mS = mJacobian;

  // TODO(JS): Deprecated
  mdS = mJacobianDeriv;

  setXYPlane();
}

//==============================================================================
PlanarJoint::~PlanarJoint()
{
}

//==============================================================================
void PlanarJoint::setXYPlane()
{
  mPlaneType = PT_XY;
  mRotAxis   = Eigen::Vector3d::UnitZ();
  mTransAxis1 = Eigen::Vector3d::UnitX();
  mTransAxis2 = Eigen::Vector3d::UnitY();
}

//==============================================================================
void PlanarJoint::setYZPlane()
{
  mPlaneType = PT_YZ;
  mRotAxis   = Eigen::Vector3d::UnitX();
  mTransAxis1 = Eigen::Vector3d::UnitY();
  mTransAxis2 = Eigen::Vector3d::UnitZ();
}

//==============================================================================
void PlanarJoint::setZXPlane()
{
  mPlaneType = PT_ZX;
  mRotAxis   = Eigen::Vector3d::UnitY();
  mTransAxis1 = Eigen::Vector3d::UnitZ();
  mTransAxis2 = Eigen::Vector3d::UnitX();
}

//==============================================================================
void PlanarJoint::setArbitraryPlane(const Eigen::Vector3d& _transAxis1,
                                    const Eigen::Vector3d& _transAxis2)
{
  // Set plane type as arbitrary plane
  mPlaneType = PT_ARBITRARY;

  // First translational axis
  mTransAxis1 = _transAxis1.normalized();

  // Second translational axis
  mTransAxis2 = _transAxis2.normalized();

  // Orthogonalize translational axese
  double dotProduct = mTransAxis1.dot(mTransAxis2);
  assert(std::fabs(dotProduct) < 1.0 - 1e-6);
  if (std::fabs(dotProduct) > 1e-6)
    mTransAxis2 = (mTransAxis2 - dotProduct * mTransAxis1).normalized();

  // Rotational axis
  mRotAxis = (mTransAxis1.cross(mTransAxis2)).normalized();
}

//==============================================================================
PlanarJoint::PlaneType PlanarJoint::getPlaneType() const
{
  return mPlaneType;
}

//==============================================================================
const Eigen::Vector3d& PlanarJoint::getRotationalAxis() const
{
  return mRotAxis;
}

//==============================================================================
const Eigen::Vector3d& PlanarJoint::getTranslationalAxis1() const
{
  return mTransAxis1;
}

//==============================================================================
const Eigen::Vector3d& PlanarJoint::getTranslationalAxis2() const
{
  return mTransAxis2;
}

//==============================================================================
void PlanarJoint::updateLocalTransform()
{
  mT = mT_ParentBodyToJoint
       * Eigen::Translation3d(mTransAxis1 * mPositions[0])
       * Eigen::Translation3d(mTransAxis2 * mPositions[1])
       * math::expAngular    (mRotAxis    * mPositions[2])
       * mT_ChildBodyToJoint.inverse();

  // Verification
  assert(math::verifyTransform(mT));
}

//==============================================================================
void PlanarJoint::updateLocalJacobian()
{
  Eigen::Matrix<double, 6, 3> J = Eigen::Matrix<double, 6, 3>::Zero();
  J.block<3, 1>(3, 0) = mTransAxis1;
  J.block<3, 1>(3, 1) = mTransAxis2;
  J.block<3, 1>(0, 2) = mRotAxis;

  mJacobian.leftCols<2>()
      = math::AdTJacFixed(mT_ChildBodyToJoint
                          * math::expAngular(mRotAxis * -mPositions[2]),
                          J.leftCols<2>());
  mJacobian.col(2) = math::AdTJac(mT_ChildBodyToJoint, J.col(2));

  // Verification
  assert(!math::isNan(mJacobian));

  // TODO(JS): Deprecated
  mS = mJacobian;
}

//==============================================================================
void PlanarJoint::updateLocalJacobianTimeDeriv()
{
  Eigen::Matrix<double, 6, 3> J = Eigen::Matrix<double, 6, 3>::Zero();
  J.block<3, 1>(3, 0) = mTransAxis1;
  J.block<3, 1>(3, 1) = mTransAxis2;
  J.block<3, 1>(0, 2) = mRotAxis;

  mJacobianDeriv.col(0)
      = -math::ad(mJacobian.col(2) * mVelocities[2],
                  math::AdT(mT_ChildBodyToJoint
                            * math::expAngular(mRotAxis
                                               * -mPositions[2]),
                            J.col(0)));

  mJacobianDeriv.col(1)
      = -math::ad(mJacobian.col(2) * mVelocities[2],
                  math::AdT(mT_ChildBodyToJoint
                            * math::expAngular(mRotAxis
                                               * -mPositions[2]),
                            J.col(1)));

  assert(mJacobianDeriv.col(2) == Eigen::Vector6d::Zero());
  assert(!math::isNan(mJacobianDeriv.col(0)));
  assert(!math::isNan(mJacobianDeriv.col(1)));

  // TODO(JS): Deprecated
  mdS = mJacobianDeriv;
}

}  // namespace dynamics
}  // namespace dart
