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

#include "./Intercom_Control_PDU.h"

//////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace KDIS;
using namespace PDU;
using namespace DATA_TYPE;
using namespace ENUMS;
using namespace UTILS;

//////////////////////////////////////////////////////////////////////////
// public:
//////////////////////////////////////////////////////////////////////////

Intercom_Control_PDU::Intercom_Control_PDU( void ) :
    m_ui8Command( 0 )
{
    m_ui8PDUType = IntercomControl_PDU_Type;
    m_ui16PDULength = INTERCOM_CONTROL_PDU_SIZE;
}

//////////////////////////////////////////////////////////////////////////

Intercom_Control_PDU::Intercom_Control_PDU( KDataStream & stream ) throw( KException )
{
    Decode( stream );
}

//////////////////////////////////////////////////////////////////////////

Intercom_Control_PDU::~Intercom_Control_PDU( void )
{
    m_vICP.clear();
}

//////////////////////////////////////////////////////////////////////////

void Intercom_Control_PDU::SetControlType( ControlType CT )
{
    m_ui8CtrlTyp = CT;
}

//////////////////////////////////////////////////////////////////////////

ControlType Intercom_Control_PDU::GetControlType() const
{
    return ( ControlType )m_ui8CtrlTyp;
}

//////////////////////////////////////////////////////////////////////////

void Intercom_Control_PDU::SetCommunicationsChannelType( const CommunicationsChannelType & CCT )
{
    m_CommChannelType = CCT;
}

//////////////////////////////////////////////////////////////////////////

const CommunicationsChannelType & Intercom_Control_PDU::GetCommunicationsChannelType() const
{
    return m_CommChannelType;
}

//////////////////////////////////////////////////////////////////////////

CommunicationsChannelType & Intercom_Control_PDU::GetCommunicationsChannelType()
{
    return m_CommChannelType;
}

//////////////////////////////////////////////////////////////////////////

void Intercom_Control_PDU::SetSourceEntityID ( const EntityIdentifier & ID )
{
    m_SrcEnt = ID;
}

//////////////////////////////////////////////////////////////////////////

const EntityIdentifier & Intercom_Control_PDU::GetSourceEntityID() const
{
    return m_SrcEnt;
}

//////////////////////////////////////////////////////////////////////////

EntityIdentifier & Intercom_Control_PDU::GetSourceEntityID()
{
    return m_SrcEnt;
}

//////////////////////////////////////////////////////////////////////////

void Intercom_Control_PDU::SetSourceCommDeviceID( KUINT16 ID )
{
    m_ui16SrcCommDevID = ID;
}

//////////////////////////////////////////////////////////////////////////

KUINT16 Intercom_Control_PDU::GetSourceCommDeviceID() const
{
    return m_ui16SrcCommDevID;
}

//////////////////////////////////////////////////////////////////////////

void Intercom_Control_PDU::SetSourceLineID( KUINT8 ID )
{
    m_ui8SrcLineID = ID;
}

//////////////////////////////////////////////////////////////////////////

KUINT8 Intercom_Control_PDU::GetSourceLineID() const
{
    return m_ui8SrcLineID;
}

//////////////////////////////////////////////////////////////////////////

void Intercom_Control_PDU::SetTransmitPriority( KUINT8 TP )
{
    m_ui8TransmitPriority = TP;
}

//////////////////////////////////////////////////////////////////////////

KUINT8 Intercom_Control_PDU::GetTransmitPriority() const
{
    return m_ui8TransmitPriority;
}

//////////////////////////////////////////////////////////////////////////

void Intercom_Control_PDU::SetTransmitLineState( TransmitLineState TLS )
{
    m_ui8TransmitLineState= TLS;
}

//////////////////////////////////////////////////////////////////////////

TransmitLineState Intercom_Control_PDU::GetTransmitLineState() const
{
    return ( TransmitLineState )m_ui8TransmitLineState;
}

//////////////////////////////////////////////////////////////////////////

void Intercom_Control_PDU::SetLineStateCommand( LineStateCommand LSC )
{
    m_ui8Command = LSC;
}

//////////////////////////////////////////////////////////////////////////

LineStateCommand Intercom_Control_PDU::GetLineStateCommand() const
{
    return ( LineStateCommand )m_ui8Command;
}

