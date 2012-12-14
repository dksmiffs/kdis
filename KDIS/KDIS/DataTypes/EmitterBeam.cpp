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

#include "./EmitterBeam.h"

//////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace KDIS;
using namespace DATA_TYPE;
using namespace ENUMS;
using namespace UTILS;

//////////////////////////////////////////////////////////////////////////
// Public:
//////////////////////////////////////////////////////////////////////////

EmitterBeam::EmitterBeam( void )  :
    m_ui8Padding( 0 ),
    m_ui8BeamDataLength( EMITTER_BEAM_SIZE / 4  ),
    m_ui8NumTargetInTrackJamField( 0 )
{
}

//////////////////////////////////////////////////////////////////////////

EmitterBeam::EmitterBeam( KDataStream & stream ) throw( KException )
{
    Decode( stream );
}

//////////////////////////////////////////////////////////////////////////

EmitterBeam::EmitterBeam( KUINT8 BeamID, KUINT16 BeamParamIndex, const FundamentalParameterData & FPD,
                          EmitterFunction EBF, HighDensityTrackJam HDTJ,
                          KUINT32 JammingModeSequence ) :
    m_ui8Padding( 0 ),
    m_ui8BeamDataLength( EMITTER_BEAM_SIZE / 4  ),
    m_ui8NumTargetInTrackJamField( 0 ),
    m_ui8EmitterBeamIDNumber( BeamID ),
    m_ui16BeamParamIndex( BeamParamIndex ),
    m_FundamentalParameterData( FPD ),
    m_ui8BeamFunction( EBF ),
    m_ui8HighDensityTrackJam( HDTJ ),
    m_ui32JammingModeSequence( JammingModeSequence )
{
}

//////////////////////////////////////////////////////////////////////////

EmitterBeam::~EmitterBeam( void )
{
    m_vTrackJamTargets.clear();
}

//////////////////////////////////////////////////////////////////////////

KUINT8 EmitterBeam::GetBeamDataLength() const
{
    return m_ui8BeamDataLength;
}

//////////////////////////////////////////////////////////////////////////

void EmitterBeam::SetEmitterBeamIDNumber( KUINT8 ID )
{
    m_ui8EmitterBeamIDNumber = ID;
}

//////////////////////////////////////////////////////////////////////////

KUINT8 EmitterBeam::GetEmitterBeamIDNumber() const
{
    return m_ui8EmitterBeamIDNumber;
}

//////////////////////////////////////////////////////////////////////////

void EmitterBeam::SetBeamParamIndex( KUINT16 BPI )
{
    m_ui16BeamParamIndex = BPI;
}

//////////////////////////////////////////////////////////////////////////

KUINT16 EmitterBeam::GetBeamParamIndex() const
{
    return m_ui16BeamParamIndex;
}

//////////////////////////////////////////////////////////////////////////

void EmitterBeam::SetFundamentalParameterData( const FundamentalParameterData & FPD )
{
    m_FundamentalParameterData = FPD;
}

//////////////////////////////////////////////////////////////////////////

const FundamentalParameterData & EmitterBeam::GetFundamentalParameterData() const
{
    return m_FundamentalParameterData;
}

//////////////////////////////////////////////////////////////////////////

FundamentalParameterData & EmitterBeam::GetFundamentalParameterData()
{
    return m_FundamentalParameterData;
}

//////////////////////////////////////////////////////////////////////////

void EmitterBeam::SetEmitterBeamFunction( EmitterFunction EBF )
{
    m_ui8BeamFunction;
}

//////////////////////////////////////////////////////////////////////////

EmitterFunction EmitterBeam::GetEmitterBeamFunction() const
{
    return ( EmitterFunction )m_ui8BeamFunction;
}

//////////////////////////////////////////////////////////////////////////

KUINT8 EmitterBeam::GetNumTargetInTrackJamField() const
{
    return m_ui8NumTargetInTrackJamField;
}

//////////////////////////////////////////////////////////////////////////

void EmitterBeam::SetHighDensityTrackJam( HighDensityTrackJam HDTJ )
{
    m_ui8HighDensityTrackJam = HDTJ;
}

//////////////////////////////////////////////////////////////////////////

HighDensityTrackJam EmitterBeam::GetHighDensityTrackJam() const
{
    return ( HighDensityTrackJam )m_ui8HighDensityTrackJam;
}

//////////////////////////////////////////////////////////////////////////

void EmitterBeam::SetJammingModeSequence( KUINT32 JMS )
{
    m_ui32JammingModeSequence = JMS;
}

//////////////////////////////////////////////////////////////////////////

KUINT32 EmitterBeam::GetJammingModeSequence() const
{
    return m_ui32JammingModeSequence;
}

//////////////////////////////////////////////////////////////////////////


void EmitterBeam::AddTrackedJammedTarget( const TrackJamTargetIdentifier & ID )
{
    m_vTrackJamTargets.push_back( ID );
    m_ui8NumTargetInTrackJamField = m_vTrackJamTargets.size();
    m_ui8BeamDataLength += TrackJamTargetIdentifier::TRACK_JAM_TARGET_SIZE / 4;
}

//////////////////////////////////////////////////////////////////////////

void EmitterBeam::SetTrackedJammedTargets( const std::vector<TrackJamTargetIdentifier> & ID )
{
    m_vTrackJamTargets = ID;
    m_ui8NumTargetInTrackJamField = m_vTrackJamTargets.size();
    m_ui8BeamDataLength = ( EMITTER_BEAM_SIZE + ( TrackJamTargetIdentifier::TRACK_JAM_TARGET_SIZE * m_ui8NumTargetInTrackJamField ) ) / 4;
}

