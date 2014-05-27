/*
 * Copyright (c) 2011-2013, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Sehoon Ha <sehoon.ha@gmail.com>
 *            Jeongseok Lee <jslee02@gmail.com>
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

#ifndef DART_DYNAMICS_JOINT_H_
#define DART_DYNAMICS_JOINT_H_

#include <string>
#include <vector>

#include "dart/math/Geometry.h"
#include "dart/dynamics/GenCoordSystem.h"

namespace dart {
namespace renderer {
class RenderInterface;
}  // namespace renderer
}  // namespace dart

namespace dart {
namespace dynamics {

class BodyNode;
class Skeleton;

/// Joint
class Joint : public GenCoordSystem
{
public:
  /// Constructor
  explicit Joint(const std::string& _name = "Noname Joint");

  /// Destructor
  virtual ~Joint();

  //------------------------------ Properties ----------------------------------
  /// Set joint name
  void setName(const std::string& _name);

  /// Get joint name
  const std::string& getName() const;

  /// Get skeleton that this joint belongs to. The skeleton set by init().
  Skeleton* getSkeleton() const;

  /// Get index of this joint in the skeleton that this joint belongs to
  int getSkeletonIndex() const;

  /// Set transformation from parent body node to this joint
  virtual void setTransformFromParentBodyNode(const Eigen::Isometry3d& _T);

  /// Set transformation from child body node to this joint
  virtual void setTransformFromChildBodyNode(const Eigen::Isometry3d& _T);

  /// Get transformation from parent body node to this joint
  const Eigen::Isometry3d& getTransformFromParentBodyNode() const;

  /// Get transformation from child body node to this joint
  const Eigen::Isometry3d& getTransformFromChildBodyNode() const;

  /// Set to enforce joint position limit
  void setPositionLimited(bool _isPositionLimited);

  /// Get whether enforcing joint position limit
  bool isPositionLimited() const;

  /// Set spring stiffness for spring force
  /// \param[in] _idx Index of joint axis
  /// \param[in] _k Spring stiffness
  void setSpringStiffness(int _idx, double _k);

  /// Get spring stiffnes for spring force
  /// \param[in] _idx Index of joint axis
  double getSpringStiffness(int _idx) const;

  /// Set rest position for spring force
  /// \param[in] _idx Index of joint axis
  /// \param[in] _q0 Rest position
  void setRestPosition(int _idx, double _q0);

  /// Get rest position for spring force
  /// \param[in] _idx Index of joint axis
  /// \return Rest position
  double getRestPosition(int _idx) const;

  /// Set damping coefficient for viscous force
  /// \param[in] _idx Index of joint axis
  /// \param[in] _d Damping coefficient
  void setDampingCoefficient(int _idx, double _d);

  /// Get damping coefficient for viscous force
  /// \param[in] _idx Index of joint axis
  double getDampingCoefficient(int _idx) const;

  //----------------- Interface for generalized coordinates --------------------
  /// Set single configuration in terms of generalized coordinates
  /// \param[in] _updateTransforms True to update transformations of body nodes
  /// \param[in] _updateVels True to update spacial velocities of body nodes
  /// \param[in] _updateAccs True to update spacial accelerations of body nodes
  virtual void setConfig(size_t _idx, double _config,
                         bool _updateTransforms = true,
                         bool _updateVels = false,
                         bool _updateAccs = false);

  /// Set configurations in terms of generalized coordinates
  /// \param[in] _updateTransforms True to update transformations of body nodes
  /// \param[in] _updateVels True to update spacial velocities of body nodes
  /// \param[in] _updateAccs True to update spacial accelerations of body nodes
  virtual void setConfigs(const Eigen::VectorXd& _configs,
                          bool _updateTransforms = true,
                          bool _updateVels = false,
                          bool _updateAccs = false);

  /// Set single generalized velocity
  /// \param[in] _updateVels True to update spacial velocities of body nodes
  /// \param[in] _updateAccs True to update spacial accelerations of body nodes
  virtual void setGenVel(size_t _idx, double _genVel,
                         bool _updateVels = true,
                         bool _updateAccs = false);

  /// Set generalized velocities
  /// \param[in] _updateVels True to update spacial velocities of body nodes
  /// \param[in] _updateAccs True to update spacial accelerations of body nodes
  virtual void setGenVels(const Eigen::VectorXd& _genVels,
                          bool _updateVels = true,
                          bool _updateAccs = false);

  /// Set single generalized acceleration
  /// \param[in] _updateAccs True to update spacial accelerations of body nodes
  virtual void setGenAcc(size_t _idx, double _genAcc,
                         bool _updateAccs );

  /// Set generalized accelerations
  /// \param[in] _updateAccs True to update spacial accelerations of body nodes
  virtual void setGenAccs(const Eigen::VectorXd& _genAccs,
                          bool _updateAccs);

  /// TODO(JS): Implementation
  virtual void setPosition(size_t _index, double _position) {}

  /// TODO(JS): Implementation
  virtual void setVelocity(size_t _index, double _velocity) {}

  /// TODO(JS): Implementation
  virtual void setAcceleration(size_t _index, double _acceleration) {}

  /// TODO(JS): Implementation
  virtual double getPosition(size_t _index) const {}

  /// TODO(JS): Implementation
  virtual double getVelocity(size_t _index) const {}

  /// TODO(JS): Implementation
  virtual double getAcceleration(size_t _index) const {}

  //----------------------------------------------------------------------------

  /// Get potential energy
  double getPotentialEnergy() const;

  /// Get transformation from parent body node to child body node
  const Eigen::Isometry3d& getLocalTransform() const;

  /// Get generalized Jacobian from parent body node to child body node
  /// w.r.t. local generalized coordinate
  DEPRECATED(4.0) virtual const math::Jacobian& getLocalJacobian() const;

  /// Get time derivative of generalized Jacobian from parent body node
  /// to child body node w.r.t. local generalized coordinate
  DEPRECATED(4.0) virtual const math::Jacobian& getLocalJacobianTimeDeriv() const;

  /// Get whether this joint contains _genCoord
  /// \param[in] Generalized coordinate to see
  /// \return True if this joint contains _genCoord
  bool contains(const GenCoord* _genCoord) const;

  /// Get local index of the dof at this joint; if the dof is not presented at
  /// this joint, return -1
  int getGenCoordLocalIndex(int _dofSkelIndex) const;

  /// Get constraint wrench expressed in body node frame
  virtual Eigen::Vector6d getBodyConstraintWrench() const = 0;

  /// Get spring force
  ///
  /// We apply spring force in implicit manner. The spring force is
  /// F = -(springStiffness * q(k+1)), where q(k+1) is approximated as
  /// q(k) + h * dq(k) * h^2 * ddq(k). Since, in the recursive forward dynamics
  /// algorithm, ddq(k) is unknown variable that we want to obtain as the
  /// result, the spring force here is just
  /// F = -springStiffness * (q(k) + h * dq(k)) and
  /// -springStiffness * h^2 * ddq(k) term is rearranged at the recursive
  /// forward dynamics algorithm, and it affects on the articulated inertia.
  /// \sa BodyNode::updateArticulatedInertia(double).
  ///
  /// \param[in] _timeStep Time step used for approximating q(k+1).
  Eigen::VectorXd getSpringForces(double _timeStep) const;

  /// Get damping force
  ///
  /// We apply the damping force in implicit manner. The damping force is
  /// F = -(dampingCoefficient * dq(k+1)), where dq(k+1) is approximated as
  /// dq(k) + h * ddq(k). Since, in the recursive forward dynamics algorithm,
  /// ddq(k) is unknown variable that we want to obtain as the result, the
  /// damping force here is just F = -(dampingCoefficient * dq(k)) and
  /// -dampingCoefficient * h * ddq(k) term is rearranged at the recursive
  /// forward dynamics algorithm, and it affects on the articulated inertia.
  /// \sa BodyNode::updateArticulatedInertia(double).
  Eigen::VectorXd getDampingForces() const;

  //----------------------------------------------------------------------------
  // Rendering
  //----------------------------------------------------------------------------

  ///
  void applyGLTransform(renderer::RenderInterface* _ri);

  //----------------------------------------------------------------------------
  // Friendship
  //----------------------------------------------------------------------------

  friend class BodyNode;
  friend class SoftBodyNode;
  friend class Skeleton;

protected:
  /// Initialize this joint. This function is called by BodyNode::init()
  virtual void init(Skeleton* _skel, int _skelIdx);

  //----------------------------------------------------------------------------
  // Recursive algorithms
  //----------------------------------------------------------------------------

  /// Update transformation from parent body node to child body node
  virtual void updateLocalTransform() = 0;

  /// Update generalized Jacobian from parent body node to child body node
  /// w.r.t. local generalized coordinate
  virtual void updateLocalJacobian() = 0;

  /// Update time derivative of generalized Jacobian from parent body node to
  /// child body node w.r.t. local generalized coordinate
  virtual void updateLocalJacobianTimeDeriv() = 0;

  ///
  virtual void addVelocityTo(Eigen::Vector6d& _vel) = 0;

  /// Set partial
  virtual void setPartialAccelerationTo(
      Eigen::Vector6d& _partialAcceleration,
      const Eigen::Vector6d& _childVelocity) = 0;

  ///
  virtual void addAccelerationTo(Eigen::Vector6d& _acc) = 0;

  ///
  virtual void addVelocityChangeTo(Eigen::Vector6d& _velocityChange) = 0;

  /// Add child's articulated inertia to parent's one
  virtual void addChildArtInertiaTo(Eigen::Matrix6d& _parentArtInertia,
                                    const Eigen::Matrix6d& _childArtInertia) = 0;

  /// Add child's articulated inertia to parent's one
  virtual void addChildArtInertiaImplicitTo(
      Eigen::Matrix6d& _parentArtInertiaImplicit,
      const Eigen::Matrix6d& _childArtInertiaImplicit) = 0;

  /// Update inverse of projected articulated body inertia
  virtual void updateInvProjArtInertia(const Eigen::Matrix6d& _artInertia) = 0;

  /// Update inverse of projected articulated body inertia with implicit damping
  /// and spring forces
  virtual void updateInvProjArtInertiaImplicit(
      const Eigen::Matrix6d& _artInertia,
      double _timeStep) = 0;

  /// Add child's bias force to parent's one
  virtual void addChildBiasForceTo(Eigen::Vector6d& _parentBiasForce,
                                   const Eigen::Matrix6d& _childArtInertia,
                                   const Eigen::Vector6d& _childBiasForce,
                                   const Eigen::Vector6d& _childPartialAcc) = 0;

  /// Add child's bias impulse to parent's one
  virtual void addChildBiasImpulseTo(Eigen::Vector6d& _parentBiasImpulse,
                                     const Eigen::Matrix6d& _childArtInertia,
                                     const Eigen::Vector6d& _childBiasImpulse)
  = 0;

  ///
  virtual void updateTotalForce(const Eigen::Vector6d& _bodyForce,
                                double _timeStep) = 0;

  ///
  virtual void updateTotalImpulse(const Eigen::Vector6d& _bodyImpulse) = 0;

  ///
  virtual void updateAcceleration(const Eigen::Matrix6d& _artInertia,
                                  const Eigen::Vector6d& _spatialAcc) = 0;

  ///
  virtual void updateVelocityChange(const Eigen::Matrix6d& _artInertia,
                                    const Eigen::Vector6d& _velocityChange) = 0;

  ///
  virtual void clearConstraintImpulse() = 0;

  //----------------------------------------------------------------------------
  // Recursive algorithms for equations of motion
  //----------------------------------------------------------------------------

  /// Add child's bias force to parent's one
  virtual void addChildBiasForceForInvMassMatrix(
      Eigen::Vector6d& _parentBiasForce,
      const Eigen::Matrix6d& _childArtInertia,
      const Eigen::Vector6d& _childBiasForce) = 0;

  /// Add child's bias force to parent's one
  virtual void addChildBiasForceForInvAugMassMatrix(
      Eigen::Vector6d& _parentBiasForce,
      const Eigen::Matrix6d& _childArtInertia,
      const Eigen::Vector6d& _childBiasForce) = 0;

  ///
  virtual void updateTotalForceForInvMassMatrix(
      const Eigen::Vector6d& _bodyForce) = 0;

  ///
  virtual void getInvMassMatrixSegment(Eigen::MatrixXd& _invMassMat,
                                       const size_t _col,
                                       const Eigen::Matrix6d& _artInertia,
                                       const Eigen::Vector6d& _spatialAcc) = 0;

  ///
  virtual void getInvAugMassMatrixSegment(Eigen::MatrixXd& _invMassMat,
                                       const size_t _col,
                                       const Eigen::Matrix6d& _artInertia,
                                       const Eigen::Vector6d& _spatialAcc) = 0;

  ///
  virtual void addInvMassMatrixSegmentTo(Eigen::Vector6d& _acc) = 0;

protected:
  /// Joint name
  std::string mName;

  /// Skeleton pointer that this joint belongs to
  Skeleton* mSkeleton;

  /// Unique dof id in skeleton
  int mSkelIndex;

  /// Transformation from parent body node to this joint
  Eigen::Isometry3d mT_ParentBodyToJoint;

  /// Transformation from child body node to this joint
  Eigen::Isometry3d mT_ChildBodyToJoint;

  /// Local transformation
  Eigen::Isometry3d mT;

  /// Relative spatial velocity from parent body to child body where the
  /// velocity is expressed in child body frame
  Eigen::Vector6d mSpatialVelocity;

  /// Time derivative of local Jacobian
  DEPRECATED(4.0) math::Jacobian mS;

  /// Time derivative of local Jacobian
  DEPRECATED(4.0) math::Jacobian mdS;

  // TODO(JS): Temporary code
public:
  /// Transmitting wrench from parent body to child body expressed in child body
  Eigen::Vector6d mWrench;

protected:
  /// True if the joint limits are enforced in dynamic simulation
  bool mIsPositionLimited;

  /// Joint spring stiffness
  std::vector<double> mSpringStiffness;

  /// Rest joint position for joint spring
  std::vector<double> mRestPosition;

  /// Joint damping coefficient
  std::vector<double> mDampingCoefficient;
};

}  // namespace dynamics
}  // namespace dart

#endif  // DART_DYNAMICS_JOINT_H_