//////////////////////////////////////////////////////////////////////////

void Intercom_Control_PDU::SetMasterEntityID ( const EntityIdentifier & ID )
{
    m_MstrEntID = ID;
}

//////////////////////////////////////////////////////////////////////////

const EntityIdentifier & Intercom_Control_PDU::GetMasterEntityID() const
{
    return m_MstrEntID;
}

//////////////////////////////////////////////////////////////////////////

EntityIdentifier & Intercom_Control_PDU::GetMasterEntityID()
{
    return m_MstrEntID;
}

//////////////////////////////////////////////////////////////////////////

void Intercom_Control_PDU::SetMasterCommDeviceID( KUINT16 ID )
{
    m_ui16MstrCommDeviceID = ID;
}

//////////////////////////////////////////////////////////////////////////

KUINT16 Intercom_Control_PDU::GetMasterCommDeviceID() const
{
    return m_ui16MstrCommDeviceID;
}

//////////////////////////////////////////////////////////////////////////

void Intercom_Control_PDU::SetMasterChannelID( KUINT16 ID )
{
    m_ui16MstrChannelID = ID;
}

//////////////////////////////////////////////////////////////////////////

KUINT16 Intercom_Control_PDU::GetMasterChannelID() const
{
    return m_ui16MstrChannelID;
}

//////////////////////////////////////////////////////////////////////////

KUINT32 Intercom_Control_PDU::GetIntercomParametersLength() const
{
    return m_ui32IntrParamLen;
}

//////////////////////////////////////////////////////////////////////////

void Intercom_Control_PDU::AddIntercomCommunicationParameters( const IntercomCommunicationParameters & ICP )
{
    m_ui16PDULength += ICP.GetLength() + IntercomCommunicationParameters::INTERCOM_COMMS_PARAM_SIZE;
    m_vICP.push_back( ICP );
}

//////////////////////////////////////////////////////////////////////////

void Intercom_Control_PDU::SetIntercomCommunicationParameters( const vector<IntercomCommunicationParameters> & ICP )
{
    m_ui16PDULength = INTERCOM_CONTROL_PDU_SIZE;

    m_vICP = ICP;

    vector<IntercomCommunicationParameters>::const_iterator citr = m_vICP.begin();
    vector<IntercomCommunicationParameters>::const_iterator citrEnd = m_vICP.end();

    for( ; citr != citrEnd; ++citr )
    {
        // Calculate the PDU length.
        m_ui16PDULength += citr->GetLength() + IntercomCommunicationParameters::INTERCOM_COMMS_PARAM_SIZE;
    }
}

//////////////////////////////////////////////////////////////////////////

const vector<IntercomCommunicationParameters> & Intercom_Control_PDU::GetIntercomCommunicationParameters() const
{
    return m_vICP;
}

//////////////////////////////////////////////////////////////////////////

KString Intercom_Control_PDU::GetAsString() const
{
    KStringStream ss;

    ss << Header::GetAsString()
       << "-Intercom Control PDU-\n"
       << "Control Type:				     " << GetEnumAsStringControlType( m_ui8CtrlTyp ) << "\n"
       << m_CommChannelType.GetAsString()
       << "Source Entity:\n"
       << IndentString( m_SrcEnt.GetAsString(), 1 )
       << "Source Communications Device ID:  " << m_ui16SrcCommDevID                << "\n"
       << "Source Line ID:                   " << ( KUINT16 )m_ui8SrcLineID         << "\n"
       << "Transmit Priority:                " << ( KUINT16 )m_ui8TransmitPriority  << "\n"
       << "Transmit Line State:              " << GetEnumAsStringTransmitLineState( m_ui8TransmitLineState ) << "\n"
       << "Command:                          " << GetEnumAsStringLineStateCommand( m_ui8Command )            << "\n"
       << "Master Entity ID:\n"
       << m_MstrEntID.GetAsString()
       << "Master Communications Device ID:  " << m_ui16MstrCommDeviceID            << "\n"
       << "Master Channel ID:                " << m_ui16MstrChannelID               << "\n"
       << "Intercom Parameter Length:        " << m_ui32IntrParamLen                << "\n";

    vector<IntercomCommunicationParameters>::const_iterator citr = m_vICP.begin();
    vector<IntercomCommunicationParameters>::const_iterator citrEnd = m_vICP.end();
    for( ; citr != citrEnd; ++citr )
    {
        ss << citr->GetAsString();
    }

    return ss.str();
}

