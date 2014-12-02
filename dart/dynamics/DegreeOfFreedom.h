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

#ifndef DART_DYNAMICS_DEGREEOFFREEDOM_H_
#define DART_DYNAMICS_DEGREEOFFREEDOM_H_

#include <string>
#include <Eigen/Core>

namespace dart {
namespace dynamics {

class Skeleton;
class Joint;
class BodyNode;

/// DegreeOfFreedom class is a proxy class for accessing single degrees of
/// freedom (or generalized coordinate) of the Skeleton.

class DegreeOfFreedom
{
public:

  friend class dart::dynamics::Joint;
  friend class dart::dynamics::Skeleton;

  /// Change the name of this DegreeOfFreedom
  const std::string& setName(const std::string& _name);

  /// Get the name of this DegreeOfFreedom
  const std::string& getName() const;

  /// Get this DegreeOfFreedom's index within its Skeleton
  size_t getIndexInSkeleton() const;

  /// Get this DegreeOfFreedom's index within its Joint
  size_t getIndexInJoint() const;

  // -- Position functions -----------------------------------------------------

  /// Set the position of this DegreeOfFreedom
  void setPosition(double _position);

  /// Get the position of this DegreeOfFreedom
  double getPosition() const;

  /// Set the position limits of this DegreeOfFreedom
  void setPositionLimits(double _lowerLimit, double _upperLimit);

  /// Set the position limits of this DegreeOfFreedom
  void setPositionLimits(const std::pair<double,double>& _limits);

  /// Get the position limits of this DegreeOfFreedom
  std::pair<double,double> getPositionLimits() const;

  /// Set the lower position limit of this DegreeOfFreedom
  void setPositionLowerLimit(double _limit);

  /// Get the lower position limit of this DegreeOfFreedom
  double getPositionLowerLimit() const;

  /// Set the upper position limit of this DegreeOfFreedom
  void setPositionUpperLimit(double _limit);

  /// Get the upper position limit of this DegreeOfFreedom
  double getPositionUpperLimit() const;

  // -- Velocity functions -----------------------------------------------------

  /// Set the velocity of this DegreeOfFreedom
  void setVelocity(double _velocity);

  /// Get the velocity of this DegreeOfFreedom
  double getVelocity() const;

  /// Set the velocity limits of this DegreeOfFreedom
  void setVelocityLimits(double _lowerLimit, double _upperLimit);

  /// Set the velocity limtis of this DegreeOfFreedom
  void setVelocityLimits(const std::pair<double,double>& _limits);

  /// Get the velocity limits of this DegreeOfFreedom
  std::pair<double,double> getVelocityLimits() const;

  /// Set the lower velocity limit of this DegreeOfFreedom
  void setVelocityLowerLimit(double _limit);

  /// Get the lower velocity limit of this DegreeOfFreedom
  double getVelocityLowerLimit() const;

  /// Set the upper velocity limit of this DegreeOfFreedom
  void setVelocityUpperLimit(double _limit);

  /// Get the upper Velocity limit of this DegreeOfFreedom
  double getVelocityUpperLimit() const;

  // -- Acceleration functions -------------------------------------------------

  /// Set the acceleration of this DegreeOfFreedom
  void setAcceleration(double _acceleration);

  /// Get the acceleration of this DegreeOfFreedom
  double getAcceleration() const;

  /// Set the acceleration limits of this DegreeOfFreedom
  void setAccelerationLimits(double _lowerLimit, double _upperLimit);

  /// Set the acceleartion limits of this DegreeOfFreedom
  void setAccelerationLimits(const std::pair<double,double>& _limits);

  /// Get the acceleration limits of this DegreeOfFreedom
  std::pair<double,double> getAccelerationLimits() const;

  /// Set the lower acceleration limit of this DegreeOfFreedom
  void setAccelerationLowerLimit(double _limit);

  /// Get the lower acceleration limit of this DegreeOfFreedom
  double getAccelerationLowerLimit() const;

  /// Set the upper acceleration limit of this DegreeOfFreedom
  void setAccelerationUpperLimit(double _limit);

  /// Get the upper acceleration limit of this DegreeOfFreedom
  double getAccelerationUpperLimit() const;

  // -- Effort/Force functions -------------------------------------------------
  // Note: In these functions, the word "Effort" is being used instead of
  // "Force". Currently "Force" is being used throughout DART to refer to the
  // Generalized Force of a Generalized Coordinate, but I propose we use the
  // word "Effort" instead. We can change the names of these functions later if
  // "Effort" is deemed inappropriate or undesirable.

  /// Set the generalized force of this DegreeOfFreedom
  void setEffort(double _effort);

  /// Get the generalized force of this DegreeOfFreedom
  double getEffort() const;

  /// Set the generalized force limits of this DegreeOfFreedom
  void setEffortLimits(double _lowerLimit, double _upperLimit);

  /// Set the generalized force limits of this DegreeOfFreedom
  void setEffortLimits(const std::pair<double,double>& _limits);

  /// Get the generalized force limits of this DegreeOfFreedom
  std::pair<double,double> getEffortLimits() const;

  /// Set the lower generalized force limit of this DegreeOfFreedom
  void setEffortLowerLimit(double _limit);

  /// Get the lower generalized force limit of this DegreeOfFreedom
  double getEffortLowerLimit() const;

  /// Set the upper generalized force limit of this DegreeOfFreedom
  void setEffortUpperLimit(double _limit);

  /// Get the upper generalized force limit of this DegreeOfFreedom
  double getEffortUpperLimit() const;

  // -- Relationships ----------------------------------------------------------

  /// Get the Joint that this DegreeOfFreedom belongs to
  Joint* getJoint();

  /// Get the Joint that this DegreeOfFreedom belongs to
  const Joint* getJoint() const;

  /// Get the Skeleton that this DegreeOfFreedom is inside of
  Skeleton* getSkeleton();

  /// Get the Skeleton that this DegreeOfFreedom is inside of
  const Skeleton* getSkeleton() const;

  /// Get the BodyNode downstream of this DegreeOfFreedom
  BodyNode* getChildBodyNode();

  /// Get the BodyNode downstream of this DegreeOfFreedom
  const BodyNode* getChildBodyNode() const;

  /// Get the BodyNode upstream of this DegreeOfFreedom
  BodyNode* getParentBodyNode();

  /// Get the BodyNode upstream of this DegreeOfFreedom
  const BodyNode* getParentBodyNode() const;

protected:

  /// The constructor is protected so that only Joints can create
  /// DegreeOfFreedom classes
  DegreeOfFreedom(Joint* _joint,
                  const std::string& _name,
                  size_t _indexInJoint);

  /// Name of this DegreeOfFreedom
  std::string mName;

  /// Index of this DegreeOfFreedom within its Joint
  size_t mIndexInJoint;

  /// Index of this DegreeOfFreedom within its Skeleton
  size_t mIndexInSkeleton;

  /// The joint that this DegreeOfFreedom belongs to
  Joint* mJoint;
  // Note that we do not need to store BodyNode or Skeleton, because we can
  // access them through this joint pointer. Moreover, we never need to check
  // whether mJoint is nullptr, because only Joints are allowed to create a
  // DegreeOfFreedom and DegreesOfFreedom are deleted when their Joint is
  // destructed.

};

} // namespace dynamics
} // namespace dart

#endif // DART_DYNAMICS_DEGREEOFFREEDOM_H_
