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

#ifndef DART_DYNAMICS_MULTIDOFJOINT_H_
#define DART_DYNAMICS_MULTIDOFJOINT_H_

#include <iostream>
#include <string>

#include "dart/config.h"
#include "dart/common/Console.h"
#include "dart/math/Helpers.h"
#include "dart/dynamics/Joint.h"
#include "dart/dynamics/Skeleton.h"

namespace dart {
namespace dynamics {

class BodyNode;
class Skeleton;

/// class MultiDofJoint
template<size_t DOF>
class MultiDofJoint : public Joint
{
public:
  /// Constructor
  MultiDofJoint(const std::string& _name);

  /// Destructor
  virtual ~MultiDofJoint();

  //----------------------------------------------------------------------------
  // Interface for generalized coordinates
  //----------------------------------------------------------------------------

  // Documentation inherited
  DEPRECATED(4.1)
  virtual size_t getDof() const;

  // Documentation inherited
  virtual size_t getNumDofs() const;

  // Documentation inherited
  virtual void setIndexInSkeleton(size_t _index, size_t _indexInSkeleton);

  // Documentation inherited
  virtual size_t getIndexInSkeleton(size_t _index) const;

  //----------------------------------------------------------------------------
  // Command
  //----------------------------------------------------------------------------

  // Documentation inherited
  virtual void setCommand(size_t _index, double _command);

  // Documentation inherited
  virtual double getCommand(size_t _index) const;

  // Documentation inherited
  virtual void setCommands(const Eigen::VectorXd& _commands);

  // Documentation inherited
  virtual Eigen::VectorXd getCommands() const;

  // Documentation inherited
  virtual void resetCommands();

  //----------------------------------------------------------------------------
  // Position
  //----------------------------------------------------------------------------

  // Documentation inherited
  virtual void setPosition(size_t _index, double _position);

  // Documentation inherited
  virtual double getPosition(size_t _index) const;

  // Documentation inherited
  virtual void setPositions(const Eigen::VectorXd& _positions);

  // Documentation inherited
  virtual Eigen::VectorXd getPositions() const;

  // Documentation inherited
  virtual void resetPositions();

  // Documentation inherited
  virtual void setPositionLowerLimit(size_t _index, double _position);

  // Documentation inherited
  virtual double getPositionLowerLimit(size_t _index) const;

  // Documentation inherited
  virtual void setPositionUpperLimit(size_t _index, double _position);

  // Documentation inherited
  virtual double getPositionUpperLimit(size_t _index) const;

  //----------------------------------------------------------------------------
  // Velocity
  //----------------------------------------------------------------------------

  // Documentation inherited
  virtual void setVelocity(size_t _index, double _velocity);

  // Documentation inherited
  virtual double getVelocity(size_t _index) const;

  // Documentation inherited
  virtual void setVelocities(const Eigen::VectorXd& _velocities);

  // Documentation inherited
  virtual Eigen::VectorXd getVelocities() const;

  // Documentation inherited
  virtual void resetVelocities();

  // Documentation inherited
  virtual void setVelocityLowerLimit(size_t _index, double _velocity);

  // Documentation inherited
  virtual double getVelocityLowerLimit(size_t _index) const;

  // Documentation inherited
  virtual void setVelocityUpperLimit(size_t _index, double _velocity);

  // Documentation inherited
  virtual double getVelocityUpperLimit(size_t _index) const;

  //----------------------------------------------------------------------------
  // Acceleration
  //----------------------------------------------------------------------------

  // Documentation inherited
  virtual void setAcceleration(size_t _index, double _acceleration);

  // Documentation inherited
  virtual double getAcceleration(size_t _index) const;

  // Documentation inherited
  virtual void setAccelerations(const Eigen::VectorXd& _accelerations);

  // Documentation inherited
  virtual Eigen::VectorXd getAccelerations() const;

  // Documentation inherited
  virtual void resetAccelerations();

  // Documentation inherited
  virtual void setAccelerationLowerLimit(size_t _index, double _acceleration);

  // Documentation inherited
  virtual double getAccelerationLowerLimit(size_t _index) const;

  // Documentation inherited
  virtual void setAccelerationUpperLimit(size_t _index, double _acceleration);

  // Documentation inherited
  virtual double getAccelerationUpperLimit(size_t _index) const;

  //----------------------------------------------------------------------------
  // Force
  //----------------------------------------------------------------------------

  // Documentation inherited
  virtual void setForce(size_t _index, double _force);

  // Documentation inherited
  virtual double getForce(size_t _index);

  // Documentation inherited
  virtual void setForces(const Eigen::VectorXd& _forces);

  // Documentation inherited
  virtual Eigen::VectorXd getForces() const;

  // Documentation inherited
  virtual void resetForces();

  // Documentation inherited
  virtual void setForceLowerLimit(size_t _index, double _force);

  // Documentation inherited
  virtual double getForceLowerLimit(size_t _index) const;

  // Documentation inherited
  virtual void setForceUpperLimit(size_t _index, double _force);

  // Documentation inherited
  virtual double getForceUpperLimit(size_t _index) const;

  //----------------------------------------------------------------------------
  // Velocity change
  //----------------------------------------------------------------------------

  // Documentation inherited
  virtual void setVelocityChange(size_t _index, double _velocityChange);

  // Documentation inherited
  virtual double getVelocityChange(size_t _index) const;

  // Documentation inherited
  virtual void resetVelocityChanges();

  //----------------------------------------------------------------------------
  // Constraint impulse
  //----------------------------------------------------------------------------

  // Documentation inherited
  virtual void setConstraintImpulse(size_t _index, double _impulse);

  // Documentation inherited
  virtual double getConstraintImpulse(size_t _index) const;

  // Documentation inherited
  virtual void resetConstraintImpulses();

  //----------------------------------------------------------------------------
  // Integration
  //----------------------------------------------------------------------------

  // Documentation inherited
  virtual void integratePositions(double _dt);

  // Documentation inherited
  virtual void integrateVelocities(double _dt);

  //----------------------------------------------------------------------------
  // Spring and damper
  //----------------------------------------------------------------------------

  // Documentation inherited
  virtual void setSpringStiffness(size_t _index, double _k);

  // Documentation inherited
  virtual double getSpringStiffness(size_t _index) const;

  // Documentation inherited
  virtual void setRestPosition(size_t _index, double _q0);

  // Documentation inherited
  virtual double getRestPosition(size_t _index) const;

  // Documentation inherited
  virtual void setDampingCoefficient(size_t _index, double _d);

  // Documentation inherited
  virtual double getDampingCoefficient(size_t _index) const;

  //----------------------------------------------------------------------------

  // Documentation inherited
  virtual double getPotentialEnergy() const;

protected:
  //----------------------------------------------------------------------------
  /// \{ \name Recursive dynamics routines
  //----------------------------------------------------------------------------

  // Documentation inherited
  virtual const math::Jacobian getLocalJacobian() const override;

  // Documentation inherited
  virtual const math::Jacobian getLocalJacobianTimeDeriv() const override;

  // Documentation inherited
  virtual void addVelocityTo(Eigen::Vector6d& _vel) override;

  // Documentation inherited
  virtual void setPartialAccelerationTo(
      Eigen::Vector6d& _partialAcceleration,
      const Eigen::Vector6d& _childVelocity) override;

  // Documentation inherited
  virtual void addAccelerationTo(Eigen::Vector6d& _acc) override;

  // Documentation inherited
  virtual void addVelocityChangeTo(Eigen::Vector6d& _velocityChange) override;

  // Documentation inherited
  virtual void addChildArtInertiaFDTo(
      Eigen::Matrix6d& _parentArtInertia,
      const Eigen::Matrix6d& _childArtInertia) override;

  // Documentation inherited
  virtual void addChildArtInertiaHDTo(
      Eigen::Matrix6d& _parentArtInertia,
      const Eigen::Matrix6d& _childArtInertia) override;

  // Documentation inherited
  virtual void addChildArtInertiaImplicitFDTo(
      Eigen::Matrix6d& _parentArtInertia,
      const Eigen::Matrix6d& _childArtInertia) override;

