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

#include "./Minefield_State_PDU.h"

//////////////////////////////////////////////////////////////////////////

using namespace KDIS;
using namespace PDU;
using namespace DATA_TYPE;
using namespace std;
using namespace ENUMS;
using namespace UTILS;

//////////////////////////////////////////////////////////////////////////
// public:
//////////////////////////////////////////////////////////////////////////

Minefield_State_PDU::Minefield_State_PDU( void ) :
    m_ui8ForceID( 0 ),
    m_ui8NumPerimPoints( 0 ),
    m_ui16NumMineTypes( 0 )
{
    m_ui8PDUType = MinefieldState_PDU_Type;
    m_ui16PDULength = MINEFIELD_STATE_PDU_SIZE;
    m_SeqNumUnion.m_ui16SeqNum = 0;
    m_ui16ProtocolModeUnion.m_ui16ProtocolMode16 = 0;
}

//////////////////////////////////////////////////////////////////////////

Minefield_State_PDU::Minefield_State_PDU( const EntityIdentifier & ID, KUINT16 SequenceNumber, ForceID FID, const EntityType & Type,
        const WorldCoordinates & Loc, const EulerAngles & Ori, const MinefieldAppearance & MA,
        MinefieldProtocolMode MPM ) :
    m_ui8ForceID( FID ),
    m_ui8NumPerimPoints( 0 ),
    m_ui16NumMineTypes( 0 ),
    m_MinefieldType( Type ),
    m_Loc( Loc ),
    m_Ori( Ori ),
    m_App( MA )
{
    m_ui8PDUType = MinefieldState_PDU_Type;
    m_ui16PDULength = MINEFIELD_STATE_PDU_SIZE;
    m_SeqNumUnion.m_ui16SeqNum = SequenceNumber;
    m_ui16ProtocolModeUnion.m_ui16ProtocolMode16 = MPM;
    m_MinefieldID = ID;
}

//////////////////////////////////////////////////////////////////////////

Minefield_State_PDU::Minefield_State_PDU( KDataStream & stream ) throw( KException )
{
    try
    {
        Decode( stream );
    }
    catch ( KException & e )
    {
        throw e;
    }
}

//////////////////////////////////////////////////////////////////////////

Minefield_State_PDU::~Minefield_State_PDU( void )
{
}

//////////////////////////////////////////////////////////////////////////

void Minefield_State_PDU::SetSequenceNumber( KUINT16 S )
{
    m_SeqNumUnion.m_ui16SeqNum15 = S;
}

//////////////////////////////////////////////////////////////////////////

KUINT16 Minefield_State_PDU::GetSequenceNumber() const
{
    return m_SeqNumUnion.m_ui16SeqNum15;
}

//////////////////////////////////////////////////////////////////////////

void Minefield_State_PDU::SetForceID( ForceID ID )
{
    m_ui8ForceID = ID;
}

//////////////////////////////////////////////////////////////////////////

ForceID Minefield_State_PDU::GetForceID() const
{
    return ( ForceID )m_ui8ForceID;
}

//////////////////////////////////////////////////////////////////////////

KUINT8 Minefield_State_PDU::GetNumberOfPerimeterPoints() const
{
    return m_ui8NumPerimPoints;
}

//////////////////////////////////////////////////////////////////////////

void Minefield_State_PDU::SetMinefieldType( const EntityType & Type )
{
    m_MinefieldType = Type;
}

//////////////////////////////////////////////////////////////////////////

const EntityType & Minefield_State_PDU::GetMinefieldType() const
{
    return m_MinefieldType;
}

//////////////////////////////////////////////////////////////////////////

EntityType & Minefield_State_PDU::GetMinefieldType()
{
    return m_MinefieldType;
}

//////////////////////////////////////////////////////////////////////////

KUINT8 Minefield_State_PDU::GetNumberOfMineTypes() const
{
    return m_ui16NumMineTypes;
}

//////////////////////////////////////////////////////////////////////////

void Minefield_State_PDU::SetMinefieldLocation( const WorldCoordinates & L )
{
    m_Loc = L;
}

//////////////////////////////////////////////////////////////////////////

const WorldCoordinates & Minefield_State_PDU::GetMinefieldLocation() const
{
    return m_Loc;
}

//////////////////////////////////////////////////////////////////////////

WorldCoordinates & Minefield_State_PDU::GetMinefieldLocation()
{
    return m_Loc;
}

//////////////////////////////////////////////////////////////////////////

void Minefield_State_PDU::SetMinefieldOrientation( const EulerAngles & O )
{
    m_Ori = O;
}

//////////////////////////////////////////////////////////////////////////

const EulerAngles & Minefield_State_PDU::GetMinefieldOrientation() const
{
    return m_Ori;
}

