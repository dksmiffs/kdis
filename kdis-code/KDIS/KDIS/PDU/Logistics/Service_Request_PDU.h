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
    class:      Service_Request_PDU
    DIS:        (5) 1278.1 - 1995
    created:    2008/09/22
    author:     Karl Jones

    purpose:    Service Request PDU
    Size:       224 bits / 28 octets + ( 96 bits / 12 octets * ( number of supplies ) )
*********************************************************************/

#pragma once

#include "./Resupply_Received_PDU.h"

namespace KDIS {
namespace PDU {

using KDIS::DATA_TYPE::EntityIdentifier;
using KDIS::DATA_TYPE::ENUMS::ServiceTypeRequested;

class KDIS_EXPORT Service_Request_PDU : public Resupply_Received_PDU
{
protected:

    KUINT8 m_ui8ServiceTypeRequested;

public:

    // Min Size the PDU can be, size can be more depending on NumSupplyTypes field
    static const KUINT16 SERVICE_REQUEST_PDU_SIZE = 28; // Does not include supply size

    Service_Request_PDU( void );

    Service_Request_PDU( KDataStream & stream ) throw( KException );

    Service_Request_PDU( const EntityIdentifier & ReceivingEntity, const EntityIdentifier & SupplyingEntity, ServiceTypeRequested STR );

    virtual ~Service_Request_PDU( void );

    //************************************
    // FullName:    KDIS::PDU::Service_Request_PDU::SetServiceTypeRequested
    //              KDIS::PDU::Service_Request_PDU::GetServiceTypeRequested
    // Description: Describes type of service being requested
    // Parameter:   ServiceTypeRequested  STR, void
    //************************************
    void SetServiceTypeRequested( ServiceTypeRequested STR );
    ServiceTypeRequested GetServiceTypeRequested() const;

    //************************************
    // FullName:    KDIS::PDU::Service_Request_PDU::GetAsString
    // Description: Returns a string representation
    //              of the PDU.
    //************************************
    virtual KString GetAsString() const;

    //************************************
    // FullName:    KDIS::PDU::Service_Request_PDU::Decode
    // Description: Convert From Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual void Decode( KDataStream & stream ) throw( KException );

    //************************************
    // FullName:    KDIS::PDU::Service_Request_PDU::Encode
    // Description: Convert To Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual KDataStream Encode() const;
    virtual void Encode( KDataStream & stream ) const;

    KBOOL operator == ( const Service_Request_PDU & Value ) const;
    KBOOL operator != ( const Service_Request_PDU & Value ) const;
};

}; // END namespace PDU
}; // END namespace KDIS