  // Documentation inherited
  virtual void addChildArtInertiaImplicitHDTo(
      Eigen::Matrix6d& _parentArtInertia,
      const Eigen::Matrix6d& _childArtInertia) override;

  // Documentation inherited
  virtual void updateInvProjArtInertiaFD(
      const Eigen::Matrix6d& _artInertia) override;

  // Documentation inherited
  virtual void updateInvProjArtInertiaHD(
      const Eigen::Matrix6d& _artInertia) override;

  // Documentation inherited
  virtual void updateInvProjArtInertiaImplicitFD(
      const Eigen::Matrix6d& _artInertia, double _timeStep) override;

  // Documentation inherited
  virtual void updateInvProjArtInertiaImplicitHD(
      const Eigen::Matrix6d& _artInertia, double _timeStep) override;

  // Documentation inherited
  virtual void addChildBiasForceFDTo(
      Eigen::Vector6d& _parentBiasForce,
      const Eigen::Matrix6d& _childArtInertia,
      const Eigen::Vector6d& _childBiasForce,
      const Eigen::Vector6d& _childPartialAcc) override;

  // Documentation inherited
  virtual void addChildBiasForceHDTo(
      Eigen::Vector6d& _parentBiasForce,
      const Eigen::Matrix6d& _childArtInertia,
      const Eigen::Vector6d& _childBiasForce,
      const Eigen::Vector6d& _childPartialAcc) override;

  // Documentation inherited
  virtual void addChildBiasImpulseFDTo(
      Eigen::Vector6d& _parentBiasImpulse,
      const Eigen::Matrix6d& _childArtInertia,
      const Eigen::Vector6d& _childBiasImpulse) override;

  // Documentation inherited
  virtual void addChildBiasImpulseHDTo(
      Eigen::Vector6d& _parentBiasImpulse,
      const Eigen::Matrix6d& _childArtInertia,
      const Eigen::Vector6d& _childBiasImpulse) override;

  // Documentation inherited
  virtual void updateTotalForceFD(const Eigen::Vector6d& _bodyForce,
                                  double _timeStep) override;

  // Documentation inherited
  virtual void updateTotalForceHD(const Eigen::Vector6d& _bodyForce,
                                  double _timeStep) override;

  // Documentation inherited
  virtual void updateTotalImpulseFD(
      const Eigen::Vector6d& _bodyImpulse) override;

  // Documentation inherited
  virtual void updateTotalImpulseHD(
      const Eigen::Vector6d& _bodyImpulse) override;

  // Documentation inherited
  virtual void resetTotalImpulses() override;

  // Documentation inherited
  virtual void updateAccelerationFD(
      const Eigen::Matrix6d& _artInertia,
      const Eigen::Vector6d& _spatialAcc) override;

  // Documentation inherited
  virtual void updateAccelerationHD(
      const Eigen::Matrix6d& _artInertia,
      const Eigen::Vector6d& _spatialAcc) override;

  // Documentation inherited
  virtual void updateVelocityChangeFD(
      const Eigen::Matrix6d& _artInertia,
      const Eigen::Vector6d& _velocityChange) override;

  // Documentation inherited
  virtual void updateVelocityChangeHD(
      const Eigen::Matrix6d& _artInertia,
      const Eigen::Vector6d& _velocityChange) override;

  // Documentation inherited
  virtual void updateForceID(const Eigen::Vector6d& _bodyForce,
                             double _timeStep,
                             bool _withDampingForces,
                             bool _withSpringForces) override;

  // Documentation inherited
  virtual void updateForceHD(const Eigen::Vector6d& _bodyForce,
                             double _timeStep,
                             bool _withDampingForces,
                             bool _withSpringForces) override;

  // Documentation inherited
  virtual void updateImpulseID(const Eigen::Vector6d& _bodyImpulse) override;

  // Documentation inherited
  virtual void updateImpulseHD(const Eigen::Vector6d& _bodyImpulse) override;

  // Documentation inherited
  virtual void updateConstrainedTermsFD(double _timeStep) override;

  // Documentation inherited
  virtual void updateConstrainedTermsHD(double _timeStep) override;

  /// \}

  //----------------------------------------------------------------------------
  /// \{ \name Recursive algorithm routines for equations of motion
  //----------------------------------------------------------------------------

  // Documentation inherited
  virtual void addChildBiasForceForInvMassMatrix(
      Eigen::Vector6d& _parentBiasForce,
      const Eigen::Matrix6d& _childArtInertia,
      const Eigen::Vector6d& _childBiasForce);

  // Documentation inherited
  virtual void addChildBiasForceForInvAugMassMatrix(
      Eigen::Vector6d& _parentBiasForce,
      const Eigen::Matrix6d& _childArtInertia,
      const Eigen::Vector6d& _childBiasForce);

  // Documentation inherited
  virtual void updateTotalForceForInvMassMatrix(
      const Eigen::Vector6d& _bodyForce);

  // Documentation inherited
  virtual void getInvMassMatrixSegment(Eigen::MatrixXd& _invMassMat,
                               const size_t _col,
                               const Eigen::Matrix6d& _artInertia,
                               const Eigen::Vector6d& _spatialAcc);

  // Documentation inherited
  virtual void getInvAugMassMatrixSegment(Eigen::MatrixXd& _invMassMat,
                                          const size_t _col,
                                          const Eigen::Matrix6d& _artInertia,
                                          const Eigen::Vector6d& _spatialAcc);

  // Documentation inherited
  virtual void addInvMassMatrixSegmentTo(Eigen::Vector6d& _acc);

  // Documentation inherited
  virtual Eigen::VectorXd getSpatialToGeneralized(
      const Eigen::Vector6d& _spatial);

  /// \}

protected:
  // TODO(JS): Need?
  ///
  Eigen::Matrix<size_t, DOF, 1> mIndexInSkeleton;

  /// Command
  Eigen::Matrix<double, DOF, 1> mCommands;

  //----------------------------------------------------------------------------
  // Configuration
  //----------------------------------------------------------------------------

  /// Position
  Eigen::Matrix<double, DOF, 1> mPositions;

  /// Lower limit of position
  Eigen::Matrix<double, DOF, 1> mPositionLowerLimits;

  /// Upper limit of position
  Eigen::Matrix<double, DOF, 1> mPositionUpperLimits;

  /// Derivatives w.r.t. an arbitrary scalr variable
  Eigen::Matrix<double, DOF, 1> mPositionDeriv;

  //----------------------------------------------------------------------------
  // Velocity
  //----------------------------------------------------------------------------

  /// Generalized velocity
  Eigen::Matrix<double, DOF, 1> mVelocities;

  /// Min value allowed.
  Eigen::Matrix<double, DOF, 1> mVelocityLowerLimits;

  /// Max value allowed.
  Eigen::Matrix<double, DOF, 1> mVelocityUpperLimits;

  /// Derivatives w.r.t. an arbitrary scalr variable
  Eigen::Matrix<double, DOF, 1> mVelocitiesDeriv;

  //----------------------------------------------------------------------------
  // Acceleration
  //----------------------------------------------------------------------------

  /// Generalized acceleration
  Eigen::Matrix<double, DOF, 1> mAccelerations;

  /// Min value allowed.
  Eigen::Matrix<double, DOF, 1> mAccelerationLowerLimits;

  /// upper limit of generalized acceleration
  Eigen::Matrix<double, DOF, 1> mAccelerationUpperLimits;

  /// Derivatives w.r.t. an arbitrary scalr variable
  Eigen::Matrix<double, DOF, 1> mAccelerationsDeriv;

  //----------------------------------------------------------------------------
  // Force
  //----------------------------------------------------------------------------

  /// Generalized force
  Eigen::Matrix<double, DOF, 1> mForces;

  /// Min value allowed.
  Eigen::Matrix<double, DOF, 1> mForceLowerLimits;

  /// Max value allowed.
  Eigen::Matrix<double, DOF, 1> mForceUpperLimits;

  /// Derivatives w.r.t. an arbitrary scalr variable
  Eigen::Matrix<double, DOF, 1> mForcesDeriv;

  //----------------------------------------------------------------------------
  // Impulse
  //----------------------------------------------------------------------------

