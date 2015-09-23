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

#include <cassert>
#include <iostream>

#include "dart/common/Console.h"
#include "dart/common/AddonManager.h"

namespace dart {
namespace common {

//==============================================================================
void AddonManager::setAddonStates(const State& newStates)
{
  const StateMap& stateMap = newStates.getMap();

  AddonMap::iterator addons = mAddonMap.begin();
  StateMap::const_iterator states = stateMap.begin();

  while( mAddonMap.end() != addons && stateMap.end() != states )
  {
    if( addons->first == states->first )
    {
      Addon* addon = addons->second.get();
      if(addon && states->second)
        addon->setState(states->second);

      ++addons;
      ++states;
    }
    else if( addons->first < states->first )
    {
      ++addons;
    }
    else
    {
      ++states;
    }
  }
}

//==============================================================================
template <typename MapType, class DataType, const DataType* (Addon::*getData)() const>
void extractMapData(MapType& outgoingMap, const AddonManager::AddonMap& addonMap)
{
  // TODO(MXG): Consider placing this function in a header so it can be utilized
  // by anything that needs to transfer data between maps of extensibles

  // This method allows us to avoid dynamic allocation (cloning) whenever possible.
  for(const auto& addon : addonMap)
  {
    if(nullptr == addon.second)
      continue;

    const DataType* data = (addon.second.get()->*getData)();
    if(data)
    {
      // Attempt to insert a nullptr to see whether this entry exists while also
      // creating an itertor to it if it did not already exist. This allows us
      // to search for a spot in the map once, instead of searching the map to
      // see if the entry already exists and then searching the map again in
      // order to insert the entry if it didn't already exist.
      std::pair<typename MapType::iterator, bool> insertion =
          outgoingMap.insert(typename MapType::value_type(addon.first, nullptr));

      typename MapType::iterator& it = insertion.first;
      bool existed = !insertion.second;

      if(existed)
      {
        // The entry already existed
        if(it->second)
        {
          // The entry was not a nullptr, so we can do an efficient copy
          it->second->copy(*data);
        }
        else
        {
          // The entry was a nullptr, so we need to clone
          it->second = data->clone();
        }
      }
      else
      {
        // The entry did not already exist, so we need to clone
        it->second = data->clone();
      }
    }
  }
}

//==============================================================================
AddonManager::State AddonManager::getAddonStates() const
{
  State states;
  copyAddonStatesTo(states);

  return states;
}

//==============================================================================
void AddonManager::copyAddonStatesTo(State& outgoingStates) const
{
  StateMap& states = outgoingStates.getMap();
  extractMapData<StateMap, Addon::State, &Addon::getState>(states, mAddonMap);
}

//==============================================================================
void AddonManager::setAddonProperties(const Properties& newProperties)
{
  const PropertiesMap& propertiesMap = newProperties.getMap();

  AddonMap::iterator addons = mAddonMap.begin();
  PropertiesMap::const_iterator props = propertiesMap.begin();

  while( mAddonMap.end() != addons && propertiesMap.end() != props )
  {
    if( addons->first == props->first )
    {
      Addon* addon = addons->second.get();
      if(addon)
        addon->setProperties(props->second);

      ++addons;
      ++props;
    }
    else if( addons->first < props->first )
    {
      ++addons;
    }
    else
    {
      ++props;
    }
  }
}

//==============================================================================
AddonManager::Properties AddonManager::getAddonProperties() const
{
  Properties properties;
  copyAddonPropertiesTo(properties);

  return properties;
}

//==============================================================================
void AddonManager::copyAddonPropertiesTo(
    Properties& outgoingProperties) const
{
  PropertiesMap& properties = outgoingProperties.getMap();
  extractMapData<PropertiesMap, Addon::Properties, &Addon::getProperties>(
        properties, mAddonMap);
}

//==============================================================================
void AddonManager::duplicateAddons(const AddonManager* otherManager)
{
  if(nullptr == otherManager)
  {
    dterr << "[AddonManager::duplicateAddons] You have asked to duplicate the "
          << "Addons of a nullptr, which is not allowed!\n";
    assert(false);
    return;
  }

  const AddonMap& otherMap = otherManager->mAddonMap;

  AddonMap::iterator receiving = mAddonMap.begin();
  AddonMap::const_iterator incoming = otherMap.begin();

  while( otherMap.end() != incoming )
  {
    if( mAddonMap.end() == receiving )
    {
      // If we've reached the end of this Manager's AddonMap, then we should
      // just add each entry
      mAddonMap[incoming->first] = incoming->second->clone(this);
    }
    else if( receiving->first == incoming->first )
    {
      if(incoming->second)
        receiving->second = incoming->second->clone(this);

      ++receiving;
      ++incoming;
    }
    else if( receiving->first < incoming->first)
    {
      ++receiving;
    }
    else
    {
      // If this Manager does not have an entry corresponding to the incoming
      // Addon, then we must create it
      mAddonMap[incoming->first] = incoming->second->clone(this);
      ++incoming;
    }
  }
}

//==============================================================================
void AddonManager::matchAddons(const AddonManager* otherManager)
{
  if(nullptr == otherManager)
  {
    dterr << "[AddonManager::matchAddons] You have asked to match the Addons "
          << "of a nullptr, which is not allowed!\n";
    assert(false);
    return;
  }

  for(auto& addon : mAddonMap)
    addon.second = nullptr;

  duplicateAddons(otherManager);
}

//==============================================================================
void AddonManager::becomeManager(Addon* addon)
{
  addon->changeManager(this);
}

} // namespace common
} // namespace dart
