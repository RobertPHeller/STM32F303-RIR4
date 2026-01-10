// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Mon Apr 3 16:47:46 2023
//  Last Modified : <260110.1629>
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
/// @file main.cxx
/// @author Robert Heller
/// @date Mon Apr 3 16:47:46 2023
/// 
///
//////////////////////////////////////////////////////////////////////////////

/**
 * @mainpage Introduction
 * STM32F303 Nucleo Baseboard for Aztrax RIR4 shield
 *
 * @image html STM32F303-RIR4Top3D.png
 *  
 * This baseboard has Morpho sockets for a STM32F303 board (NUCLEO-F303K8), with 
 * one or two [Azatrax RIR4 shields](https://www.azatrax.com/arduino-shield-ir-detector.html) stacked on 
 * top.  There is firmware that implements grade crossing logic, using two
 * resolutions using 1 or 2 shields. There is also firmware that allows using
 * just the sensors and stopwatches, with support for one or two shields.
 * 
 * The baseboard also provides additional output functions: four servos, four
 * blink signals, two stall motors, and two Solid State relays.  These outputs
 * can be used to implement an active grade crossing or to operate other
 * automation. 
 */

#include <unistd.h>

#include "os/os.h"
#include "nmranet_config.h"

#include "openlcb/SimpleStack.hxx"
#include "openlcb/MultiConfiguredConsumer.hxx"
#include "openlcb/ConfiguredProducer.hxx"
#include "openlcb/ServoConsumer.hxx"
#include <openlcb/RefreshLoop.hxx>

#ifdef LOGLEVEL
#undef LOGLEVEL
#define LOGLEVEL VERBOSE
#endif


#include "stdio_logging.h"

#include "freertos_drivers/st/Stm32Gpio.hxx"
#include "freertos_drivers/common/BlinkerGPIO.hxx"
#include "freertos_drivers/common/DummyGPIO.hxx"
#include "os/MmapGpio.hxx"
//#include "NodeIdConfigurationGroup.hxx"
#include "config.hxx"
#include "Hardware.hxx"
#include "Azatrax.hxx"
#include "Blink.hxx"
#include "BlinkingConsumerConfig.hxx"
#include "BlinkingConsumer.hxx"
#include "openlcb/ServoConsumerConfig.hxx"
#include "openlcb/ServoConsumer.hxx"
#include "StallConsumerConfig.hxx"
#include "StallConsumer.hxx"
#include "SSRConsumerConfig.hxx"
#include "SSRConsumer.hxx"

#if defined(LOWRESCROSSING) || defined(STANDARDRESCROSSING)
#include "AzatraxRIR4Crossing.hxx"
#if defined(LOWRESCROSSING) && defined(RIR4ADDRESS2)
#include "AzatraxRIR4PC.hxx"
#endif
#else
#include "AzatraxRIR4PC.hxx"
#endif
// These preprocessor symbols are used to select which physical connections
// will be enabled in the main(). See @ref appl_main below.
//#define SNIFF_ON_SERIAL
//#define SNIFF_ON_USB
#define HAVE_PHYSICAL_CAN_PORT

// Changes the default behavior by adding a newline after each gridconnect
// packet. Makes it easier for debugging the raw device.
OVERRIDE_CONST(gc_generate_newlines, 1);
// Specifies how much RAM (in bytes) we allocate to the stack of the main
// thread. Useful tuning parameter in case the application runs out of memory.
OVERRIDE_CONST(main_thread_stack_size, 2500);

// Specifies the 48-bit OpenLCB node identifier. This must be unique for every
// hardware manufactured, so in production this should be replaced by some
// easily incrementable method.
static openlcb::NodeID NODE_ID = 0x050101012200ULL; // 05 01 01 01 22 00


// ConfigDef comes from config.hxx and is specific to the particular device and
// target. It defines the layout of the configuration memory space and is also
// used to generate the cdi.xml file. Here we instantiate the configuration
// layout. The argument of offset zero is ignored and will be removed later.
openlcb::ConfigDef cfg(0);
// Defines weak constants used by the stack to tell it which device contains
// the volatile configuration information. This device name appears in
// HwInit.cxx that creates the device drivers.
extern const char *const openlcb::CONFIG_FILENAME = "/dev/eeprom";
// The size of the memory space to export over the above device. We verify that
// the available eeprom is not too full (8192 max) to avoid quick wear-out
// of the flash. Recommended to have at least 10% spare.
extern const size_t openlcb::CONFIG_FILE_SIZE =
cfg.seg().size() + cfg.seg().offset();
static_assert(openlcb::CONFIG_FILE_SIZE <= 7000, "Need to adjust eeprom size");

