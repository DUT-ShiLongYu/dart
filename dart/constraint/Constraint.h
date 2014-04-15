/*
 * Copyright (c) 2014, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Jeongseok Lee <jslee02@gmail.com>
 *
 * Geoorgia Tech Graphics Lab and Humanoid Robotics Lab
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

#ifndef DART_CONSTRAINT_CONSTRAINT_H_
#define DART_CONSTRAINT_CONSTRAINT_H_

#include <cstddef>

namespace dart {

namespace dynamics {
class Skeleton;
}  // namespace dynamics

namespace constraint {

//==============================================================================
// TODO(JS): Restricted to ODE LCP solver. Generalize this class for various
//           types of LCP solvers.
/// LCPTerms class
class ODELcp
{
public:
  ///  Constructor
  explicit ODELcp(int _n);

  ///  Destructor
  ~ODELcp();

  //-------------------------- TEST CODE ---------------------------------------
  void print();

  void clear();

  bool checkSymmetric();

  bool checkSymmetric2(int _index);

  //----------------------------------------------------------------------------
  ///
  double* A;

  ///
  double* b;

  ///
  double* x;

  ///
  double* w;

  /// Lower bound of x
  double* lb;

  /// Upper bound of x
  double* ub;

  /// Friction index
  int* frictionIndex;

  /// Total dimension of contraints
  int dim;

  ///
  int nSkip;

  double invTimestep;
};

/// Type of the constraint
enum ConstraintType
{
  CT_STATIC,
  CT_DYNAMIC
};

/// ConstraintTEST class
class Constraint
{
protected:
  /// Default contructor
  explicit Constraint(ConstraintType _type);

  /// Destructor
  virtual ~Constraint();

  /// Update constraint using updated Skeleton's states
  virtual void update() = 0;

  /// Fill LCP variables
  virtual void fillLcpOde(ODELcp* _lcp, int _idx) = 0;

  /// Apply unit impulse to constraint space of _idx
  virtual void applyUnitImpulse(int _idx) = 0;

  ///
  virtual void getVelocityChange(double* _delVel, int _idx, bool _withCfm) = 0;

  ///
  virtual void excite() = 0;

  ///
  virtual void unexcite() = 0;

  /// Apply computed constraint impulse to constrained skeletons
  virtual void applyConstraintImpulse(double* _lambda) = 0;

  /// Return true if this constraint is active
  virtual bool isActive() const = 0;

  ///
  virtual dynamics::Skeleton* getRootSkeleton() const {}

  ///
  virtual void uniteSkeletons() {}

  ///
  size_t getDimension() const;

  ///
  static dynamics::Skeleton* compressPath(dynamics::Skeleton* _skeleton);

  ///
  static dynamics::Skeleton* getRootSkeleton(dynamics::Skeleton* _skeleton);

protected:
  /// Dimension of constraint
  size_t mDim;

  /// Constraint type: static or dynamic
  ConstraintType mConstraintType;

public:
  //----------------------------------------------------------------------------
  // Friendship
  //----------------------------------------------------------------------------
  friend class ConstraintSolver;
  friend class ConstrainedGroup;
};

} // namespace constraint
} // namespace dart

#endif  // DART_CONSTRAINT_CONSTRAINT_H_TEST