//////////////////////////////////////////////////////////////////////////

void Intercom_Control_PDU::Decode( KDataStream & stream ) throw( KException )
{
    if( stream.GetBufferSize() < INTERCOM_CONTROL_PDU_SIZE )throw KException( __FUNCTION__, NOT_ENOUGH_DATA_IN_BUFFER );

    Header::Encode( stream );

    stream >> m_ui8CtrlTyp
           >> KDIS_STREAM m_CommChannelType
           >> KDIS_STREAM m_SrcEnt
           >> m_ui16SrcCommDevID
           >> m_ui8SrcLineID
           >> m_ui8TransmitPriority
           >> m_ui8TransmitLineState
           >> m_ui8Command
           >> KDIS_STREAM m_MstrEntID
           >> m_ui16MstrCommDeviceID
           >> m_ui16MstrChannelID
           >> m_ui32IntrParamLen;

    m_vICP.clear();

    // Using the parameter length field to decode each parameter.
    KUINT32 ParamLength = m_ui32IntrParamLen;

    while( ParamLength )
    {
        IntercomCommunicationParameters icp( stream );

        m_vICP.push_back( icp );

        ParamLength -= icp.GetLength() + IntercomCommunicationParameters::INTERCOM_COMMS_PARAM_SIZE;
    }
}

//////////////////////////////////////////////////////////////////////////

KDataStream Intercom_Control_PDU::Encode() const
{
    KDataStream stream;

    Intercom_Control_PDU::Encode( stream );

    return stream;
}

//////////////////////////////////////////////////////////////////////////

void Intercom_Control_PDU::Encode( KDataStream & stream ) const
{
    Header::Encode( stream );

    stream << m_ui8CtrlTyp
           << KDIS_STREAM m_CommChannelType
           << KDIS_STREAM m_SrcEnt
           << m_ui16SrcCommDevID
           << m_ui8SrcLineID
           << m_ui8TransmitPriority
           << m_ui8TransmitLineState
           << m_ui8Command
           << KDIS_STREAM m_MstrEntID
           << m_ui16MstrCommDeviceID
           << m_ui16MstrChannelID
           << m_ui32IntrParamLen;

    vector<IntercomCommunicationParameters>::const_iterator citr = m_vICP.begin();
    vector<IntercomCommunicationParameters>::const_iterator citrEnd = m_vICP.end();

    for( ; citr != citrEnd; ++citr )
    {
        stream << KDIS_STREAM *citr;
    }
}

//////////////////////////////////////////////////////////////////////////

KBOOL Intercom_Control_PDU::operator == ( const Intercom_Control_PDU & Value ) const
{
    if( Header::operator        !=( Value ) )                     return false;
    if( m_ui8CtrlTyp            != Value.m_ui8CtrlTyp )           return false;
    if( m_CommChannelType       != Value.m_CommChannelType )      return false;
    if( m_SrcEnt                != Value.m_SrcEnt )               return false;
    if( m_ui16SrcCommDevID      != Value.m_ui16SrcCommDevID )     return false;
    if( m_ui8SrcLineID          != Value.m_ui8SrcLineID )         return false;
    if( m_ui8TransmitPriority   != Value.m_ui8TransmitPriority )  return false;
    if( m_ui8TransmitLineState  != Value.m_ui8TransmitLineState ) return false;
    if( m_ui8Command            != Value.m_ui8Command )           return false;
    if( m_MstrEntID             != Value.m_MstrEntID )            return false;
    if( m_ui16MstrCommDeviceID  != Value.m_ui16MstrCommDeviceID ) return false;
    if( m_ui16MstrChannelID     != Value.m_ui16MstrChannelID )    return false;
    if( m_ui32IntrParamLen      != Value.m_ui32IntrParamLen )     return false;
    if( m_vICP                  != Value.m_vICP )                 return false;
    return true;
}

//////////////////////////////////////////////////////////////////////////

KBOOL Intercom_Control_PDU::operator != ( const Intercom_Control_PDU & Value ) const
{
    return !( *this == Value );
}

//////////////////////////////////////////////////////////////////////////

