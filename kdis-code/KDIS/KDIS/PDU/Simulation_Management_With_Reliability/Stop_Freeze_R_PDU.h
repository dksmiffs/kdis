/*********************************************************************
KDIS is free software; you can redistribute it and/or modify it under the
terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option)
any later version.

KDIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along
with this library; if not, write to the Free Software Foundation, Inc.,
59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.

For Further Information Please Contact me at
Karljj1@yahoo.com
http://p.sf.net/kdis/UserGuide
*********************************************************************/

/********************************************************************
    class:      Stop_Freeze_R_PDU
    DIS:        (6) 1278.1A - 1998
    created:    21:03:2009
    author:     Karl Jones

    purpose:    Indicates the stopping/freezing of an entity/exercise
    size:       352 bits / 44 octets
*********************************************************************/

#pragma once

#include "./../Simulation_Management/Stop_Freeze_PDU.h"
#include "./Reliability_Header.h"

namespace KDIS {
namespace PDU {

using KDIS::DATA_TYPE::EntityIdentifier;
using KDIS::DATA_TYPE::ClockTime;
using KDIS::DATA_TYPE::ENUMS::StopFreezeReason;
using KDIS::DATA_TYPE::ENUMS::FrozenBehavior;
using KDIS::DATA_TYPE::ENUMS::RequiredReliabilityService;

class KDIS_EXPORT Stop_Freeze_R_PDU : public Stop_Freeze_PDU,
    public Reliability_Header
{
public:

    static const KUINT16 STOP_FREEZE_R_PDU_SIZE = 44;

    Stop_Freeze_R_PDU( void );

    Stop_Freeze_R_PDU( KDataStream & stream ) throw( KException );

    Stop_Freeze_R_PDU( const EntityIdentifier & ReceivingEntity, const EntityIdentifier & SupplyingEntity, const ClockTime & RealWorldTime,
                       StopFreezeReason SFR, FrozenBehavior FB, KUINT32 ReqID, RequiredReliabilityService RRS );

    Stop_Freeze_R_PDU( const Simulation_Management_Header & SimMgrHeader, const ClockTime & RealWorldTime,
                       StopFreezeReason SFR, FrozenBehavior FB, KUINT32 ReqID, RequiredReliabilityService RRS );

    virtual ~Stop_Freeze_R_PDU( void );

    //************************************
    // FullName:    KDIS::PDU::Stop_Freeze_R_PDU::GetAsString
    // Description: Returns a string representation
    //              of the PDU.
    //************************************
    virtual KString GetAsString() const;

    //************************************
    // FullName:    KDIS::PDU::Stop_Freeze_R_PDU::Decode
    // Description: Convert From Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual void Decode( KDataStream & stream ) throw( KException );

    //************************************
    // FullName:    KDIS::PDU::Stop_Freeze_R_PDU::Encode
    // Description: Convert To Network Data.
    //************************************
    virtual KDataStream Encode() const;
    virtual void Encode( KDataStream & stream ) const;

    KBOOL operator == ( const Stop_Freeze_R_PDU & Value ) const;
    KBOOL operator != ( const Stop_Freeze_R_PDU & Value ) const;
};

}; // END namespace PDU
}; // END namespace KDIS