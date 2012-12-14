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
    class:      Resupply_Received_PDU
    DIS:        (5) 1278.1 - 1995
    created:    2008/09/22
    author:     Karl Jones

    purpose:    Resupply Received PDU
    Size:       224 bits / 28 octets + ( 96 bits / 12 octets * ( number of supplies ) )
*********************************************************************/

#pragma once

#include "./Logistics_Header.h"

namespace KDIS {
namespace PDU {

using KDIS::DATA_TYPE::EntityIdentifier;

class KDIS_EXPORT Resupply_Cancel_PDU : public Logistics_Header
{
public:

    static const KUINT16 RESUPPLY_CANCEL_PDU_SIZE = 24;

    Resupply_Cancel_PDU( void );

    Resupply_Cancel_PDU( const EntityIdentifier & ReceivingEntity, const EntityIdentifier & SupplyingEntity );

    Resupply_Cancel_PDU( KDataStream & stream ) throw( KException );

    virtual ~Resupply_Cancel_PDU( void );

    //************************************
    // FullName:    KDIS::PDU::Resupply_Cancel_PDU::GetAsString
    // Description: Returns a string representation
    //              of the PDU.
    //************************************
    virtual KString GetAsString() const;

    KBOOL operator == ( const Resupply_Cancel_PDU & Value ) const;
    KBOOL operator != ( const Resupply_Cancel_PDU & Value ) const;
};

}; // END namespace PDU
}; // END namespace KDIS