  /// Change of generalized velocity
  Eigen::Matrix<double, DOF, 1> mVelocityChanges;

  /// Generalized impulse
  Eigen::Matrix<double, DOF, 1> mImpulses;

  /// Generalized constraint impulse
  Eigen::Matrix<double, DOF, 1> mConstraintImpulses;

  //----------------------------------------------------------------------------
  // Spring and damper
  //----------------------------------------------------------------------------

  /// Joint spring stiffness
  Eigen::Matrix<double, DOF, 1> mSpringStiffness;

  /// Rest joint position for joint spring
  Eigen::Matrix<double, DOF, 1> mRestPosition;

  /// Joint damping coefficient
  Eigen::Matrix<double, DOF, 1> mDampingCoefficient;

  //----------------------------------------------------------------------------
  // For recursive dynamics algorithms
  //----------------------------------------------------------------------------

  /// Spatial Jacobian expressed in the child body frame
  Eigen::Matrix<double, 6, DOF> mJacobian;

  /// Time derivative of spatial Jacobian expressed in the child body frame
  Eigen::Matrix<double, 6, DOF> mJacobianDeriv;

  /// Inverse of projected articulated inertia
  Eigen::Matrix<double, DOF, DOF> mInvProjArtInertia;

  /// Inverse of projected articulated inertia for implicit joint damping and
  /// spring forces
  Eigen::Matrix<double, DOF, DOF> mInvProjArtInertiaImplicit;

  /// Total force projected on joint space
  Eigen::Matrix<double, DOF, 1> mTotalForce;

  /// Total impluse projected on joint space
  Eigen::Matrix<double, DOF, 1> mTotalImpulse;

  //----------------------------------------------------------------------------
  // For equations of motion
  //----------------------------------------------------------------------------

  ///
  Eigen::Matrix<double, DOF, 1> mInvM_a;

  ///
  Eigen::Matrix<double, DOF, 1> mInvMassMatrixSegment;

private:
  //----------------------------------------------------------------------------
  /// \{ \name Recursive dynamics routines
  //----------------------------------------------------------------------------

  void addChildArtInertiaHDToTorqueType(
      Eigen::Matrix6d& _parentArtInertia,
      const Eigen::Matrix6d& _childArtInertia);

  void addChildArtInertiaHDToAccelerationType(
      Eigen::Matrix6d& _parentArtInertia,
      const Eigen::Matrix6d& _childArtInertia);

  void addChildArtInertiaImplicitHDToTorqueType(
      Eigen::Matrix6d& _parentArtInertia,
      const Eigen::Matrix6d& _childArtInertia);

  void addChildArtInertiaImplicitHDToAccelerationType(
      Eigen::Matrix6d& _parentArtInertia,
      const Eigen::Matrix6d& _childArtInertia);

  void updateInvProjArtInertiaHDTorqueType(
      const Eigen::Matrix6d& _artInertia);

  void updateInvProjArtInertiaHDAccelerationType(
      const Eigen::Matrix6d& _artInertia);

  void updateInvProjArtInertiaImplicitHDTorqueType(
      const Eigen::Matrix6d& _artInertia, double _timeStep);

  void updateInvProjArtInertiaImplicitHDAccelerationType(
      const Eigen::Matrix6d& _artInertia, double _timeStep);

  void addChildBiasForceHDToTorqueType(
      Eigen::Vector6d& _parentBiasForce,
      const Eigen::Matrix6d& _childArtInertia,
      const Eigen::Vector6d& _childBiasForce,
      const Eigen::Vector6d& _childPartialAcc);

  void addChildBiasForceHDToAccelerationType(
      Eigen::Vector6d& _parentBiasForce,
      const Eigen::Matrix6d& _childArtInertia,
      const Eigen::Vector6d& _childBiasForce,
      const Eigen::Vector6d& _childPartialAcc);

  void addChildBiasImpulseHDToTorqueType(
      Eigen::Vector6d& _parentBiasImpulse,
      const Eigen::Matrix6d& _childArtInertia,
      const Eigen::Vector6d& _childBiasImpulse);

  void addChildBiasImpulseHDToAccelerationType(
      Eigen::Vector6d& _parentBiasImpulse,
      const Eigen::Matrix6d& _childArtInertia,
      const Eigen::Vector6d& _childBiasImpulse);

  void updateTotalForceHDTorqueType(const Eigen::Vector6d& _bodyForce,
                                    double _timeStep);

  void updateTotalForceHDAccelerationType(const Eigen::Vector6d& _bodyForce,
                                          double _timeStep);

  void updateTotalImpulseHDTorqueType(
        const Eigen::Vector6d& _bodyImpulse);

  void updateTotalImpulseHDAccelerationType(
        const Eigen::Vector6d& _bodyImpulse);

  void updateAccelerationHDTorqueType(
        const Eigen::Matrix6d& _artInertia,
        const Eigen::Vector6d& _spatialAcc);

  void updateAccelerationHDAccelerationType(
        const Eigen::Matrix6d& _artInertia,
        const Eigen::Vector6d& _spatialAcc);

  void updateVelocityChangeHDTorqueType(
        const Eigen::Matrix6d& _artInertia,
        const Eigen::Vector6d& _velocityChange);

  void updateVelocityChangeHDAccelerationType(
        const Eigen::Matrix6d& _artInertia,
        const Eigen::Vector6d& _velocityChange);

  void updateConstrainedTermsHDTorqueType(double _timeStep);

  void updateConstrainedTermsHDAccelerationType(double _timeStep);

