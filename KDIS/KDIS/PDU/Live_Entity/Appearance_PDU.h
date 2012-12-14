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
    class:      Appearance_PDU
    DIS:        (6) 1278.1a - 1998
    created:    04/07/2010
    author:     Karl Jones

    purpose:    The Appearance PDU communicates information about the appearance
                of an Live Entity. This includes state information that is
                necessary for the receiving simulation applications to represent
                the issuing entity�s appearance in the simulation application�s own simulation.

    size:       136 bits / 17 octets - Min size
*********************************************************************/

#pragma once

#include "./LE_Header.h"
#include "./../../DataTypes/EntityType.h"
#include "./../../DataTypes/EntityMarking.h"
#include "./../../DataTypes/EntityCapabilities.h"
#include "./../../DataTypes/EntityAppearance.h"

namespace KDIS {
namespace PDU {

using KDIS::DATA_TYPE::EntityType;
using KDIS::DATA_TYPE::EntityMarking;
using KDIS::DATA_TYPE::EntityCapabilities;
using KDIS::DATA_TYPE::EntityAppearance;
using KDIS::DATA_TYPE::ENUMS::ForceID;

class KDIS_EXPORT Appearance_PDU : public LE_Header
{
protected:

    union
    {
        struct
        {
            KUINT8 m_ui8ForceId : 1;
            KUINT8 m_ui8Typ     : 1;
            KUINT8 m_ui8AltTyp  : 1;
            KUINT8 m_ui8Mark    : 1;
            KUINT8 m_ui8Cap     : 1;
            KUINT8 m_ui8Vis     : 1;
            KUINT8 m_ui8IR      : 1;
            KUINT8 m_ui8Flag2   : 1;
        };
        KUINT8 m_ui8Flag;
    } m_AppearanceFlag1Union;

    union
    {
        struct
        {
            KUINT8 m_ui8EM       : 1;
            KUINT8 m_ui8Audio    : 1;
            KUINT8 m_ui8Unused   : 5;
            KUINT8 m_ui8Reserved : 1;
        };
        KUINT8 m_ui8Flag;
    } m_AppearanceFlag2Union;

    KUINT8 m_ui8ForceID;

    EntityType m_EntityType;

    EntityType m_AltEntityType;

    EntityMarking m_EntityMarking;

    EntityCapabilities m_EntityCapabilities;

    EntityAppearance m_VisApp;

    EntityAppearance m_IRApp;

    EntityAppearance m_EMApp;

    EntityAppearance m_AudApp;

public:

    static const KUINT16 APPEARANCE_PDU_SIZE = 17; // Min size, not including optional fields

    Appearance_PDU( void );

    Appearance_PDU( const LE_EntityIdentifier & ID );

    Appearance_PDU( KDataStream & stream ) throw( KException );

    virtual ~Appearance_PDU( void );

