// -!- c++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Wed Apr 12 15:07:42 2023
//  Last Modified : <230412.1630>
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
/// @file AzatraxRIR4Crossing.hxx
/// @author Robert Heller
/// @date Wed Apr 12 15:07:42 2023
/// 
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __AZATRAXRIR4CROSSING_HXX
#define __AZATRAXRIR4CROSSING_HXX

#include "openlcb/Node.hxx"
#include "openlcb/EventHandlerTemplates.hxx"
#include "openlcb/ConfigRepresentation.hxx"
#include "utils/ConfigUpdateListener.hxx"
#include "utils/ConfigUpdateService.hxx"
#include "openlcb/RefreshLoop.hxx"
#include "Azatrax/Azatrax.hxx"

/// CDI Configuration for a @ref AzatraxRIR4Crossing
CDI_GROUP(AzatraxRIR4CrossingConfig);
/// Allows the user to assign a name for this unit
CDI_GROUP_ENTRY(description, openlcb::StringConfigEntry<16>, //
                Name("Description"),
                Description("User name of this grade crossing."));
/// Event produced (sent) when the the grade crossing is activated.
CDI_GROUP_ENTRY(activated, openlcb::EventConfigEntry,
                Name("Activated"),
                Description("(P) This event is produced when the grade crossing is activated."));
/// Event produced (sent) when the the grade crossing is deactivated.
CDI_GROUP_ENTRY(deactivated, openlcb::EventConfigEntry,
                Name("Deactivated"),
                Description("(P) This event is produced when the grade crossing is deactivated."));
CDI_GROUP_END();

