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
    class:      Minefield_State_PDU
    DIS:        (6) 1278.1a - 1998
    created:    13/04/2010
    author:     Karl Jones

    purpose:    Provides information about the complete minefield. The minefield presence,
                perimeter, protocol mode, and the types of mines contained within the minefield.

    size:       576 bits / 72 octets  - Min size
*********************************************************************/

#pragma once

#include "./Minefield_Header.h"
#include "./../../DataTypes/EntityType.h"
#include "./../../DataTypes/WorldCoordinates.h"
#include "./../../DataTypes/EulerAngles.h"
#include "./../../DataTypes/MinefieldAppearance.h"
#include "./../../DataTypes/PerimeterPointCoordinate.h"
#include <vector>

namespace KDIS {
namespace PDU {

using KDIS::DATA_TYPE::EntityType;
using KDIS::DATA_TYPE::WorldCoordinates;
using KDIS::DATA_TYPE::EulerAngles;
using KDIS::DATA_TYPE::MinefieldAppearance;
using KDIS::DATA_TYPE::PerimeterPointCoordinate;
using KDIS::DATA_TYPE::EntityType;
using KDIS::DATA_TYPE::EntityIdentifier;
using KDIS::DATA_TYPE::ENUMS::ForceID;
using KDIS::DATA_TYPE::ENUMS::MinefieldProtocolMode;
using std::vector;

class KDIS_EXPORT Minefield_State_PDU : public Minefield_Header
{
protected:

    union
    {
        struct
        {
            KUINT16 m_ui16Reserved : 1;
            KUINT16 m_ui16SeqNum15 : 15;
        };
        KUINT16 m_ui16SeqNum;
    } m_SeqNumUnion;

    KUINT8 m_ui8ForceID;

    KUINT8 m_ui8NumPerimPoints;

    EntityType m_MinefieldType;

    KUINT16 m_ui16NumMineTypes;

    WorldCoordinates m_Loc;

    EulerAngles m_Ori;

    MinefieldAppearance m_App;

    union
    {
        struct
        {
            KUINT16 m_ui16ProtocolMode2 : 2;
            KUINT16 m_ui16Reserved      : 14;
        };
        KUINT16 m_ui16ProtocolMode16;
    } m_ui16ProtocolModeUnion;

    vector<PerimeterPointCoordinate> m_vPoints;

    vector<EntityType> m_vMineTypes;

public:

    static const KUINT16 MINEFIELD_STATE_PDU_SIZE = 72; // Min size

    Minefield_State_PDU( void );

    Minefield_State_PDU( const EntityIdentifier & ID, KUINT16 SequenceNumber, ForceID FID, const EntityType & Type,
                         const WorldCoordinates & Loc, const EulerAngles & Ori, const MinefieldAppearance & MA,
                         MinefieldProtocolMode MPM );

    Minefield_State_PDU( KDataStream & stream ) throw( KException );

    virtual ~Minefield_State_PDU( void );

    //************************************
    // FullName:    KDIS::PDU::Minefield_State_PDU::SetSequenceNumber
    //              KDIS::PDU::Minefield_State_PDU::GetSequenceNumber
    // Description: Specifies a change in state of a minefield as a result of a
    //              change in minefield information or a change in the state,
    //              in accordance with the rules specified in 5.9.2.3(IEEE 1278.1a).
    // Parameter:   KUINT16 S, void
    //************************************
    void SetSequenceNumber( KUINT16 S );
    KUINT16 GetSequenceNumber() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_State_PDU::SetForceID
    //              KDIS::PDU::Minefield_State_PDU::GetForceID
    // Description: Force ID. Enumerated value representing the force the minefield belongs to,
    //              such as friendly, opposing or neutral.
    // Parameter:   ForceID ID, void
    //************************************
    void SetForceID( ForceID ID );
    ForceID GetForceID() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_State_PDU::GetNumberOfPerimeterPoints
    // Description: Number of points in the perimeter of the minefield.
    //************************************
    KUINT8 GetNumberOfPerimeterPoints() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_State_PDU::SetMinefieldType
    //              KDIS::PDU::Minefield_State_PDU::GetMinefieldType
    // Description: Identifies the minefield type of the issuing minefield.
    //              Consists of 7 values used to represent the type of minefield.
    //              Please see DIS Enums document found on the SISO website for a full list of enumerations available.
    //              See 6.2.30(IEEE 1278.1) and Section 4 of SISO-REF-010.
    // Parameter:   const EntityType & Type, void
    //************************************
    void SetMinefieldType( const EntityType & Type );
    const EntityType & GetMinefieldType() const;
    EntityType & GetMinefieldType();

