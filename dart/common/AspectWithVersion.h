/*
 * Copyright (c) 2016, Georgia Tech Research Corporation
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

#ifndef DART_COMMON_ASPECTWITHVERSION_H_
#define DART_COMMON_ASPECTWITHVERSION_H_

#include "dart/common/detail/AspectWithVersion.h"

namespace dart {
namespace common {

//==============================================================================
template <class DerivedT,
          typename StateDataT,
          class CompositeT = Composite,
          void (*updateState)(DerivedT*) = &detail::NoOp<DerivedT*> >
using AspectWithState =
    detail::AspectWithState<CompositeTrackingAspect<CompositeT>, DerivedT, StateDataT, CompositeT, updateState>;

//==============================================================================
template <class DerivedT,
          typename PropertiesDataT,
          class CompositeT = Composite,
          void (*updateProperties)(DerivedT*) = &detail::NoOp<DerivedT*> >
using AspectWithVersionedProperties =
    detail::AspectWithVersionedProperties<CompositeTrackingAspect<CompositeT>, DerivedT, PropertiesDataT, CompositeT, updateProperties>;

//==============================================================================
template <class DerivedT,
          typename StateDataT,
          typename PropertiesDataT,
          class CompositeT = Composite,
          void (*updateState)(DerivedT*) = &detail::NoOp<DerivedT*>,
          void (*updateProperties)(DerivedT*) = updateState>
class AspectWithStateAndVersionedProperties :
    public detail::AspectWithVersionedProperties<
        AspectWithState<DerivedT, StateDataT, CompositeT, updateState>,
        DerivedT, PropertiesDataT, CompositeT, updateProperties>
{
public:

  using Derived = DerivedT;
  using StateData = StateDataT;
  using PropertiesData = PropertiesDataT;
  using CompositeType = CompositeT;
  using State = common::Aspect::StateMixer<StateData>;
  using Properties = common::Aspect::PropertiesMixer<PropertiesData>;
  constexpr static void (*UpdateState)(Derived*) = updateState;
  constexpr static void (*UpdateProperties)(Derived*) = updateProperties;

  using AspectStateImplementation = AspectWithState<
      Derived, StateData, CompositeType, updateState>;

  using AspectPropertiesImplementation = detail::AspectWithVersionedProperties<
      AspectStateImplementation,
      Derived, PropertiesData, CompositeType, updateProperties>;

  using AspectImplementation = AspectWithStateAndVersionedProperties<
      DerivedT, StateDataT, PropertiesDataT, CompositeT,
      updateState, updateProperties>;

  AspectWithStateAndVersionedProperties() = delete;
  AspectWithStateAndVersionedProperties(
      const AspectWithStateAndVersionedProperties&) = delete;

  /// Construct using a StateData and a PropertiesData instance
  AspectWithStateAndVersionedProperties(
      common::Composite* comp,
      const StateData& state = StateData(),
      const PropertiesData& properties = PropertiesData())
    : AspectPropertiesImplementation(comp, properties, state)
  {
    // Do nothing
  }

  /// Construct using a PropertiesData and a StateData instance
  AspectWithStateAndVersionedProperties(
      common::Composite* comp,
      const PropertiesData& properties,
      const StateData& state = StateData())
    : AspectPropertiesImplementation(comp, properties, state)
  {
    // Do nothing
  }

};

//==============================================================================
//
// These namespace-level definitions are required to enable ODR-use of static
// constexpr member variables.
//
// See this StackOverflow answer: http://stackoverflow.com/a/14396189/111426
//
template <class DerivedT,
          typename StateDataT,
          typename PropertiesDataT,
          class CompositeT,
          void (*updateState)(DerivedT*),
          void (*updateProperties)(DerivedT*)>
constexpr void (*AspectWithStateAndVersionedProperties<DerivedT, StateDataT,
    PropertiesDataT, CompositeT, updateState, updateProperties>::UpdateState)
    (DerivedT*);

//==============================================================================
template <class DerivedT,
          typename StateDataT,
          typename PropertiesDataT,
          class CompositeT,
          void (*updateState)(DerivedT*),
          void (*updateProperties)(DerivedT*)>
constexpr void (*AspectWithStateAndVersionedProperties<DerivedT, StateDataT,
    PropertiesDataT, CompositeT, updateState, updateProperties>::UpdateProperties)
    (DerivedT*);

} // namespace common
} // namespace dart

#endif // DART_COMMON_ASPECTWITHVERSION_H_