  /// \}
};

//==============================================================================
template <size_t DOF>
MultiDofJoint<DOF>::MultiDofJoint(const std::string& _name)
  : Joint(_name),
    mIndexInSkeleton(Eigen::Matrix<size_t, DOF, 1>::Constant(0u)),
    mCommands(Eigen::Matrix<double, DOF, 1>::Constant(0.0)),
    mPositions(Eigen::Matrix<double, DOF, 1>::Constant(0.0)),
    mPositionLowerLimits(Eigen::Matrix<double, DOF, 1>::Constant(-DART_DBL_INF)),
    mPositionUpperLimits(Eigen::Matrix<double, DOF, 1>::Constant(DART_DBL_INF)),
    mPositionDeriv(Eigen::Matrix<double, DOF, 1>::Constant(0.0)),
    mVelocities(Eigen::Matrix<double, DOF, 1>::Constant(0.0)),
    mVelocityLowerLimits(Eigen::Matrix<double, DOF, 1>::Constant(-DART_DBL_INF)),
    mVelocityUpperLimits(Eigen::Matrix<double, DOF, 1>::Constant(DART_DBL_INF)),
    mVelocitiesDeriv(Eigen::Matrix<double, DOF, 1>::Constant(0.0)),
    mAccelerations(Eigen::Matrix<double, DOF, 1>::Constant(0.0)),
    mAccelerationLowerLimits(Eigen::Matrix<double, DOF, 1>::Constant(-DART_DBL_INF)),
    mAccelerationUpperLimits(Eigen::Matrix<double, DOF, 1>::Constant(DART_DBL_INF)),
    mAccelerationsDeriv(Eigen::Matrix<double, DOF, 1>::Constant(0.0)),
    mForces(Eigen::Matrix<double, DOF, 1>::Constant(0.0)),
    mForceLowerLimits(Eigen::Matrix<double, DOF, 1>::Constant(-DART_DBL_INF)),
    mForceUpperLimits(Eigen::Matrix<double, DOF, 1>::Constant(DART_DBL_INF)),
    mForcesDeriv(Eigen::Matrix<double, DOF, 1>::Constant(0.0)),
    mVelocityChanges(Eigen::Matrix<double, DOF, 1>::Constant(0.0)),
    mImpulses(Eigen::Matrix<double, DOF, 1>::Constant(0.0)),
    mConstraintImpulses(Eigen::Matrix<double, DOF, 1>::Constant(0.0)),
    mSpringStiffness(Eigen::Matrix<double, DOF, 1>::Constant(0.0)),
    mRestPosition(Eigen::Matrix<double, DOF, 1>::Constant(0.0)),
    mDampingCoefficient(Eigen::Matrix<double, DOF, 1>::Constant(0.0)),
    mJacobian(Eigen::Matrix<double, 6, DOF>::Zero()),
    mJacobianDeriv(Eigen::Matrix<double, 6, DOF>::Zero()),
    mInvProjArtInertia(Eigen::Matrix<double, DOF, DOF>::Zero()),
    mInvProjArtInertiaImplicit(Eigen::Matrix<double, DOF, DOF>::Zero()),
    mTotalForce(Eigen::Matrix<double, DOF, 1>::Zero()),
    mTotalImpulse(Eigen::Matrix<double, DOF, 1>::Zero())
{
}

//==============================================================================
template <size_t DOF>
MultiDofJoint<DOF>::~MultiDofJoint()
{
}

//==============================================================================
template <size_t DOF>
size_t MultiDofJoint<DOF>::getDof() const
{
  return getNumDofs();
}

//==============================================================================
template <size_t DOF>
size_t MultiDofJoint<DOF>::getNumDofs() const
{
  return DOF;
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setIndexInSkeleton(size_t _index,
                                            size_t _indexInSkeleton)
{
  if (_index >= getNumDofs())
  {
    dterr << "setIndexInSkeleton index[" << _index << "] out of range"
          << std::endl;
    return;
  }

  mIndexInSkeleton[_index] = _indexInSkeleton;
}

//==============================================================================
template <size_t DOF>
size_t MultiDofJoint<DOF>::getIndexInSkeleton(size_t _index) const
{
  if (_index >= getNumDofs())
  {
    dterr << "getIndexInSkeleton index[" << _index << "] out of range"
          << std::endl;
    return 0;
  }

  return mIndexInSkeleton[_index];
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setCommand(size_t _index, double _position)
{
  if (_index >= getNumDofs())
  {
    dterr << "[MultiDofJoint::setCommand]: index[" << _index << "] out of range"
          << std::endl;
    return;
  }

  mCommands[_index] = _position;
}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getCommand(size_t _index) const
{
  if (_index >= getNumDofs())
  {
    dterr << "[MultiDofJoint::getCommand]: index[" << _index << "] out of range"
          << std::endl;
    return 0.0;
  }

  return mCommands[_index];
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setCommands(const Eigen::VectorXd& _commands)
{
  if (static_cast<size_t>(_commands.size()) != getNumDofs())
  {
    dterr << "[MultiDofJoint::setCommands]: commands's size["
          << _commands.size() << "] is different with the dof ["
          << getNumDofs() << "]" << std::endl;
    return;
  }

  mCommands = _commands;
}

//==============================================================================
template <size_t DOF>
Eigen::VectorXd MultiDofJoint<DOF>::getCommands() const
{
  return mCommands;
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::resetCommands()
{
  mCommands.setZero();
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setPosition(size_t _index, double _position)
{
  if (_index >= getNumDofs())
  {
    dterr << "setPosition index[" << _index << "] out of range" << std::endl;
    return;
  }

  mPositions[_index] = _position;
}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getPosition(size_t _index) const
{
  if (_index >= getNumDofs())
  {
    dterr << "setPosition index[" << _index << "] out of range" << std::endl;
    return 0.0;
  }

  return mPositions[_index];
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setPositions(const Eigen::VectorXd& _positions)
{
  if (static_cast<size_t>(_positions.size()) != getNumDofs())
  {
    dterr << "setPositions positions's size[" << _positions.size()
          << "] is different with the dof [" << getNumDofs() << "]" << std::endl;
    return;
  }

  mPositions = _positions;
}

//==============================================================================
template <size_t DOF>
Eigen::VectorXd MultiDofJoint<DOF>::getPositions() const
{
  return mPositions;
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::resetPositions()
{
  mPositions.setZero();
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setPositionLowerLimit(size_t _index, double _position)
{
  if (_index >= getNumDofs())
  {
    dterr << "setPositionLowerLimit index[" << _index << "] out of range"
          << std::endl;
    return;
  }

  mPositionLowerLimits[_index] = _position;
}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getPositionLowerLimit(size_t _index) const
{
  if (_index >= getNumDofs())
  {
    dterr << "getPositionLowerLimit index[" << _index << "] out of range"
          << std::endl;
    return 0.0;
  }

  return mPositionLowerLimits[_index];
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setPositionUpperLimit(size_t _index, double _position)
{
  if (_index >= getNumDofs())
  {
    dterr << "setPositionUpperLimit index[" << _index << "] out of range"
          << std::endl;
    return;
  }

  mPositionUpperLimits[_index] = _position;
}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getPositionUpperLimit(size_t _index) const
{
  if (_index >= getNumDofs())
  {
    dterr << "getPositionUpperLimit index[" << _index << "] out of range"
          << std::endl;
    return 0.0;
  }

  return mPositionUpperLimits[_index];
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setVelocity(size_t _index, double _velocity)
{
  if (_index >= getNumDofs())
  {
    dterr << "setVelocity index[" << _index << "] out of range" << std::endl;
    return;
  }

  mVelocities[_index] = _velocity;
}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getVelocity(size_t _index) const
{
  if (_index >= getNumDofs())
  {
    dterr << "getVelocity index[" << _index << "] out of range" << std::endl;
    return 0.0;
  }

  return mVelocities[_index];
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setVelocities(const Eigen::VectorXd& _velocities)
{
  if (static_cast<size_t>(_velocities.size()) != getNumDofs())
  {
    dterr << "setVelocities velocities's size[" << _velocities.size()
          << "] is different with the dof [" << getNumDofs() << "]" << std::endl;
    return;
  }

  mVelocities = _velocities;
}

//==============================================================================
template <size_t DOF>
Eigen::VectorXd MultiDofJoint<DOF>::getVelocities() const
{
  return mVelocities;
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::resetVelocities()
{
  mVelocities.setZero();
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setVelocityLowerLimit(size_t _index, double _velocity)
{
  if (_index >= getNumDofs())
  {
    dterr << "setVelocityLowerLimit index[" << _index << "] out of range"
          << std::endl;
    return;
  }

  mVelocityLowerLimits[_index] = _velocity;
}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getVelocityLowerLimit(size_t _index) const
{
  if (_index >= getNumDofs())
  {
    dterr << "getVelocityLowerLimit index[" << _index << "] out of range"
          << std::endl;
    return 0.0;
  }

  return mVelocityLowerLimits[_index];
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setVelocityUpperLimit(size_t _index, double _velocity)
{
  if (_index >= getNumDofs())
  {
    dterr << "setVelocityUpperLimit index[" << _index << "] out of range"
          << std::endl;
    return;
  }

  mVelocityUpperLimits[_index] = _velocity;
}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getVelocityUpperLimit(size_t _index) const
{
  if (_index >= getNumDofs())
  {
    dterr << "getVelocityUpperLimit index[" << _index << "] out of range"
          << std::endl;
    return 0.0;
  }

  return mVelocityUpperLimits[_index];
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setAcceleration(size_t _index, double _acceleration)
{
  if (_index >= getNumDofs())
  {
    dterr << "setAcceleration index[" << _index << "] out of range"
          << std::endl;
    return;
  }

  mAccelerations[_index] = _acceleration;

#if DART_MAJOR_VERSION == 4
  if (mActuatorType == ACCELERATION)
    mCommands[_index] = mAccelerations[_index];
#endif
  // TODO: Remove at DART 5.0.
}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getAcceleration(size_t _index) const
{
  if (_index >= getNumDofs())
  {
    dterr << "getAcceleration index[" << _index << "] out of range"
          << std::endl;
    return 0.0;
  }

  return mAccelerations[_index];
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setAccelerations(const Eigen::VectorXd& _accelerations)
{
  if (static_cast<size_t>(_accelerations.size()) != getNumDofs())
  {
    dterr << "setAccelerations accelerations's size[" << _accelerations.size()
          << "] is different with the dof [" << getNumDofs() << "]" << std::endl;
    return;
  }

  mAccelerations = _accelerations;

#if DART_MAJOR_VERSION == 4
  if (mActuatorType == ACCELERATION)
    mCommands = mAccelerations;
#endif
  // TODO: Remove at DART 5.0.
}

//==============================================================================
template <size_t DOF>
Eigen::VectorXd MultiDofJoint<DOF>::getAccelerations() const
{
  return mAccelerations;
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::resetAccelerations()
{
  mAccelerations.setZero();
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setAccelerationLowerLimit(size_t _index,
                                                   double _acceleration)
{
  if (_index >= getNumDofs())
  {
    dterr << "setAccelerationLowerLimit index[" << _index << "] out of range"
          << std::endl;
    return;
  }

  mAccelerationLowerLimits[_index] = _acceleration;
}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getAccelerationLowerLimit(size_t _index) const
{
  if (_index >= getNumDofs())
  {
    dterr << "getAccelerationLowerLimit index[" << _index << "] out of range"
          << std::endl;
    return 0.0;
  }

  return mAccelerationLowerLimits[_index];
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setAccelerationUpperLimit(size_t _index,
                                                   double _acceleration)
{
  if (_index >= getNumDofs())
  {
    dterr << "setAccelerationUpperLimit index[" << _index << "] out of range"
          << std::endl;
    return;
  }

  mAccelerationUpperLimits[_index] = _acceleration;
}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getAccelerationUpperLimit(size_t _index) const
{
  if (_index >= getNumDofs())
  {
    dterr << "getAccelerationUpperLimit index[" << _index << "] out of range"
          << std::endl;
    return 0.0;
  }

  return mAccelerationUpperLimits[_index];
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setForce(size_t _index, double _force)
{
  if (_index >= getNumDofs())
  {
    dterr << "setForce index[" << _index << "] out of range" << std::endl;
    return;
  }

  mForces[_index] = _force;

#if DART_MAJOR_VERSION == 4
  if (mActuatorType == TORQUE)
    mCommands[_index] = mForces[_index];
#endif
  // TODO: Remove at DART 5.0.
}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getForce(size_t _index)
{
  if (_index >= getNumDofs())
  {
    dterr << "getForce index[" << _index << "] out of range" << std::endl;
    return 0.0;
  }

  return mForces[_index];
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setForces(const Eigen::VectorXd& _forces)
{
  if (static_cast<size_t>(_forces.size()) != getNumDofs())
  {
    dterr << "setForces forces's size[" << _forces.size()
          << "] is different with the dof [" << getNumDofs() << "]" << std::endl;
    return;
  }

  mForces = _forces;

#if DART_MAJOR_VERSION == 4
  if (mActuatorType == TORQUE)
    mCommands = mForces;
#endif
  // TODO: Remove at DART 5.0.
}

//==============================================================================
template <size_t DOF>
Eigen::VectorXd MultiDofJoint<DOF>::getForces() const
{
  return mForces;
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::resetForces()
{
  mForces.setZero();
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setForceLowerLimit(size_t _index, double _force)
{
  if (_index >= getNumDofs())
  {
    dterr << "setForceLowerLimit index[" << _index << "] out of range"
          << std::endl;
    return;
  }

  mForceLowerLimits[_index] = _force;
}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getForceLowerLimit(size_t _index) const
{
  if (_index >= getNumDofs())
  {
    dterr << "getForceMin index[" << _index << "] out of range" << std::endl;
    return 0.0;
  }

  return mForceLowerLimits[_index];
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setForceUpperLimit(size_t _index, double _force)
{
  if (_index >= getNumDofs())
  {
    dterr << "setForceUpperLimit index[" << _index << "] out of range"
          << std::endl;
    return;
  }

  mForceUpperLimits[_index] = _force;
}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getForceUpperLimit(size_t _index) const
{
  if (_index >= getNumDofs())
  {
    dterr << "getForceUpperLimit index[" << _index << "] out of range"
          << std::endl;
    return 0.0;
  }

  return mForceUpperLimits[_index];
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setVelocityChange(size_t _index,
                                           double _velocityChange)
{
  if (_index >= getNumDofs())
  {
    dterr << "setVelocityChange index[" << _index << "] out of range"
          << std::endl;
    return;
  }

  mVelocityChanges[_index] = _velocityChange;
}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getVelocityChange(size_t _index) const
{
  if (_index >= getNumDofs())
  {
    dterr << "getVelocityChange index[" << _index << "] out of range"
          << std::endl;
    return 0.0;
  }

  return mVelocityChanges[_index];
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::resetVelocityChanges()
{
  mVelocityChanges.setZero();
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setConstraintImpulse(size_t _index, double _impulse)
{
  if (_index >= getNumDofs())
  {
    dterr << "setConstraintImpulse index[" << _index << "] out of range"
          << std::endl;
    return;
  }

  mConstraintImpulses[_index] = _impulse;
}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getConstraintImpulse(size_t _index) const
{
  if (_index >= getNumDofs())
  {
    dterr << "getConstraintImpulse index[" << _index << "] out of range"
          << std::endl;
    return 0.0;
  }

  return mConstraintImpulses[_index];
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::resetConstraintImpulses()
{
  mConstraintImpulses.setZero();
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::integratePositions(double _dt)
{
  mPositions += mVelocities * _dt;
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::integrateVelocities(double _dt)
{
  mVelocities += mAccelerations * _dt;
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setSpringStiffness(size_t _index, double _k)
{
  if (_index >= getNumDofs())
  {
    dterr << "setSpringStiffness index[" << _index << "] out of range\n";
    return;
  }

  assert(_k >= 0.0);

  mSpringStiffness[_index] = _k;
}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getSpringStiffness(size_t _index) const
{
  if (_index >= getNumDofs())
  {
    dterr << "getSpringStiffness index[" << _index << "] out of range\n";
    return 0.0;
  }

  return mSpringStiffness[_index];
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setRestPosition(size_t _index, double _q0)
{
  if (_index >= getNumDofs())
  {
    dterr << "setRestPosition index[" << _index << "] out of range\n";
    return;
  }

  if (mPositionLowerLimits[_index] > _q0 || mPositionUpperLimits[_index] < _q0)
  {
    dterr << "Rest position of joint[" << getName() << "], " << _q0
          << ", is out of the limit range["
          << mPositionLowerLimits[_index] << ", "
          << mPositionUpperLimits[_index] << "] in index[" << _index
          << "].\n";
    return;
  }

  mRestPosition[_index] = _q0;
}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getRestPosition(size_t _index) const
{
  if (_index >= getNumDofs())
  {
    dterr << "getRestPosition index[" << _index << "] out of range\n";
    return 0.0;
  }

  return mRestPosition[_index];
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setDampingCoefficient(size_t _index, double _d)
{
  if (_index >= getNumDofs())
  {
    dterr << "setDampingCoefficient index[" << _index << "] out of range\n";
    return;
  }

  assert(_d >= 0.0);

  mDampingCoefficient[_index] = _d;

}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getDampingCoefficient(size_t _index) const
{
  if (_index >= getNumDofs())
  {
    dterr << "getDampingCoefficient index[" << _index << "] out of range\n";
    return 0.0;
  }

  return mDampingCoefficient[_index];
}

//==============================================================================
template <size_t DOF>
double MultiDofJoint<DOF>::getPotentialEnergy() const
{
  // Spring energy
  Eigen::VectorXd displacement = mPositions - mRestPosition;
  double pe
      = 0.5 * displacement.dot(mSpringStiffness.asDiagonal() * displacement);

  return pe;
}

//==============================================================================
template <size_t DOF>
const math::Jacobian MultiDofJoint<DOF>::getLocalJacobian() const
{
  return mJacobian;
}

//==============================================================================
template <size_t DOF>
const math::Jacobian MultiDofJoint<DOF>::getLocalJacobianTimeDeriv() const
{
  return mJacobianDeriv;
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addVelocityTo(Eigen::Vector6d& _vel)
{
  // Add joint velocity to _vel
  _vel.noalias() += mJacobian * mVelocities;

  // Verification
  assert(!math::isNan(_vel));
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::setPartialAccelerationTo(
    Eigen::Vector6d& _partialAcceleration,
    const Eigen::Vector6d& _childVelocity)
{
  // ad(V, S * dq)
  _partialAcceleration = math::ad(_childVelocity, mJacobian * mVelocities);

  // Add joint acceleration
  _partialAcceleration.noalias() += mJacobianDeriv * mVelocities;

  // Verification
  assert(!math::isNan(_partialAcceleration));
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addAccelerationTo(Eigen::Vector6d& _acc)
{
  // Add joint acceleration to _acc
  _acc.noalias() += mJacobian * mAccelerations;

  // Verification
  assert(!math::isNan(_acc));
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addVelocityChangeTo(Eigen::Vector6d& _velocityChange)
{
  // Add joint velocity change to _velocityChange
  _velocityChange.noalias() += mJacobian * mVelocityChanges;

  // Verification
  assert(!math::isNan(_velocityChange));
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addChildArtInertiaFDTo(
    Eigen::Matrix6d& _parentArtInertia,
    const Eigen::Matrix6d& _childArtInertia)
{
  addChildArtInertiaHDToTorqueType(_parentArtInertia, _childArtInertia);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addChildArtInertiaHDTo(
    Eigen::Matrix6d& _parentArtInertia,
    const Eigen::Matrix6d& _childArtInertia)
{
  switch (mActuatorType)
  {
    case TORQUE:
    case PASSIVE:
    case SERVO:
      addChildArtInertiaHDToTorqueType(_parentArtInertia,
                                       _childArtInertia);
      break;
    case ACCELERATION:
      addChildArtInertiaHDToAccelerationType(_parentArtInertia,
                                             _childArtInertia);
      break;
    default:
      dterr << "Unsupported actuator type." << std::endl;
      break;
  }
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addChildArtInertiaHDToTorqueType(
    Eigen::Matrix6d& _parentArtInertia,
    const Eigen::Matrix6d& _childArtInertia)
{
  // Child body's articulated inertia
  Eigen::Matrix<double, 6, DOF> AIS = _childArtInertia * mJacobian;
  Eigen::Matrix6d PI = _childArtInertia;
  PI.noalias() -= AIS * mInvProjArtInertia * AIS.transpose();
  assert(!math::isNan(PI));

  // Add child body's articulated inertia to parent body's articulated inertia.
  // Note that mT should be updated.
  _parentArtInertia += math::transformInertia(mT.inverse(), PI);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addChildArtInertiaHDToAccelerationType(
    Eigen::Matrix6d& _parentArtInertia,
    const Eigen::Matrix6d& _childArtInertia)
{
  // Add child body's articulated inertia to parent body's articulated inertia.
  // Note that mT should be updated.
  _parentArtInertia += math::transformInertia(mT.inverse(), _childArtInertia);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addChildArtInertiaImplicitFDTo(
    Eigen::Matrix6d& _parentArtInertia,
    const Eigen::Matrix6d& _childArtInertia)
{
  addChildArtInertiaImplicitHDToTorqueType(_parentArtInertia,
                                            _childArtInertia);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addChildArtInertiaImplicitHDTo(
    Eigen::Matrix6d& _parentArtInertia,
    const Eigen::Matrix6d& _childArtInertia)
{
  switch (mActuatorType)
  {
    case TORQUE:
    case PASSIVE:
    case SERVO:
      addChildArtInertiaImplicitHDToTorqueType(_parentArtInertia,
                                                _childArtInertia);
      break;
    case ACCELERATION:
      addChildArtInertiaImplicitHDToAccelerationType(_parentArtInertia,
                                                _childArtInertia);
      break;
    default:
      dterr << "Unsupported actuator type." << std::endl;
      break;
  }
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addChildArtInertiaImplicitHDToTorqueType(
    Eigen::Matrix6d& _parentArtInertia,
    const Eigen::Matrix6d& _childArtInertia)
{
  // Child body's articulated inertia
  Eigen::Matrix<double, 6, DOF> AIS = _childArtInertia * mJacobian;
  Eigen::Matrix6d PI = _childArtInertia;
  PI.noalias() -= AIS * mInvProjArtInertiaImplicit * AIS.transpose();
  assert(!math::isNan(PI));

  // Add child body's articulated inertia to parent body's articulated inertia.
  // Note that mT should be updated.
  _parentArtInertia += math::transformInertia(mT.inverse(), PI);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addChildArtInertiaImplicitHDToAccelerationType(
    Eigen::Matrix6d& _parentArtInertia,
    const Eigen::Matrix6d& _childArtInertia)
{
  // Add child body's articulated inertia to parent body's articulated inertia.
  // Note that mT should be updated.
  _parentArtInertia += math::transformInertia(mT.inverse(), _childArtInertia);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateInvProjArtInertiaFD(
    const Eigen::Matrix6d& _artInertia)
{
  updateInvProjArtInertiaHDTorqueType(_artInertia);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateInvProjArtInertiaHD(
    const Eigen::Matrix6d& _artInertia)
{
  switch (mActuatorType)
  {
    case TORQUE:
    case PASSIVE:
    case SERVO:
      updateInvProjArtInertiaHDTorqueType(_artInertia);
      break;
    case ACCELERATION:
      updateInvProjArtInertiaHDAccelerationType(_artInertia);
      break;
    default:
      dterr << "Unsupported actuator type." << std::endl;
      break;
  }
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateInvProjArtInertiaHDTorqueType(
    const Eigen::Matrix6d& _artInertia)
{
  // Projected articulated inertia
  const Eigen::Matrix<double, DOF, DOF> projAI
      = mJacobian.transpose() * _artInertia * mJacobian;

  // Inversion of projected articulated inertia
  //mInvProjArtInertia = projAI.inverse();
  mInvProjArtInertia
      = projAI.ldlt().solve(Eigen::Matrix<double, DOF, DOF>::Identity());

  // Verification
  assert(!math::isNan(mInvProjArtInertia));
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateInvProjArtInertiaHDAccelerationType(
    const Eigen::Matrix6d& /*_artInertia*/)
{
  // Do nothing
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateInvProjArtInertiaImplicitFD(
    const Eigen::Matrix6d& _artInertia,
    double _timeStep)
{
  updateInvProjArtInertiaImplicitHDTorqueType(_artInertia, _timeStep);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateInvProjArtInertiaImplicitHD(
    const Eigen::Matrix6d& _artInertia,
    double _timeStep)
{
  switch (mActuatorType)
  {
    case TORQUE:
    case PASSIVE:
    case SERVO:
      updateInvProjArtInertiaImplicitHDTorqueType(_artInertia, _timeStep);
      break;
    case ACCELERATION:
      updateInvProjArtInertiaImplicitHDAccelerationType(_artInertia, _timeStep);
      break;
    default:
      dterr << "Unsupported actuator type." << std::endl;
      break;
  }
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateInvProjArtInertiaImplicitHDTorqueType(
    const Eigen::Matrix6d& _artInertia,
    double _timeStep)
{
  // Projected articulated inertia
  Eigen::Matrix<double, DOF, DOF> projAI
      = mJacobian.transpose() * _artInertia * mJacobian;

  // Add additional inertia for implicit damping and spring force
  for (size_t i = 0; i < DOF; ++i)
  {
    projAI(i, i) += _timeStep * mDampingCoefficient[i]
        + _timeStep * _timeStep * mSpringStiffness[i];
  }

  // Inversion of projected articulated inertia
  //    mInvProjArtInertiaImplicit = projAI.inverse();
  mInvProjArtInertiaImplicit
      = projAI.ldlt().solve(Eigen::Matrix<double, DOF, DOF>::Identity());

  // Verification
  assert(!math::isNan(mInvProjArtInertiaImplicit));
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateInvProjArtInertiaImplicitHDAccelerationType(
    const Eigen::Matrix6d& _artInertia,
    double _timeStep)
{
  // Do nothing
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addChildBiasForceFDTo(
    Eigen::Vector6d& _parentBiasForce,
    const Eigen::Matrix6d& _childArtInertia,
    const Eigen::Vector6d& _childBiasForce,
    const Eigen::Vector6d& _childPartialAcc)
{
  addChildBiasForceHDToTorqueType(_parentBiasForce,
                                   _childArtInertia,
                                   _childBiasForce,
                                   _childPartialAcc);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addChildBiasForceHDTo(
    Eigen::Vector6d& _parentBiasForce,
    const Eigen::Matrix6d& _childArtInertia,
    const Eigen::Vector6d& _childBiasForce,
    const Eigen::Vector6d& _childPartialAcc)
{
  switch (mActuatorType)
  {
    case TORQUE:
    case PASSIVE:
    case SERVO:
      addChildBiasForceHDToTorqueType(_parentBiasForce,
                                       _childArtInertia,
                                       _childBiasForce,
                                       _childPartialAcc);
      break;
    case ACCELERATION:
      addChildBiasForceHDToAccelerationType(_parentBiasForce,
                                             _childArtInertia,
                                             _childBiasForce,
                                             _childPartialAcc);
      break;
    default:
      dterr << "Unsupported actuator type." << std::endl;
      break;
  }
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addChildBiasForceHDToTorqueType(
    Eigen::Vector6d& _parentBiasForce,
    const Eigen::Matrix6d& _childArtInertia,
    const Eigen::Vector6d& _childBiasForce,
    const Eigen::Vector6d& _childPartialAcc)
{
  // Compute beta
  const Eigen::Vector6d beta
      = _childBiasForce
        + _childArtInertia
          * (_childPartialAcc
             + mJacobian*mInvProjArtInertiaImplicit*mTotalForce);

  //    Eigen::Vector6d beta
  //        = _childBiasForce;
  //    beta.noalias() += _childArtInertia * _childPartialAcc;
  //    beta.noalias() += _childArtInertia *  mJacobian * mInvProjArtInertiaImplicit * mTotalForce;

  // Verification
  assert(!math::isNan(beta));

  // Add child body's bias force to parent body's bias force. Note that mT
  // should be updated.
  _parentBiasForce += math::dAdInvT(mT, beta);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addChildBiasForceHDToAccelerationType(
    Eigen::Vector6d& _parentBiasForce,
    const Eigen::Matrix6d& _childArtInertia,
    const Eigen::Vector6d& _childBiasForce,
    const Eigen::Vector6d& _childPartialAcc)
{
  // Compute beta
  const Eigen::Vector6d beta
      = _childBiasForce
        + _childArtInertia*(_childPartialAcc + mJacobian*mAccelerations);

  //    Eigen::Vector6d beta
  //        = _childBiasForce;
  //    beta.noalias() += _childArtInertia * _childPartialAcc;
  //    beta.noalias() += _childArtInertia *  mJacobian * mInvProjArtInertiaImplicit * mTotalForce;

  // Verification
  assert(!math::isNan(beta));

  // Add child body's bias force to parent body's bias force. Note that mT
  // should be updated.
  _parentBiasForce += math::dAdInvT(mT, beta);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addChildBiasImpulseFDTo(
    Eigen::Vector6d& _parentBiasImpulse,
    const Eigen::Matrix6d& _childArtInertia,
    const Eigen::Vector6d& _childBiasImpulse)
{
  addChildBiasImpulseHDToTorqueType(_parentBiasImpulse,
                                    _childArtInertia,
                                    _childBiasImpulse);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addChildBiasImpulseHDTo(
    Eigen::Vector6d& _parentBiasImpulse,
    const Eigen::Matrix6d& _childArtInertia,
    const Eigen::Vector6d& _childBiasImpulse)
{
  switch (mActuatorType)
  {
    case TORQUE:
    case PASSIVE:
    case SERVO:
      addChildBiasImpulseHDToTorqueType(_parentBiasImpulse,
                                        _childArtInertia,
                                        _childBiasImpulse);
      break;
    case ACCELERATION:
      addChildBiasImpulseHDToAccelerationType(_parentBiasImpulse,
                                              _childArtInertia,
                                              _childBiasImpulse);
      break;
    default:
      dterr << "Unsupported actuator type." << std::endl;
      break;
  }
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addChildBiasImpulseHDToTorqueType(
    Eigen::Vector6d& _parentBiasImpulse,
    const Eigen::Matrix6d& _childArtInertia,
    const Eigen::Vector6d& _childBiasImpulse)
{
  // Compute beta
  const Eigen::Vector6d beta
      = _childBiasImpulse
        + _childArtInertia*mJacobian*mInvProjArtInertia*mTotalImpulse;

  // Verification
  assert(!math::isNan(beta));

  // Add child body's bias force to parent body's bias force. Note that mT
  // should be updated.
  _parentBiasImpulse += math::dAdInvT(mT, beta);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addChildBiasImpulseHDToAccelerationType(
    Eigen::Vector6d& _parentBiasImpulse,
    const Eigen::Matrix6d& _childArtInertia,
    const Eigen::Vector6d& _childBiasImpulse)
{
  // Add child body's bias force to parent body's bias force. Note that mT
  // should be updated.
  _parentBiasImpulse += math::dAdInvT(mT, _childBiasImpulse);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateTotalForceFD(
    const Eigen::Vector6d& _bodyForce,
    double _timeStep)
{
  updateTotalForceHDTorqueType(_bodyForce, _timeStep);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateTotalForceHD(
    const Eigen::Vector6d& _bodyForce,
    double _timeStep)
{
  switch (mActuatorType)
  {
    case TORQUE:
      mForces = mCommands;
      updateTotalForceHDTorqueType(_bodyForce, _timeStep);
      break;
    case PASSIVE:
    case SERVO:
      mForces.setZero();
      updateTotalForceHDTorqueType(_bodyForce, _timeStep);
      break;
    case ACCELERATION:
      mAccelerations = mCommands;
      updateTotalForceHDAccelerationType(_bodyForce, _timeStep);
      break;
    default:
      dterr << "Unsupported actuator type." << std::endl;
      break;
  }
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateTotalForceHDTorqueType(
    const Eigen::Vector6d& _bodyForce,
    double _timeStep)
{
  // Spring force
  const Eigen::Matrix<double, DOF, 1> springForce
      = (-mSpringStiffness).asDiagonal()
        *(mPositions - mRestPosition + mVelocities*_timeStep);

  // Damping force
  const Eigen::Matrix<double, DOF, 1> dampingForce
      = (-mDampingCoefficient).asDiagonal()*mVelocities;

  //
  mTotalForce = mForces + springForce + dampingForce;
  mTotalForce.noalias() -= mJacobian.transpose()*_bodyForce;
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateTotalForceHDAccelerationType(
    const Eigen::Vector6d& _bodyForce,
    double _timeStep)
{
  // Do nothing
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateTotalImpulseFD(
    const Eigen::Vector6d& _bodyImpulse)
{
  updateTotalImpulseHDTorqueType(_bodyImpulse);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateTotalImpulseHD(
    const Eigen::Vector6d& _bodyImpulse)
{
  switch (mActuatorType)
  {
    case TORQUE:
    case PASSIVE:
    case SERVO:
      updateTotalImpulseHDTorqueType(_bodyImpulse);
      break;
    case ACCELERATION:
      updateTotalImpulseHDAccelerationType(_bodyImpulse);
      break;
    default:
      dterr << "Unsupported actuator type." << std::endl;
      break;
  }
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateTotalImpulseHDTorqueType(
    const Eigen::Vector6d& _bodyImpulse)
{
  //
  mTotalImpulse = mConstraintImpulses;
  mTotalImpulse.noalias() -= mJacobian.transpose()*_bodyImpulse;
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateTotalImpulseHDAccelerationType(
    const Eigen::Vector6d& _bodyImpulse)
{
  // Do nothing
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::resetTotalImpulses()
{
  mTotalImpulse.setZero();
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateAccelerationFD(
    const Eigen::Matrix6d& _artInertia,
    const Eigen::Vector6d& _spatialAcc)
{
  updateAccelerationHDTorqueType(_artInertia, _spatialAcc);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateAccelerationHD(
    const Eigen::Matrix6d& _artInertia,
    const Eigen::Vector6d& _spatialAcc)
{
  switch (mActuatorType)
  {
    case TORQUE:
    case PASSIVE:
    case SERVO:
      updateAccelerationHDTorqueType(_artInertia, _spatialAcc);
      break;
    case ACCELERATION:
      updateAccelerationHDAccelerationType(_artInertia, _spatialAcc);
      break;
    default:
      dterr << "Unsupported actuator type." << std::endl;
      break;
  }
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateAccelerationHDTorqueType(
    const Eigen::Matrix6d& _artInertia,
    const Eigen::Vector6d& _spatialAcc)
{
  //
  mAccelerations
      = mInvProjArtInertiaImplicit
      * (mTotalForce - mJacobian.transpose()
         *_artInertia*math::AdInvT(mT, _spatialAcc));

  // Verification
  assert(!math::isNan(mAccelerations));
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateAccelerationHDAccelerationType(
    const Eigen::Matrix6d& _artInertia,
    const Eigen::Vector6d& _spatialAcc)
{
  // Do nothing
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateVelocityChangeFD(
    const Eigen::Matrix6d& _artInertia,
    const Eigen::Vector6d& _velocityChange)
{
  updateVelocityChangeHDTorqueType(_artInertia, _velocityChange);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateVelocityChangeHD(
    const Eigen::Matrix6d& _artInertia,
    const Eigen::Vector6d& _velocityChange)
{
  switch (mActuatorType)
  {
    case TORQUE:
    case PASSIVE:
    case SERVO:
      updateVelocityChangeHDTorqueType(_artInertia, _velocityChange);
      break;
    case ACCELERATION:
      updateVelocityChangeHDAccelerationType(_artInertia, _velocityChange);
      break;
    default:
      dterr << "Unsupported actuator type." << std::endl;
      break;
  }
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateVelocityChangeHDTorqueType(
    const Eigen::Matrix6d& _artInertia,
    const Eigen::Vector6d& _velocityChange)
{
  //
  mVelocityChanges
      = mInvProjArtInertia
      * (mTotalImpulse - mJacobian.transpose()
         *_artInertia*math::AdInvT(mT, _velocityChange));

  // Verification
  assert(!math::isNan(mVelocityChanges));
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateVelocityChangeHDAccelerationType(
    const Eigen::Matrix6d& _artInertia,
    const Eigen::Vector6d& _velocityChange)
{
  // Do nothing
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateForceID(const Eigen::Vector6d& _bodyForce,
                                       double _timeStep,
                                       bool _withDampingForces,
                                       bool _withSpringForces)
{
  mForces = mJacobian.transpose()*_bodyForce;

  // Damping force
  if (_withDampingForces)
  {
    const Eigen::Matrix<double, DOF, 1> dampingForces
        = (-mDampingCoefficient).asDiagonal()*mVelocities;
    mForces -= dampingForces;
  }

  // Spring force
  if (_withSpringForces)
  {
    const Eigen::Matrix<double, DOF, 1> springForces
        = (-mSpringStiffness).asDiagonal()
          *(mPositions - mRestPosition + mVelocities*_timeStep);
    mForces -= springForces;
  }
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateForceHD(const Eigen::Vector6d& _bodyForce,
                                       double _timeStep,
                                       bool _withDampingForces,
                                       bool _withSpringForces)
{
  switch (mActuatorType)
  {
    case TORQUE:
    case PASSIVE:
    case SERVO:
      break;
    case ACCELERATION:
      updateForceID(_bodyForce, _timeStep, _withDampingForces,
                    _withSpringForces);
      break;
    default:
      dterr << "Unsupported actuator type." << std::endl;
      break;
  }
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateImpulseID(const Eigen::Vector6d& _bodyImpulse)
{
  mImpulses = mJacobian.transpose()*_bodyImpulse;
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateImpulseHD(const Eigen::Vector6d& _bodyImpulse)
{
  switch (mActuatorType)
  {
    case TORQUE:
    case PASSIVE:
    case SERVO:
      break;
    case ACCELERATION:
      updateImpulseID(_bodyImpulse);
      break;
    default:
      dterr << "Unsupported actuator type." << std::endl;
      break;
  }
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateConstrainedTermsFD(double _timeStep)
{
  updateConstrainedTermsHDTorqueType(_timeStep);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateConstrainedTermsHD(double _timeStep)
{
  switch (mActuatorType)
  {
    case TORQUE:
    case PASSIVE:
    case SERVO:
      updateConstrainedTermsHDTorqueType(_timeStep);
      break;
    case ACCELERATION:
      updateConstrainedTermsHDAccelerationType(_timeStep);
      break;
    default:
      dterr << "Unsupported actuator type." << std::endl;
      break;
  }
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateConstrainedTermsHDTorqueType(double _timeStep)
{
  const double invTimeStep = 1.0 / _timeStep;

  mVelocities += mVelocityChanges;
  mAccelerations.noalias() += mVelocityChanges*invTimeStep;
  mForces.noalias() += mImpulses*invTimeStep;
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateConstrainedTermsHDAccelerationType(
    double _timeStep)
{
  mForces.noalias() += mImpulses / _timeStep;
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addChildBiasForceForInvMassMatrix(
    Eigen::Vector6d& _parentBiasForce,
    const Eigen::Matrix6d& _childArtInertia,
    const Eigen::Vector6d& _childBiasForce)
{
  // Compute beta
  Eigen::Vector6d beta = _childBiasForce;
  beta.noalias() += _childArtInertia * mJacobian * mInvProjArtInertia
      * mInvM_a;

  // Verification
  assert(!math::isNan(beta));

  // Add child body's bias force to parent body's bias force. Note that mT
  // should be updated.
  _parentBiasForce += math::dAdInvT(mT, beta);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addChildBiasForceForInvAugMassMatrix(
    Eigen::Vector6d& _parentBiasForce,
    const Eigen::Matrix6d& _childArtInertia,
    const Eigen::Vector6d& _childBiasForce)
{
  // Compute beta
  Eigen::Vector6d beta = _childBiasForce;
  beta.noalias() += _childArtInertia * mJacobian * mInvProjArtInertiaImplicit
      * mInvM_a;

  // Verification
  assert(!math::isNan(beta));

  // Add child body's bias force to parent body's bias force. Note that mT
  // should be updated.
  _parentBiasForce += math::dAdInvT(mT, beta);
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::updateTotalForceForInvMassMatrix(
    const Eigen::Vector6d& _bodyForce)
{
  // Compute alpha
  mInvM_a = mForces;
  mInvM_a.noalias() -= mJacobian.transpose() * _bodyForce;
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::getInvMassMatrixSegment(
    Eigen::MatrixXd& _invMassMat,
    const size_t _col,
    const Eigen::Matrix6d& _artInertia,
    const Eigen::Vector6d& _spatialAcc)
{
  //
  mInvMassMatrixSegment
      = mInvProjArtInertia
      * (mInvM_a - mJacobian.transpose()
         * _artInertia * math::AdInvT(mT, _spatialAcc));

  // Verification
  assert(!math::isNan(mInvMassMatrixSegment));

  // Index
  size_t iStart = mIndexInSkeleton[0];

  // Assign
  _invMassMat.block<DOF, 1>(iStart, _col) = mInvMassMatrixSegment;
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::getInvAugMassMatrixSegment(
    Eigen::MatrixXd& _invMassMat,
    const size_t _col,
    const Eigen::Matrix6d& _artInertia,
    const Eigen::Vector6d& _spatialAcc)
{
  //
  mInvMassMatrixSegment
      = mInvProjArtInertiaImplicit
      * (mInvM_a - mJacobian.transpose()
         * _artInertia * math::AdInvT(mT, _spatialAcc));

  // Verification
  assert(!math::isNan(mInvMassMatrixSegment));

  // Index
  size_t iStart = mIndexInSkeleton[0];

  // Assign
  _invMassMat.block<DOF, 1>(iStart, _col) = mInvMassMatrixSegment;
}

//==============================================================================
template <size_t DOF>
void MultiDofJoint<DOF>::addInvMassMatrixSegmentTo(Eigen::Vector6d& _acc)
{
  //
  _acc += mJacobian * mInvMassMatrixSegment;
}

//==============================================================================
template <size_t DOF>
Eigen::VectorXd MultiDofJoint<DOF>::getSpatialToGeneralized(
    const Eigen::Vector6d& _spatial)
{
  return mJacobian.transpose() * _spatial;
}

}  // namespace dynamics
}  // namespace dart

#endif  // DART_DYNAMICS_MULTIDOFJOINT_H_