// The SNIP user-changeable information in also stored in the above eeprom
// device. In general this could come from different eeprom segments, but it is
// simpler to keep them together.
extern const char *const openlcb::SNIP_DYNAMIC_FILENAME =
openlcb::CONFIG_FILENAME;

//class FactoryResetHelper : public DefaultConfigUpdateListener {
//public:
//    UpdateAction apply_configuration(int fd, bool initial_load,
//                                     BarrierNotifiable *done) OVERRIDE {
//                                         AutoNotify n(done);
//                                         return UPDATED;
//                                     }
//    
//    void factory_reset(int fd) override
//    {
//        //cfg.userinfo().name().write(fd, "Azatrax RIR4");
//        //cfg.userinfo().description().write(
//        //       fd, "Azatrax RIR4 + Nucleo dev board.");
//    }
//} factory_reset_helper;

azatrax::Azatrax rir4(RIR4ADDRESS);
#ifdef RIR4ADDRESS2
azatrax::Azatrax rir4_2(RIR4ADDRESS2);
#endif

extern "C" {
extern void resetblink(uint32_t pattern);
}

/** Entry point to application.
 * @param argc number of command line arguments
 * @param argv array of command line arguments
 * @return 0, should never return
 */
int appl_main(int argc, char *argv[])
{
    LOG(VERBOSE,"[appl_main] Startup");
    resetblink(0x80000001);
    //NodeIdMemoryConfigSpace nodeIdSpace(NODE_ID);
    //LOG(VERBOSE,"[appl_main] nodeIdSpace allocated");
    //resetblink(0x80000005);
    //NODE_ID = nodeIdSpace.node_id();
    LOG(VERBOSE,"[appl_main] NODE_ID is 0X%llu0X", NODE_ID);
    resetblink(0x80000015);
    
    rir4.begin("/dev/i2c0");
    LOG(VERBOSE,"[appl_main] rir4 initialized.");
    resetblink(0x80000055);
#ifdef RIR4ADDRESS2
    rir4_2.begin("/dev/i2c0");
    LOG(VERBOSE,"[appl_main] rir4_2 initialized.");
    resetblink(0x80000155);
#endif
    // Sets up a comprehensive OpenLCB stack for a single virtual node. This stack
    // contains everything needed for a usual peripheral node -- all
    // CAN-bus-specific components, a virtual node, PIP, SNIP, Memory configuration
    // protocol, ACDI, CDI, a bunch of memory spaces, etc.
    openlcb::SimpleCanStack stack(NODE_ID);
    LOG(VERBOSE,"[appl_main] stack initialized.");
    resetblink(0x80000555);
    //nodeIdSpace.RegisterSpace(&stack);
    //LOG(VERBOSE,"[appl_main] nodeIdSpace registered.");
    //resetblink(0x80001555);
    
    //DEFINE_SINGLETON_INSTANCE(BlinkTimer);
    BlinkTimer blinker(stack.executor()->active_timers());
    LOG(VERBOSE,"[appl_main] blinker initialized.");
    resetblink(0x80005555);
#ifdef LOWRESCROSSING
    AzatraxRIR4Crossing crossing(stack.node(),cfg.seg().azatraxrir4crossing(),
                                 &rir4,true);
    openlcb::RefreshLoop crossingloop(stack.node(), {(openlcb::Polling*)&crossing});
    LOG(VERBOSE,"[appl_main] crossing (LOWRESCROSSING) initialized.");
#ifdef RIR4ADDRESS2
    AzatraxRIR4 shield(stack.node(),cfg.seg().azatraxrir4(),&rir4_2);
    openlcb::RefreshLoop shieldloop(stack.node(), {(openlcb::Polling*)&shield});
    LOG(VERBOSE,"[appl_main] shield initialized.");
#endif
#elif defined(STANDARDRESCROSSING)
#ifdef RIR4ADDRESS2
    AzatraxRIR4Crossing crossing(stack.node(),cfg.seg().azatraxrir4crossing(),
                                 &rir4,&rir4_2);
    openlcb::RefreshLoop crossingloop(stack.node(), {(openlcb::Polling*)&crossing});
    LOG(VERBOSE,"[appl_main] crossing (STANDARDRESCROSSING, 2 shields) initialized.");
#else
    AzatraxRIR4Crossing crossing(stack.node(),cfg.seg().azatraxrir4crossing(),
                                 &rir4,false);
    openlcb::RefreshLoop crossingloop(stack.node(), {(openlcb::Polling*)&crossing});
    LOG(VERBOSE,"[appl_main] crossing (STANDARDRESCROSSING, 1 shield) initialized."); 
#endif
#else
    AzatraxRIR4 shield(stack.node(),cfg.seg().azatraxrir4(),&rir4);
    openlcb::RefreshLoop shieldloop(stack.node(), {(openlcb::Polling*)&shield});
    LOG(VERBOSE,"[appl_main] shield initialized.");
#ifdef RIR4ADDRESS2
    AzatraxRIR4 shield2(stack.node(),cfg.seg().azatraxrir4_2(),&rir4_2);
    openlcb::RefreshLoop shield2loop(stack.node(), {(openlcb::Polling*)&shield2});
    LOG(VERBOSE,"[appl_main] shield2 initialized.");
#endif
#endif
    resetblink(0x80015555);

    BlinkingConsumer signal1(stack.node(), cfg.seg().signals().entry<0>(),SIG1_Pin());
    BlinkingConsumer signal2(stack.node(), cfg.seg().signals().entry<1>(),SIG2_Pin());
    BlinkingConsumer signal3(stack.node(), cfg.seg().signals().entry<2>(),SIG3_Pin());
    BlinkingConsumer signal4(stack.node(), cfg.seg().signals().entry<3>(),SIG4_Pin());
    LOG(VERBOSE,"[appl_main] signal1, signal2, signal3, signal4 initialized.");
    resetblink(0x80055555);
    openlcb::ServoConsumer srv0(stack.node(), cfg.seg().servos().entry<0>(),servoPwmCountPerMs, servo_channels[0]);
    openlcb::ServoConsumer srv1(stack.node(), cfg.seg().servos().entry<1>(),servoPwmCountPerMs, servo_channels[1]);
    openlcb::ServoConsumer srv2(stack.node(), cfg.seg().servos().entry<2>(),servoPwmCountPerMs, servo_channels[2]);
    openlcb::ServoConsumer srv3(stack.node(), cfg.seg().servos().entry<3>(),servoPwmCountPerMs, servo_channels[3]);
    LOG(VERBOSE,"[appl_main] srv0, srv1, srv2, srv3 initialized.");
    resetblink(0x80155555);
    StallConsumer stall1(stack.node(), cfg.seg().stallmotors().entry<0>(),StallM_Pin());                            
    StallConsumer stall2(stack.node(), cfg.seg().stallmotors().entry<1>(),StallN_Pin());
    LOG(VERBOSE,"[appl_main] stall1 and stall2 initialized.");
    resetblink(0x80555555);
    SSRConsumer ssr1(stack.node(), cfg.seg().ssrs().entry<0>(),SSR1_Pin());
    SSRConsumer ssr2(stack.node(), cfg.seg().ssrs().entry<1>(),SSR2_Pin());
    LOG(VERBOSE,"[appl_main] ssr1 and ssr2 initialized."); 
    resetblink(0x81555555);
    
    blinker.start(500000000);
    LOG(VERBOSE,"[appl_main] blinker started.");
    resetblink(0x85555555);
    stack.check_version_and_factory_reset(
           cfg.seg().internal_config(), openlcb::CANONICAL_VERSION, false);
    LOG(VERBOSE,"[appl_main] check_version_and_factory_reset done.");
    resetblink(0x95555555);
    
    // The necessary physical ports must be added to the stack.
    //
    // It is okay to enable multiple physical ports, in which case the stack
    // will behave as a bridge between them. For example enabling both the
    // physical CAN port and the USB port will make this firmware act as an
    // USB-CAN adapter in addition to the producers/consumers created above.
    //
    // If a port is enabled, it must be functional or else the stack will
    // freeze waiting for that port to send the packets out.
#if defined(HAVE_PHYSICAL_CAN_PORT)
    stack.add_can_port_select("/dev/can0");
    LOG(VERBOSE,"[appl_main] /dev/can0 added to stack.");
    resetblink(0xd5555555);
#endif
#if defined(SNIFF_ON_USB)
    stack.add_gridconnect_port("/dev/serUSB0");
#endif
#if defined(SNIFF_ON_SERIAL)
    stack.add_gridconnect_port("/dev/ser0");
#endif
    
    // This command donates the main thread to the operation of the
    // stack. Alternatively the stack could be started in a separate stack and
    // then application-specific business logic could be executed ion a busy
    // loop in the main thread.
    stack.loop_executor();
    return 0;
}