    //************************************
    // FullName:    KDIS::PDU::Appearance_PDU::SetForceIDFlag
    //              KDIS::PDU::Appearance_PDU::GetForceIDFlag
    //              KDIS::PDU::Appearance_PDU::SetEntityTypeFlag
    //              KDIS::PDU::Appearance_PDU::GetEntityTypeFlag
    //              KDIS::PDU::Appearance_PDU::SetAlternateEntityTypeFlag
    //              KDIS::PDU::Appearance_PDU::GetAlternateEntityTypeFlag
    //              KDIS::PDU::Appearance_PDU::SetEntityMarkingFlag
    //              KDIS::PDU::Appearance_PDU::GetEntityMarkingFlag
    //              KDIS::PDU::Appearance_PDU::SetCapabilitiesFlag
    //              KDIS::PDU::Appearance_PDU::GetCapabilitiesFlag
    //              KDIS::PDU::Appearance_PDU::SetAppearanceVisualFlag
    //              KDIS::PDU::Appearance_PDU::GetAppearanceVisualFlag
    //              KDIS::PDU::Appearance_PDU::SetAppearanceIRFlag
    //              KDIS::PDU::Appearance_PDU::GetAppearanceIRFlag
    //              KDIS::PDU::Appearance_PDU::SetFlag2Flag
    //              KDIS::PDU::Appearance_PDU::GetFlag2Flag
    //              KDIS::PDU::Appearance_PDU::SetAppearanceEMFlag
    //              KDIS::PDU::Appearance_PDU::GetAppearanceEMFlag
    //              KDIS::PDU::Appearance_PDU::SetAppearanceAudioFlag
    //              KDIS::PDU::Appearance_PDU::GetAppearanceAudioFlag
    // Description: Identifies optional data fields that are being transmitted with
    //              this PDU.
    //              Note setting Appearance EM flag and Appearance Audio flag
    //              will automatically set Flag2 flag.
    // Parameter:   KBOOL F
    //************************************
    void SetForceIDFlag( KBOOL F );
    KBOOL GetForceIDFlag() const;
    void SetEntityTypeFlag( KBOOL F );
    KBOOL GetEntityTypeFlag() const;
    void SetAlternateEntityTypeFlag( KBOOL F );
    KBOOL GetAlternateEntityTypeFlag() const;
    void SetEntityMarkingFlag( KBOOL F );
    KBOOL GetEntityMarkingFlag() const;
    void SetCapabilitiesFlag( KBOOL F );
    KBOOL GetCapabilitiesFlag() const;
    void SetAppearanceVisualFlag( KBOOL F );
    KBOOL GetAppearanceVisualFlag() const;
    void SetAppearanceIRFlag( KBOOL F );
    KBOOL GetAppearanceIRFlag() const;
    void SetFlag2Flag( KBOOL F );
    KBOOL GetFlag2Flag() const;
    void SetAppearanceEMFlag( KBOOL F );
    KBOOL GetAppearanceEMFlag() const;
    void SetAppearanceAudioFlag( KBOOL F );
    KBOOL GetAppearanceAudioFlag()const;

    //************************************
    // FullName:    KDIS::PDU::Appearance_PDU::SetForceID
    //              KDIS::PDU::Appearance_PDU::GetForceID
    // Description: Optional field. Force ID. Enumerated value representing the force the entity belongs to,
    //              such as friendly, opposing or neutral.
    //              Note: Setting this value will also cause the relevant flag to be set to true.
    // Parameter:   ForceID ID
    //************************************
    void SetForceID( ForceID ID );
    ForceID GetForceID() const;

    //************************************
    // FullName:    KDIS::PDU::Appearance_PDU::SetEntityType
    //              KDIS::PDU::Appearance_PDU::GetEntityType
    // Description: Optional field. Entity Type. Consists of 7 values used to represent
    //              the type of entity. Please see DIS Enums document found on
    //              the SISO website for a full list of enumerations available.
    //              Note: Setting this value will also cause the relevant flag to be set to true.
    // Parameter:   const EntityType & Type
    //************************************
    void SetEntityType( const EntityType & Type );
    const EntityType & GetEntityType() const;
    EntityType & GetEntityType();

    //************************************
    // FullName:    KDIS::PDU::Appearance_PDU::SetAltEntityType
    //              KDIS::PDU::Appearance_PDU::GetAltEntityType
    // Description: Optional field. This identifies the entity type to be displayed by members of forces
    //              other than that of the issuing entity.
    //              I.E This could be used to represent an entity in disguise.
    //              Note: Setting this value will also cause the relevant flag to be set to true.
    // Parameter:   const EntityType & Type
    //************************************
    void SetAltEntityType( const EntityType & Type );
    const EntityType & GetAltEntityType() const;
    EntityType & GetAltEntityType();

    //************************************
    // FullName:    KDIS::PDU::Appearance_PDU::SetEntityMarking
    //              KDIS::PDU::Appearance_PDU::GetEntityMarking
    // Description: Optional field. Entity Marking. This can be the entities name,Army Markings or Chevrons.
    //              Note: Setting this value will also cause the relevant flag to be set to true.
    // Parameter:   const EntityMarking & EM, void
    //************************************
    void SetEntityMarking( const EntityMarking & EM );
    const EntityMarking & GetEntityMarking() const;
    EntityMarking & GetEntityMarking();