    //************************************
    // FullName:    KDIS::PDU::Minefield_State_PDU::GetNumberOfMineTypes
    // Description: The number of different mine types employed in the minefield.
    //************************************
    KUINT8 GetNumberOfMineTypes() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_State_PDU::SetMinefieldLocation
    //              KDIS::PDU::Minefield_State_PDU::GetMinefieldLocation
    // Description: Location of the center of the minefield in Geocentric world coordinates.
    //              Note: See KConversions.h for some useful coordinate conversions.
    // Parameter:   const WorldCoordinates & L, void
    //************************************
    void SetMinefieldLocation( const WorldCoordinates & L );
    const WorldCoordinates & GetMinefieldLocation() const;
    WorldCoordinates & GetMinefieldLocation();

    //************************************
    // FullName:    KDIS::PDU::Minefield_State_PDU::SetMinefieldOrientation
    //              KDIS::PDU::Minefield_State_PDU::GetMinefieldOrientation
    // Description: Orientation of minefield. Geocentric Euler Angles.
    //              Note: See KConversions.h for some useful orientation conversions.
    // Parameter:   const EulerAngles & O, void
    //************************************
    void SetMinefieldOrientation( const EulerAngles & O );
    const EulerAngles & GetMinefieldOrientation() const;
    EulerAngles & GetMinefieldOrientation();

    //************************************
    // FullName:    KDIS::PDU::Minefield_State_PDU::SetMinefieldAppearance
    //              KDIS::PDU::Minefield_State_PDU::GetMinefieldAppearance
    // Description: The appearance of the minefield.
    // Parameter:   const MinefieldAppearance & MA, void
    //************************************
    void SetMinefieldAppearance( const MinefieldAppearance & MA );
    const MinefieldAppearance & GetMinefieldAppearance() const;
    MinefieldAppearance & GetMinefieldAppearance();

    //************************************
    // FullName:    KDIS::PDU::Minefield_State_PDU::SetMinefieldProtocolMode
    //              KDIS::PDU::Minefield_State_PDU::GetMinefieldProtocolMode
    // Description: Specifies which protocol mode is being used to communicate the minefield data.
    // Parameter:   MinefieldProtocolMode MPM, void
    //************************************
    void SetMinefieldProtocolMode( MinefieldProtocolMode MPM );
    MinefieldProtocolMode GetMinefieldProtocolMode() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_State_PDU::AddPerimeterPointCoordinate
    //              KDIS::PDU::Minefield_State_PDU::SetPerimeterPointCoordinates
    //              KDIS::PDU::Minefield_State_PDU::GetPerimeterPointCoordinates
    // Description: Specifies the location of each perimeter point, relative to
    //              the Minefield Location field.
    //              Only the x and y coordinates of each perimeter point shall be specified.
    // Parameter:   const PerimeterPointCoordinate & PPC, vector<PerimeterPointCoordinate> & PPC, void
    //************************************
    void AddPerimeterPointCoordinate( const PerimeterPointCoordinate & PPC );
    void SetPerimeterPointCoordinates( const vector<PerimeterPointCoordinate> & PPC );
    const vector<PerimeterPointCoordinate> & GetPerimeterPointCoordinates() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_State_PDU::AddMineType
    //              KDIS::PDU::Minefield_State_PDU::SetMineTypes
    //              KDIS::PDU::Minefield_State_PDU::GetMineTypes
    // Description: Specifies the type of each mine contained within the minefield.
    // Parameter:   const EntityType & MT, vector<EntityType> & MT, void
    //************************************
    void AddMineType( const EntityType & MT );
    void SetMineTypes( const vector<EntityType> & MT );
    const vector<EntityType> & GetMineTypes() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_State_PDU::GetAsString
    // Description: Returns a string representation of the PDU.
    //************************************
    virtual KString GetAsString() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_State_PDU::Decode
    // Description: Convert From Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual void Decode( KDataStream & stream ) throw( KException );

    //************************************
    // FullName:    KDIS::PDU::Minefield_State_PDU::Encode
    // Description: Convert To Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual KDataStream Encode() const;
    virtual void Encode( KDataStream & stream ) const;

    KBOOL operator == ( const Minefield_State_PDU & Value ) const;
    KBOOL operator != ( const Minefield_State_PDU & Value ) const;
};

}; // END namespace PDU
}; // END namespace KDIS
