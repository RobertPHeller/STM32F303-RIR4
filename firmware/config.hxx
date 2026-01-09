// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Mon Apr 3 16:47:54 2023
//  Last Modified : <260109.1258>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
/// @copyright
///    Copyright (C) 2023  Robert Heller D/B/A Deepwoods Software
///			51 Locke Hill Road
///			Wendell, MA 01379-9728
///
///    This program is free software; you can redistribute it and/or modify
///    it under the terms of the GNU General Public License as published by
///    the Free Software Foundation; either version 2 of the License, or
///    (at your option) any later version.
///
///    This program is distributed in the hope that it will be useful,
///    but WITHOUT ANY WARRANTY; without even the implied warranty of
///    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
///    GNU General Public License for more details.
///
///    You should have received a copy of the GNU General Public License
///    along with this program; if not, write to the Free Software
///    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
/// @file config.hxx
/// @author Robert Heller
/// @date Mon Apr 3 16:47:54 2023
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __CONFIG_HXX
#define __CONFIG_HXX

#include "openlcb/ConfigRepresentation.hxx"
#include "openlcb/ConfiguredConsumer.hxx"
#include "openlcb/ConfiguredProducer.hxx"
#include "openlcb/ServoConsumerConfig.hxx"
#include "openlcb/MemoryConfig.hxx"
//#include "NodeIdConfigurationGroup.hxx"
#include "BlinkingConsumerConfig.hxx"
#include "StallConsumerConfig.hxx"
#include "SSRConsumerConfig.hxx"
#include "Revision.hxxout"
#include "HardwareDEFS.hxx"

#if defined(LOWRESCROSSING) || defined(STANDARDRESCROSSING)
#include "AzatraxRIR4Crossing.hxx"
#if defined(LOWRESCROSSING) && defined(RIR4ADDRESS2)
#include "AzatraxRIR4PC.hxx"
#endif
#else
#include "AzatraxRIR4PC.hxx"
#endif

namespace openlcb
{
/// Defines the identification information for the node. The arguments are:
///
/// - 4 (version info, always 4 by the standard
/// - Manufacturer name
/// - Model name
/// - Hardware version
/// - Software version
///
/// This data will be used for all purposes of the identification:
///
/// - the generated cdi.xml will include this data
/// - the Simple Node Ident Info Protocol will return this data
/// - the ACDI memory space will contain this data.
extern const SimpleNodeStaticValues SNIP_STATIC_DATA = {
    4, "Deepwoods Software", "Azatrax RIR4 + Nucleo F303 dev board",
    "Rev A", "1.00"};

/// Modify this value every time the EEPROM needs to be cleared on the node
/// after an update.

#if defined(LOWRESCROSSING) || defined(STANDARDRESCROSSING)
# if defined(LOWRESCROSSING) && defined(RIR4ADDRESS2)
#define CANONICAL_VERSIONOFFSET 11
# else
#define CANONICAL_VERSIONOFFSET 10
# endif
#else
# if defined(RIR4ADDRESS2)
#define CANONICAL_VERSIONOFFSET 6
# else 
#define CANONICAL_VERSIONOFFSET 5
# endif
#endif




static constexpr uint16_t CANONICAL_VERSION = 0x1000 + CANONICAL_VERSIONOFFSET;


using ServoConsumers = RepeatedGroup<ServoConsumerConfig, NUM_SERVOS>;
using SignalConsumers = RepeatedGroup<BlinkingConsumerConfig, NUM_SIGNALS>;
using StallConsumers = RepeatedGroup<StallConsumerConfig, NUM_STALL>;
using SSRConsumers = RepeatedGroup<SSRConsumerConfig, NUM_SSR>;

/// Defines the main segment in the configuration CDI. This is laid out at
/// origin 128 to give space for the ACDI user data at the beginning.
CDI_GROUP(IoBoardSegment, Segment(MemoryConfigDefs::SPACE_CONFIG), Offset(128));
/// Each entry declares the name of the current entry, then the type and then
/// optional arguments list.
CDI_GROUP_ENTRY(internal_config, InternalConfigData);
#if defined(LOWRESCROSSING) || defined(STANDARDRESCROSSING)
CDI_GROUP_ENTRY(azatraxrir4crossing,AzatraxRIR4CrossingConfig,
                Name("Azatrax RIR4 Crossing"),
                Description("Azatrax RIR4 Crossing"));
# if defined(LOWRESCROSSING) && defined(RIR4ADDRESS2)
CDI_GROUP_ENTRY(azatraxrir4,AzatraxRIR4Config,Name("Azatrax RIR4 #2"),
                Description("Azatrax RIR4 shield #2"));
#endif
#else
CDI_GROUP_ENTRY(azatraxrir4,AzatraxRIR4Config,Name("Azatrax RIR4"),
                Description("Azatrax RIR4 shield"));
#ifdef RIR4ADDRESS2
CDI_GROUP_ENTRY(azatraxrir4_2,AzatraxRIR4Config,Name("Azatrax RIR4 #2"),
                Description("Azatrax RIR4 shield #2"));
#endif
#endif
CDI_GROUP_ENTRY(signals,SignalConsumers,Name("Signals"),RepName("Signal"),
                Description("Blinking Signals"));
CDI_GROUP_ENTRY(stallmotors,StallConsumers,Name("Stall Motors"),
                RepName("Stall Motor"),Description("Stall motors for gates or other things."));
CDI_GROUP_ENTRY(servos,ServoConsumers,Name("Servos"),RepName("Servo"),
                Description("Servos for gates or other things."));
CDI_GROUP_ENTRY(ssrs,SSRConsumers,Name("Solid State Relays"),RepName("Relay"),
                Description("Solid State Relays for other accessors (sound units, etc.)"));
CDI_GROUP_END();

/// This segment is only needed temporarily until there is program code to set
/// the ACDI user data version byte.
CDI_GROUP(VersionSeg, Segment(MemoryConfigDefs::SPACE_CONFIG),
          Name("Version information"));
CDI_GROUP_ENTRY(acdi_user_version, Uint8ConfigEntry,
                Name("ACDI User Data version"), Description("Set to 2 and do not change."));
CDI_GROUP_ENTRY(buildrevisions,BuildRevisions);
CDI_GROUP_END();

/// The main structure of the CDI. ConfigDef is the symbol we use in main.cxx
/// to refer to the configuration defined here.
CDI_GROUP(ConfigDef, MainCdi());
/// Adds the <identification> tag with the values from SNIP_STATIC_DATA above.
CDI_GROUP_ENTRY(ident, Identification);
/// Adds an <acdi> tag.
CDI_GROUP_ENTRY(acdi, Acdi);
/// Adds a segment for changing the values in the ACDI user-defined
/// space. UserInfoSegment is defined in the system header.
CDI_GROUP_ENTRY(userinfo, UserInfoSegment);
/// Adds the main configuration segment.
CDI_GROUP_ENTRY(seg, IoBoardSegment);
//CDI_GROUP_ENTRY(node,NodeIdConfig,Name("Node ID"));
/// Adds the versioning segment.
CDI_GROUP_ENTRY(version, VersionSeg);
CDI_GROUP_END();

} // namespace openlcb



#endif // __CONFIG_HXX