    //************************************
    // FullName:    KDIS::PDU::Appearance_PDU::SetEntityCapabilities
    //              KDIS::PDU::Appearance_PDU::GetEntityCapabilities
    // Description: Optional field. Entity Capabilities. Such as has fuel/ammo supply etc.
    //              Note: Setting this value will also cause the relevant flag to be set to true.
    // Parameter:   const EntityCapabilities & EC
    //************************************
    void SetEntityCapabilities( const EntityCapabilities & EC );
    const EntityCapabilities & GetEntityCapabilities() const;
    EntityCapabilities & GetEntityCapabilities();

    //************************************
    // FullName:    KDIS::PDU::Appearance_PDU::SetAppearanceVisual
    //              KDIS::PDU::Appearance_PDU::GetAppearanceVisual
    // Description: Optional field. Specifies the dynamic changes to the entity�s visual appearance attributes.
    //              Note: Setting this value will also cause the relevant flag to be set to true.
    // Parameter:   const EntityAppearance & V
    //************************************
    void SetAppearanceVisual( const EntityAppearance & V );
    const EntityAppearance & GetAppearanceVisual() const;
    EntityAppearance & GetAppearanceVisual();

    //************************************
    // FullName:    KDIS::PDU::Appearance_PDU::SetAppearanceIR
    //              KDIS::PDU::Appearance_PDU::GetAppearanceIR
    // Description: Optional field. Specifies the dynamic changes to the entity�s infrared appearance attributes.
    //              Note: Setting this value will also cause the relevant flag to be set to true.
    // Parameter:   const EntityAppearance & IR
    //************************************
    void SetAppearanceIR( const EntityAppearance & IR );
    const EntityAppearance & GetAppearanceIR() const;
    EntityAppearance & GetAppearanceIR();

    //************************************
    // FullName:    KDIS::PDU::Appearance_PDU::SetAppearanceEM
    //              KDIS::PDU::Appearance_PDU::GetAppearanceEM
    // Description: Optional field. Specifies the dynamic changes to the entity�s electromagnetic appearance attributes.
    //              Note: Setting this value will also cause the relevant flags to be set to true.
    // Parameter:   const EntityAppearance & EM
    //************************************
    void SetAppearanceEM( const EntityAppearance & EM );
    const EntityAppearance & GetAppearanceEM() const;
    EntityAppearance & GetAppearanceEM();

    //************************************
    // FullName:    KDIS::PDU::Appearance_PDU::SetAppearanceAudio
    //              KDIS::PDU::Appearance_PDU::GetAppearanceAudio
    // Description: Optional field. Specifies the dynamic changes to the entity�s acoustic appearance attributes.
    //              Note: Setting this value will also cause the relevant flags to be set to true.
    // Parameter:   const EntityAppearance & A
    //************************************
    void SetAppearanceAudio( const EntityAppearance & A );
    const EntityAppearance & GetAppearanceAudio() const;
    EntityAppearance & GetAppearanceAudio();

    //************************************
    // FullName:    KDIS::PDU::Appearance_PDU::GetAsString
    // Description: Returns a string representation of the PDU
    //************************************
    virtual KString GetAsString() const;

    //************************************
    // FullName:    KDIS::PDU::Appearance_PDU::Decode
    // Description: Convert From Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual void Decode( KDataStream & stream ) throw( KException );

    //************************************
    // FullName:    KDIS::PDU::Appearance_PDU::Encode
    // Description: Convert To Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual KDataStream Encode() const;
    virtual void Encode( KDataStream & stream ) const;

    KBOOL operator == ( const Appearance_PDU & Value ) const;
    KBOOL operator != ( const Appearance_PDU & Value ) const;
};

}; // END namespace PDU
}; // END namespace KDIS