//////////////////////////////////////////////////////////////////////////

const vector<TrackJamTargetIdentifier> & EmitterBeam::GetTrackedJammedTargets() const
{
    return m_vTrackJamTargets;
}

//////////////////////////////////////////////////////////////////////////

void EmitterBeam::ClearTrackedJammedTargets()
{
    m_vTrackJamTargets.clear();
    m_ui8NumTargetInTrackJamField = 0;
    m_ui8BeamDataLength = EMITTER_BEAM_SIZE;
}

//////////////////////////////////////////////////////////////////////////

KString EmitterBeam::GetAsString() const
{
    KStringStream ss;

    ss << "Emitter Beam:\n\t"
       << "\n\tBeam Data Length (32bits):        " << ( KUINT16 )m_ui8BeamDataLength
       << "\n\tEmitter Beam ID Number:           " << ( KUINT16 )m_ui8EmitterBeamIDNumber
       << "\n\tBeam Parameter Index:             " << m_ui16BeamParamIndex
       << IndentString( m_FundamentalParameterData.GetAsString(), 1 )
       << "\tBeam Function:                    "   << GetEnumAsStringEmitterFunction( m_ui8BeamFunction )
       << "\n\tNumber Of Targets Tracked/Jammed: " << ( KUINT16 )m_ui8NumTargetInTrackJamField
       << "\n\tHigh Density Track/Jam:           " <<  GetEnumAsStringHighDensityTrackJam( m_ui8HighDensityTrackJam )
       << "\n\tJamming Mode Sequence:            " << m_ui32JammingModeSequence
       << "\n\tTracked/Jammed Targets:\n";

    vector<TrackJamTargetIdentifier>::const_iterator citr = m_vTrackJamTargets.begin();
    vector<TrackJamTargetIdentifier>::const_iterator citrEnd = m_vTrackJamTargets.end();
    for( ; citr != citrEnd; ++ citr )
    {
        ss << "Target:\n"
           << IndentString( citr->GetAsString(), 1 );
    }

    return ss.str();
}

//////////////////////////////////////////////////////////////////////////

void EmitterBeam::Decode( KDataStream & stream ) throw( KException )
{
    if( stream.GetBufferSize() < EMITTER_BEAM_SIZE )throw KException( __FUNCTION__, NOT_ENOUGH_DATA_IN_BUFFER );

    stream >> m_ui8BeamDataLength
           >> m_ui8EmitterBeamIDNumber
           >> m_ui16BeamParamIndex
           >> KDIS_STREAM m_FundamentalParameterData
           >> m_ui8BeamFunction
           >> m_ui8NumTargetInTrackJamField
           >> m_ui8HighDensityTrackJam
           >> m_ui8Padding
           >> m_ui32JammingModeSequence;

    for( KUINT8 i = 0; i < m_ui8NumTargetInTrackJamField; ++i )
    {
        m_vTrackJamTargets.push_back( TrackJamTargetIdentifier( stream ) );
    }
}

//////////////////////////////////////////////////////////////////////////

KDataStream EmitterBeam::Encode() const
{
    KDataStream stream;

    EmitterBeam::Encode( stream );

    return stream;
}

//////////////////////////////////////////////////////////////////////////

void EmitterBeam::Encode( KDataStream & stream ) const
{
    stream << m_ui8BeamDataLength
           << m_ui8EmitterBeamIDNumber
           << m_ui16BeamParamIndex
           << KDIS_STREAM m_FundamentalParameterData
           << m_ui8BeamFunction
           << m_ui8NumTargetInTrackJamField
           << m_ui8HighDensityTrackJam
           << m_ui8Padding
           << m_ui32JammingModeSequence;

    vector<TrackJamTargetIdentifier>::const_iterator citr = m_vTrackJamTargets.begin();
    vector<TrackJamTargetIdentifier>::const_iterator citrEnd = m_vTrackJamTargets.end();

    for( ; citr != citrEnd; ++citr )
    {
        citr->Encode( stream );
    }
}

//////////////////////////////////////////////////////////////////////////

KBOOL EmitterBeam::operator == ( const EmitterBeam & Value ) const
{
    if( m_ui8BeamDataLength             != Value.m_ui8BeamDataLength )           return false;
    if( m_ui8EmitterBeamIDNumber        != Value.m_ui8EmitterBeamIDNumber )      return false;
    if( m_ui16BeamParamIndex            != Value.m_ui16BeamParamIndex )          return false;
    if( m_FundamentalParameterData      != Value.m_FundamentalParameterData )    return false;
    if( m_ui8BeamFunction               != Value.m_ui8BeamFunction )             return false;
    if( m_ui8NumTargetInTrackJamField   != Value.m_ui8NumTargetInTrackJamField ) return false;
    if( m_ui8HighDensityTrackJam        != Value.m_ui8HighDensityTrackJam )      return false;
    if( m_ui32JammingModeSequence       != Value.m_ui32JammingModeSequence )     return false;
    if( m_vTrackJamTargets              != Value.m_vTrackJamTargets )            return false;
    return true;
}

//////////////////////////////////////////////////////////////////////////

KBOOL EmitterBeam::operator != ( const EmitterBeam & Value ) const
{
    return !( *this == Value );
}

//////////////////////////////////////////////////////////////////////////