//////////////////////////////////////////////////////////////////////////

EulerAngles & Minefield_State_PDU::GetMinefieldOrientation()
{
    return m_Ori;
}

//////////////////////////////////////////////////////////////////////////

void Minefield_State_PDU::SetMinefieldAppearance( const MinefieldAppearance & MA )
{
    m_App = MA;
}

//////////////////////////////////////////////////////////////////////////

const MinefieldAppearance & Minefield_State_PDU::GetMinefieldAppearance() const
{
    return m_App;
}

//////////////////////////////////////////////////////////////////////////

MinefieldAppearance & Minefield_State_PDU::GetMinefieldAppearance()
{
    return m_App;
}

//////////////////////////////////////////////////////////////////////////

void Minefield_State_PDU::SetMinefieldProtocolMode( MinefieldProtocolMode MPM )
{
    m_ui16ProtocolModeUnion.m_ui16ProtocolMode2 = MPM;
}

//////////////////////////////////////////////////////////////////////////

MinefieldProtocolMode Minefield_State_PDU::GetMinefieldProtocolMode() const
{
    return ( MinefieldProtocolMode )m_ui16ProtocolModeUnion.m_ui16ProtocolMode2;
}

//////////////////////////////////////////////////////////////////////////

void Minefield_State_PDU::AddPerimeterPointCoordinate( const PerimeterPointCoordinate & PPC )
{
    m_vPoints.push_back( PPC );
    m_ui16PDULength += PerimeterPointCoordinate::PERIMETER_POINT_COORDINATE_SIZE;
    ++m_ui8NumPerimPoints;
}

//////////////////////////////////////////////////////////////////////////

void Minefield_State_PDU::SetPerimeterPointCoordinates( const vector<PerimeterPointCoordinate> & PPC )
{
    // Subtract old values from pdu length.
    m_ui16PDULength -= m_ui8NumPerimPoints * PerimeterPointCoordinate::PERIMETER_POINT_COORDINATE_SIZE;

    m_vPoints = PPC;
    m_ui8NumPerimPoints = m_vPoints.size();

    // Calculate the new size
    m_ui16PDULength += m_ui8NumPerimPoints * PerimeterPointCoordinate::PERIMETER_POINT_COORDINATE_SIZE;
}

//////////////////////////////////////////////////////////////////////////

const vector<PerimeterPointCoordinate> & Minefield_State_PDU::GetPerimeterPointCoordinates() const
{
    return m_vPoints;
}

//////////////////////////////////////////////////////////////////////////

void Minefield_State_PDU::AddMineType( const EntityType & MT )
{
    m_vMineTypes.push_back( MT );
    m_ui16PDULength += EntityType::ENTITY_TYPE_SIZE;
    ++m_ui16NumMineTypes;
}

//////////////////////////////////////////////////////////////////////////

void Minefield_State_PDU::SetMineTypes( const vector<EntityType> & MT )
{
    // Subtract old values from pdu length.
    m_ui16PDULength -= m_ui16NumMineTypes * EntityType::ENTITY_TYPE_SIZE;

    m_vMineTypes = MT;
    m_ui16NumMineTypes = m_vMineTypes.size();

    // Calculate the new size
    m_ui16PDULength += m_ui16NumMineTypes * EntityType::ENTITY_TYPE_SIZE;
}

//////////////////////////////////////////////////////////////////////////

const vector<EntityType> & Minefield_State_PDU::GetMineTypes() const
{
    return m_vMineTypes;
}

//////////////////////////////////////////////////////////////////////////

KString Minefield_State_PDU::GetAsString() const
{
    KStringStream ss;

    ss << Header::GetAsString()
       << "-Minefield State PDU-\n"
       << Minefield_Header::GetAsString()
       << "Sequence Number:     " << m_SeqNumUnion.m_ui16SeqNum15           << "\n"
       << "Force ID:            " << GetEnumAsStringForceID( m_ui8ForceID ) << "\n"
       << "Number Perim Points: " << ( KUINT16 )m_ui8NumPerimPoints         << "\n"
       << "Minefield Type:      " << m_MinefieldType.GetAsString()
       << "Number Mine Types:   " << m_ui16NumMineTypes                     << "\n"
       << "Minefield Location:  " << m_Loc.GetAsString()
       << "Orientation:         " << m_Ori.GetAsString()
       << m_App.GetAsString()
       << "Protocol Mode:       " << GetEnumAsStringMinefieldProtocolMode( m_ui16ProtocolModeUnion.m_ui16ProtocolMode2 ) << "\n"
       << "Perimeter Points:\n";

    std::vector<PerimeterPointCoordinate>::const_iterator citrPnt = m_vPoints.begin();
    std::vector<PerimeterPointCoordinate>::const_iterator citrEndPnt = m_vPoints.end();
    for( ; citrPnt != citrEndPnt; ++citrPnt )
    {
        ss << IndentString( citrPnt->GetAsString(), 1 );
    }

    ss << "Mine Types:\n";

    std::vector<EntityType>::const_iterator citrTyp = m_vMineTypes.begin();
    std::vector<EntityType>::const_iterator citrEndTyp = m_vMineTypes.end();
    for( ; citrTyp != citrEndTyp; ++citrTyp )
    {
        ss << IndentString( citrTyp->GetAsString(), 1 );
    }

    return ss.str();
}