class AzatraxRIR4Crossing : public DefaultConfigUpdateListener,
                                        public openlcb::SimpleEventHandler,
                                        public openlcb::Polling
{
private:
    enum States {Idle, Track1, Track1Wait, Track2, Track2Wait};
    enum Modes  {LowRes12Tracks, StandardRes1Track, StandardRes2Tracks};
public:
    /// Constructor (one shield):
    /// @param node LCC Node object.
    /// @param cfg Configuration for this AzatraxRIR4Crossing.
    /// @param rir4 Azatrax instance
    /// @param lowres True means LowRes12Tracks, false means StandardRes1Track
    AzatraxRIR4Crossing(openlcb::Node *node, 
                        const AzatraxRIR4CrossingConfig &cfg,
                        azatrax::Azatrax *rir4,
                        bool lowres = true)
                : DefaultConfigUpdateListener()
          , node_(node)
          , cfg_(cfg)
          , rir4a_(rir4)
          , activated_(0)
          , deactivated_(0)
          , state_(Idle)
          , mode_(lowres?LowRes12Tracks:StandardRes1Track)
    {
    }
    /// Constructor (two shields):
    /// @param node LCC Node object.
    /// @param cfg Configuration for this AzatraxRIR4Crossing.
    /// @param rir4a Azatrax instance 1
    /// @param rir4b Azatrax instance 2
    AzatraxRIR4Crossing(openlcb::Node *node,
                        const AzatraxRIR4CrossingConfig &cfg,
                        azatrax::Azatrax *rir4a,
                        azatrax::Azatrax *rir4b)
                : DefaultConfigUpdateListener()
          , node_(node)
          , cfg_(cfg)
          , rir4a_(rir4a)
          , rir4b_(rir4b)
          , activated_(0)
          , deactivated_(0)
          , state_(Idle)
          , mode_(StandardRes2Tracks)
    {
    }
    /// Destructor:
    ~AzatraxRIR4Crossing()
    {
    }
    /// Apply a configuration update.
    /// @param fd File description into the configuration.
    /// @param initial_load True if this is the first time.
    /// @param done Notification object.
    /// @returns the update action, either REINIT_NEEDED or UPDATED.
    UpdateAction apply_configuration(int fd, 
                                     bool initial_load, 
                                     BarrierNotifiable *done) OVERRIDE
    {
        AutoNotify n(done);
        const openlcb::EventId cfg_activated = cfg_.activated().read(fd);
        const openlcb::EventId cfg_deactivated = cfg_.deactivated().read(fd);
        if (cfg_activated != activated_ ||
            cfg_deactivated != deactivated_)
        {
            if (!initial_load) unregister_event_handler();
            activated_ = cfg_activated;
            deactivated_ = cfg_deactivated;
            register_event_handler();
            return REINIT_NEEDED;
        }
        return UPDATED;
    }
    /// Factory reset.
    /// @param fd File descriptor into the configuration.
    /// @returns nothing.
    void factory_reset(int fd) OVERRIDE
    {
        cfg_.description().write(fd, "");
    }
    void poll_33hz(openlcb::WriteHelper *helper, Notifiable *done) OVERRIDE
    {
        switch (mode_)
        {
        case LowRes12Tracks:
            LowRes12Tracks_poll_33hz(helper,done);
            break;
        case StandardRes1Tracks:
            StandardRes1Tracks_poll_33hz(helper,done);
            break;
        case StandardRes2Tracks:
            StandardRes2Tracks_poll_33hz(helper,done);
            break;
        }
    }
    /// Handle identify global.
    /// @param registry_entry The event registry entry.
    /// @param event The event report.
    /// @param done  Notification object.
    /// @returns nothing.
    void handle_identify_global(const openlcb::EventRegistryEntry &registry_entry, 
                                openlcb::EventReport *event, 
                                BarrierNotifiable *done) override
    {
        if (event->dst_node && event->dst_node != node_)
        {
            return done->notify();
        }
        sendProducerIdentified(event,done);
        done->maybe_done();
    }
    /// Handle identify producer.
    /// @param registry_entry The event registry entry.
    /// @param event The event report.
    /// @param done  Notification object.
    /// @returns nothing.
    void handle_identify_producer(const openlcb::EventRegistryEntry &registry_entry, 
                                  openlcb::EventReport *event, 
                                  BarrierNotifiable *done) override
    {
        if (event->dst_node && event->dst_node != node_)
        {
            return done->notify();
        }
        sendProducerIdentified(event,done);
        done->maybe_done();
    }
private:
    void LowRes12Tracks_poll_33hz(openlcb::WriteHelper *helper, Notifiable *done)
    {
        switch (state_)
        {
        case Idle:
            if (rir4a_->detOccupied(1))
            {
                state_ = Track1;
                sendEventReport(activated_,helper,done);
            }
            else if (rir4a_->detOccupied(3))
            {
                state_ = Track2;
                sendEventReport(activated_,helper,done);
            }
            else
            {
                done->notify();
            }
            break;
        case Track1:
            if (rir4a_->detOccupied(3))
            {
                state_ = Track2;
            }
            else if (rir4a_->detOccupied(2))
            {
                state_ = Track1Wait;
            }
            done->notify();
            break;
        case Track1Wait:
            if (rir4a_->detOccupied(3))
            {
                state_ = Track2;
                done->notify();
            }
            else if (rir4a_->deVacant(2))
            {
                state_ = Idle;
                sendEventReport(deactivated_,helper,done);
            }
            else
            {
                done->notify();
            }
            break;
        case Track2:
            if (rir4a_->detOccupied(1))
            {
                state_ = Track1;
            }
            else if (rir4a_->detOccupied(4))
            {
                state_ = Track2Wait;
            }
            done->notify();
            break;
        case Track2Wait:
            if (rir4a_->detOccupied(1))
            {
                state_ = Track1;
                done->notify();
            }
            else if (rir4a_->deVacant(4))
            {
                state_ = Idle;
                sendEventReport(deactivated_,helper,done);
            }
            else
            {
                done->notify();
            }
            break;
        }
    }
    void StandardRes1Tracks_poll_33hz(openlcb::WriteHelper *helper, Notifiable *done)
    {
    }
    void StandardRes2Tracks_poll_33hz(openlcb::WriteHelper *helper, Notifiable *done)
    {
    }
    /// Register event handlers.
    void register_event_handler()
    {
        openlcb::EventRegistry::instance()->register_handler(openlcb::EventRegistryEntry(this,activated_), 0);
        openlcb::EventRegistry::instance()->register_handler(openlcb::EventRegistryEntry(this,deactivated_), 0);
    }
    /// Unregister event handlers.
    void unregister_event_handler()
    {
        openlcb::EventRegistry::instance()->unregister_handler(this);
    }
    void sendEventReport(const openlcb::EventId event,
                         openlcb::WriteHelper *helper, 
                         Notifiable *done)
    {
        helper->WriteAsync(node_, openlcb::Defs::MTI_EVENT_REPORT,
                           openlcb::WriteHelper::global(), 
                           openlcb::eventid_to_buffer(event), done);
    }
    void sendProducerIdentified(openlcb::EventReport *event,
                                BarrierNotifiable *done)
    {
        openlcb::Defs::MTI mti = openlcb::Defs::MTI_PRODUCER_IDENTIFIED_VALID;
        if (state_ != Idle)
        {
            event->event_write_helper<1>()->WriteAsync(node_, mti,
                  openlcb::WriteHelper::global(),
                  openlcb::eventid_to_buffer(activated_),
                  done->new_child());
        }
        else
        {
            event->event_write_helper<1>()->WriteAsync(node_, mti,
                  openlcb::WriteHelper::global(),
                  openlcb::eventid_to_buffer(deactivated__),
                  done->new_child());
        }
        mti = openlcb::Defs::MTI_PRODUCER_IDENTIFIED_INVALID;
        if (state_ == Idle)
        {
            event->event_write_helper<2>()->WriteAsync(node_, mti,
                  openlcb::WriteHelper::global(),
                  openlcb::eventid_to_buffer(activated_),
                  done->new_child());
        }
        else
        {
            event->event_write_helper<2>()->WriteAsync(node_, mti,
                  openlcb::WriteHelper::global(),
                  openlcb::eventid_to_buffer(deactivated__),
                  done->new_child());
        }
    }
    /// Node.
    openlcb::Node *node_;
    /// Configuration.
    const AzatraxRIR4CrossingConfig cfg_;
    /// Sensor chips
    azatrax::Azatrax *rir4a_;
    azatrax::Azatrax *rir4b_;
    openlcb::EventId activated_;
    openlcb::EventId deactivated__;
    States state_;
    Modes mode_;
};
    
#endif // __AZATRAXRIR4CROSSING_HXX

