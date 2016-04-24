/*
 * Copyright (c) 2014-2016, Georgia Tech Research Corporation
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

#ifndef EXAMPLES_ATLASSIMBICON_TERMINALCONDITION_H_
#define EXAMPLES_ATLASSIMBICON_TERMINALCONDITION_H_

#include <vector>
#include <string>

#include <Eigen/Dense>

#include "dart/dart.hpp"

class State;

//==============================================================================
/// \brief class TerminalCondition
class TerminalCondition
{
public:
  /// \brief Constructor
  TerminalCondition(State* _state);

  /// \brief Destructor
  virtual ~TerminalCondition();

  /// \brief Check if this condition is satisfied or not.
  virtual bool isSatisfied() = 0;

protected:
  /// \brief State
  State* mState;
};

//==============================================================================
/// \brief class TimerCondition
class TimerCondition : public TerminalCondition
{
public:
  /// \brief Constructor
  TimerCondition(State* _state, double _duration);

  /// \brief Destructor
  virtual ~TimerCondition();

  // Documentation inherited.
  bool isSatisfied() override;

protected:
  /// \brief Duration
  double mDuration;
};

//==============================================================================
/// \brief class BodyContactCondition
class BodyContactCondition : public TerminalCondition
{
public:
  /// \brief Constructor
  BodyContactCondition(State* _state, dart::dynamics::BodyNode* _body);

  /// \brief Destructor
  virtual ~BodyContactCondition();

  // Documentation inherited.
  bool isSatisfied() override;

protected:
  /// \brief Body node to be tested
  dart::dynamics::BodyNode* mBodyNode;
};

#endif  // EXAMPLES_ATLASSIMBICON_TERMINALCONDITION_H_