//////////////////////////////////////////////////////////////////////////

void Minefield_State_PDU::Decode( KDataStream & stream ) throw( KException )
{
    if( stream.GetBufferSize() < MINEFIELD_STATE_PDU_SIZE )throw KException( __FUNCTION__, NOT_ENOUGH_DATA_IN_BUFFER );

    m_vPoints.clear();
    m_vMineTypes.clear();

    Minefield_Header::Decode( stream );

    stream >> m_SeqNumUnion.m_ui16SeqNum
           >> m_ui8ForceID
           >> m_ui8NumPerimPoints
           >> KDIS_STREAM m_MinefieldType
           >> m_ui16NumMineTypes
           >> KDIS_STREAM m_Loc
           >> KDIS_STREAM m_Ori
           >> KDIS_STREAM m_App
           >> m_ui16ProtocolModeUnion.m_ui16ProtocolMode16;

    for( KUINT8 i = 0; i < m_ui8NumPerimPoints; ++i )
    {
        m_vPoints.push_back( PerimeterPointCoordinate( stream ) );
    }

    for( KUINT16 j = 0; j < m_ui16NumMineTypes; ++j )
    {
        m_vMineTypes.push_back( EntityType( stream ) );
    }
}

//////////////////////////////////////////////////////////////////////////

KDataStream Minefield_State_PDU::Encode() const
{
    KDataStream stream;

    Minefield_State_PDU::Encode( stream );

    return stream;
}

//////////////////////////////////////////////////////////////////////////

void Minefield_State_PDU::Encode( KDataStream & stream ) const
{
    Minefield_Header::Encode( stream );

    stream << m_SeqNumUnion.m_ui16SeqNum
           << m_ui8ForceID
           << m_ui8NumPerimPoints
           << KDIS_STREAM m_MinefieldType
           << m_ui16NumMineTypes
           << KDIS_STREAM m_Loc
           << KDIS_STREAM m_Ori
           << KDIS_STREAM m_App
           << m_ui16ProtocolModeUnion.m_ui16ProtocolMode16;

    std::vector<PerimeterPointCoordinate>::const_iterator citrPnt = m_vPoints.begin();
    std::vector<PerimeterPointCoordinate>::const_iterator citrEndPnt = m_vPoints.end();
    for( ; citrPnt != citrEndPnt; ++citrPnt )
    {
        citrPnt->Encode( stream );
    }

    std::vector<EntityType>::const_iterator citrTyp = m_vMineTypes.begin();
    std::vector<EntityType>::const_iterator citrEndTyp = m_vMineTypes.end();
    for( ; citrTyp != citrEndTyp; ++citrTyp )
    {
        citrTyp->Encode( stream );
    }
}

//////////////////////////////////////////////////////////////////////////

KBOOL Minefield_State_PDU::operator == ( const Minefield_State_PDU & Value ) const
{
    if( Minefield_Header::operator  != ( Value ) )                          return false;
    if( m_SeqNumUnion.m_ui16SeqNum  != Value.m_SeqNumUnion.m_ui16SeqNum )   return false;
    if( m_ui8ForceID                != Value.m_ui8ForceID )                 return false;
    if( m_ui8NumPerimPoints         != Value.m_ui8NumPerimPoints )          return false;
    if( m_MinefieldType             != Value.m_MinefieldType )              return false;
    if( m_ui16NumMineTypes          != Value.m_ui16NumMineTypes )           return false;
    if( m_Loc                       != Value.m_Loc )                        return false;
    if( m_Ori                       != Value.m_Ori )                        return false;
    if( m_App                       != Value.m_App )                        return false;
    if( m_ui16ProtocolModeUnion.m_ui16ProtocolMode16 != Value.m_ui16ProtocolModeUnion.m_ui16ProtocolMode16 ) return false;
    if( m_vPoints                   != Value.m_vPoints )                    return false;
    if( m_vMineTypes                != Value.m_vMineTypes )                 return false;
    return true;
}

//////////////////////////////////////////////////////////////////////////

KBOOL Minefield_State_PDU::operator != ( const Minefield_State_PDU & Value ) const
{
    return !( *this == Value );
}

//////////////////////////////////////////////////////////////////////////
