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
    class:      Remove_Entity_R_PDU
    DIS:        (6) 1278.1A - 1998
    created:    2009/03/21
    author:     Karl Jones

    purpose:    Sent when a entity is removed
    size:       256 bits / 34 octets
*********************************************************************/

#pragma once

#include "./Create_Entity_R_PDU.h"

namespace KDIS {
namespace PDU {

using KDIS::DATA_TYPE::EntityIdentifier;
using KDIS::DATA_TYPE::ENUMS::RequiredReliabilityService;

class KDIS_EXPORT Remove_Entity_R_PDU : public Create_Entity_R_PDU
{
public:

    static const KUINT16 REMOVE_ENTITY_R_PDU_SIZE = 32;

    Remove_Entity_R_PDU( void );

    Remove_Entity_R_PDU( KDataStream & stream ) throw( KException );

    Remove_Entity_R_PDU( const EntityIdentifier & OrigintatingID, const EntityIdentifier & ReceivingID,
                         KUINT32 RequestID, RequiredReliabilityService RRS );

    Remove_Entity_R_PDU( const Simulation_Management_Header & SimMgrHeader,
                         KUINT32 RequestID, RequiredReliabilityService RRS );

    virtual ~Remove_Entity_R_PDU( void );

    //************************************
    // FullName:    KDIS::PDU::Remove_Entity_R_PDU::GetAsString
    // Description: Returns a string representation
    //              of the PDU.
    //************************************
    virtual KString GetAsString() const;

    KBOOL operator == ( const Remove_Entity_R_PDU & Value ) const;
    KBOOL operator != ( const Remove_Entity_R_PDU & Value ) const;
};

}; // END namespace PDU
}; // END namespace KDIS