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

#include "./Gridded_Data_PDU.h"

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

Gridded_Data_PDU::Gridded_Data_PDU( void ) :
    m_ui16FieldNum( 0 ),
    m_ui16PDUNum( 0 ),
    m_ui16PDUTotal( 0 ),
    m_ui16CordSys( 0 ),
    m_ui8NumAxis( 0 ),
    m_ui8ConstGrid( 0 ),
    m_ui64SampleTime( 0 ),
    m_ui32TotalValues( 0 ),
    m_ui8VecDim( 0 ),
    m_ui16Padding1( 0 ),
    m_ui8Padding1( 0 )
{
    m_ui8ProtocolFamily = SyntheticEnvironment;
    m_ui8PDUType = GriddedData_PDU_Type;
    m_ui16PDULength = GRIDDED_DATA_PDU_SIZE;
    m_ui8ProtocolVersion = IEEE_1278_1A_1998;
}

//////////////////////////////////////////////////////////////////////////

Gridded_Data_PDU::Gridded_Data_PDU( KDataStream & stream ) throw( KException )
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

Gridded_Data_PDU::Gridded_Data_PDU( const EntityIdentifier & EnvironmentalProcessID, KUINT16 FieldNumber, KUINT16 PduNum,
                                    KUINT16 PduTotal, CoordinateSystem CS, ConstantGrid CG, const EnvironmentType & ET,
                                    const EulerAngles & Ori, KUINT64 SampleTime ) :
    m_EnvProcID( EnvironmentalProcessID ),
    m_ui16FieldNum( FieldNumber ),
    m_ui16PDUNum( PduNum ),
    m_ui16PDUTotal( PduTotal ),
    m_ui16CordSys( CS ),
    m_ui8NumAxis( 0 ),
    m_ui8ConstGrid( CG ),
    m_EnvType( ET ),
    m_Ori( Ori ),
    m_ui64SampleTime( SampleTime ),
    m_ui32TotalValues( 0 ),
    m_ui8VecDim( 0 ),
    m_ui16Padding1( 0 ),
    m_ui8Padding1( 0 )
{
    m_ui8ProtocolFamily = SyntheticEnvironment;
    m_ui8PDUType = GriddedData_PDU_Type;
    m_ui16PDULength = GRIDDED_DATA_PDU_SIZE;
    m_ui8ProtocolVersion = IEEE_1278_1A_1998;
}

//////////////////////////////////////////////////////////////////////////

Gridded_Data_PDU::~Gridded_Data_PDU( void )
{
}

//////////////////////////////////////////////////////////////////////////

void Gridded_Data_PDU::SetEnvironmentalProcessID( const EntityIdentifier & ID )
{
    m_EnvProcID = ID;
}

//////////////////////////////////////////////////////////////////////////

const EntityIdentifier & Gridded_Data_PDU::GetEnvironmentalProcessID() const
{
    return m_EnvProcID;
}

//////////////////////////////////////////////////////////////////////////

EntityIdentifier & Gridded_Data_PDU::GetEnvironmentalProcessID()
{
    return m_EnvProcID;
}

//////////////////////////////////////////////////////////////////////////

void Gridded_Data_PDU::SetFieldNumber( KUINT16 FN )
{
    m_ui16FieldNum = FN;
}

//////////////////////////////////////////////////////////////////////////

KUINT16 Gridded_Data_PDU::GetFieldNumber() const
{
    return m_ui16FieldNum;
}

//////////////////////////////////////////////////////////////////////////

void Gridded_Data_PDU::SetPDUNumber( KUINT16 PN )
{
    m_ui16PDUNum = PN;
}

//////////////////////////////////////////////////////////////////////////

KUINT16 Gridded_Data_PDU::GetPDUNumber() const
{
    return m_ui16PDUNum;
}

//////////////////////////////////////////////////////////////////////////

void Gridded_Data_PDU::SetPDUNumberAndTotal( KUINT16 Num, KUINT16 Total ) throw( KException )
{
    if( Num > Total )throw KException( __FUNCTION__, INVALID_DATA, "PDU Number can not be greater than PDU Total" );
    m_ui16PDUNum = Num;
    m_ui16PDUTotal = Total;
}

//////////////////////////////////////////////////////////////////////////

void Gridded_Data_PDU::SetPDUTotal( KUINT16 PT )
{
    m_ui16PDUTotal = PT;
}

//////////////////////////////////////////////////////////////////////////

KUINT16 Gridded_Data_PDU::GetPDUTotal() const
{
    return m_ui16PDUTotal;
}

//////////////////////////////////////////////////////////////////////////

void Gridded_Data_PDU::SetCoordinateSystem( CoordinateSystem CS )
{
    m_ui16CordSys = CS;
}

//////////////////////////////////////////////////////////////////////////

CoordinateSystem Gridded_Data_PDU::GetCoordinateSystem() const
{
    return ( CoordinateSystem )m_ui16CordSys;
}

//////////////////////////////////////////////////////////////////////////

KUINT8 Gridded_Data_PDU::GetNumberAxis() const
{
    return m_ui8NumAxis;
}

//////////////////////////////////////////////////////////////////////////

void Gridded_Data_PDU::SetConstantGrid( ConstantGrid CG )
{
    m_ui8ConstGrid = CG;
}

//////////////////////////////////////////////////////////////////////////

ConstantGrid Gridded_Data_PDU::GetConstantGrid() const
{
    return ( ConstantGrid )m_ui8ConstGrid;
}

//////////////////////////////////////////////////////////////////////////

void Gridded_Data_PDU::SetEnvironmentType( const EnvironmentType & ET )
{
    m_EnvType= ET;
}

//////////////////////////////////////////////////////////////////////////

const EnvironmentType & Gridded_Data_PDU::GetEnvironmentType() const
{
    return m_EnvType;
}

//////////////////////////////////////////////////////////////////////////

EnvironmentType & Gridded_Data_PDU::GetEnvironmentType()
{
    return m_EnvType;
}

//////////////////////////////////////////////////////////////////////////

void Gridded_Data_PDU::SetOrientation( const EulerAngles & O )
{
    m_Ori = O;
}

//////////////////////////////////////////////////////////////////////////

const EulerAngles & Gridded_Data_PDU::GetOrientation() const
{
    return m_Ori;
}

//////////////////////////////////////////////////////////////////////////

EulerAngles & Gridded_Data_PDU::GetOrientation()
{
    return m_Ori;
}

//////////////////////////////////////////////////////////////////////////

void Gridded_Data_PDU::SetSampleTime( KUINT64 ST )
{
    m_ui64SampleTime = ST;
}

//////////////////////////////////////////////////////////////////////////

KUINT64 Gridded_Data_PDU::GetSampleTime() const
{
    return m_ui64SampleTime;
}

//////////////////////////////////////////////////////////////////////////

void Gridded_Data_PDU::SetTotalValues( KUINT32 TV )
{
    m_ui32TotalValues = TV;
}

//////////////////////////////////////////////////////////////////////////

KUINT32 Gridded_Data_PDU::GetTotalValues() const
{
    return m_ui32TotalValues;
}

//////////////////////////////////////////////////////////////////////////

void Gridded_Data_PDU::SetVectorDimension( KUINT8 VD )
{
    m_ui8VecDim = VD;
}

//////////////////////////////////////////////////////////////////////////

KUINT8 Gridded_Data_PDU::GetVectorDimension() const
{
    return m_ui8VecDim;
}

//////////////////////////////////////////////////////////////////////////

void Gridded_Data_PDU::AddGridAxisDescriptor( const GridAxisDescriptor & GAD )
{
    m_vpGridAxisDesc.push_back( GAD );
    ++m_ui8NumAxis;
    m_ui16PDULength += GAD->GetLength();
}

//////////////////////////////////////////////////////////////////////////

void Gridded_Data_PDU::SetGridAxisDescriptors( const std::vector<GridAxisDescriptor> & GADS )
{
    // calculate length that needs to be removed.
    vector<GridAxisDescriptor>::const_iterator citr = m_vpGridAxisDesc.begin();
    vector<GridAxisDescriptor>::const_iterator citrEnd = m_vpGridAxisDesc.end();

    for( ; citr != citrEnd; ++citr )
    {
        m_ui16PDULength -= ( *citr )->GetLength();
    }

    m_vpGridAxisDesc = GADS;
    m_ui8NumAxis = m_vpGridAxisDesc.size();

    // Calculate the new PDU length.
    citr = m_vpGridAxisDesc.begin();
    citrEnd = m_vpGridAxisDesc.end();

    for( ; citr != citrEnd; ++citr )
    {
        m_ui16PDULength += ( *citr )->GetLength();
    }
}

//////////////////////////////////////////////////////////////////////////

const std::vector<GridAxisDescriptor> & Gridded_Data_PDU::GetSetGridAxisDescriptors() const
{
    return m_vpGridAxisDesc;
}

//////////////////////////////////////////////////////////////////////////

void Gridded_Data_PDU::AddGridData( const GridDataPtr & GD )
{
    ++m_ui8VecDim;
    m_vGridData.push_back( GD );
    m_ui16PDULength += GD->GetSize();
}

//////////////////////////////////////////////////////////////////////////

void Gridded_Data_PDU::SetGridData( const std::vector<GridDataPtr> & GD )
{
    // Remove the old grid data from the PDU length.
    std::vector<GridDataPtr>::const_iterator citr = m_vGridData.begin();
    std::vector<GridDataPtr>::const_iterator citrEnd = m_vGridData.end();
    for( ; citr != citrEnd; ++citr )
    {
        m_ui16PDULength -= ( *citr )->GetSize();
    }

    m_vGridData = GD;
    m_ui8VecDim = m_vGridData.size();

    // Now recalculate the PDU length.
    citr = m_vGridData.begin();
    citrEnd = m_vGridData.end();
    for( ; citr != citrEnd; ++citr )
    {
        m_ui16PDULength += ( *citr )->GetSize();
    }
}

//////////////////////////////////////////////////////////////////////////

const std::vector<GridDataPtr> & Gridded_Data_PDU::GetGridData() const
{
    return m_vGridData;
}

//////////////////////////////////////////////////////////////////////////

KString Gridded_Data_PDU::GetAsString() const
{
    KStringStream ss;

    ss << Header::GetAsString()
       << "-Gridded Data PDU-\n"
       << "Environmental Process ID:\n"
       << m_EnvProcID.GetAsString()
       << "Field Number: "      << m_ui16FieldNum                                   << "\n"
       << "PDU Number: "        << m_ui16PDUNum                                     << "\n"
       << "PDU Total: "         << m_ui16PDUTotal                                   << "\n"
       << "Coordinate System: " << GetEnumAsStringCoordinateSystem( m_ui16CordSys ) << "\n"
       << "Number Of Axis: "    <<  ( KUINT16 )m_ui8NumAxis                         << "\n"
       << "Constant Grid: "     << GetEnumAsStringConstantGrid( m_ui8ConstGrid )    << "\n"
       << "Environment Type: "  << m_EnvType.GetAsString()
       << "Orientation: "       << m_Ori.GetAsString()
       << "Sample Time: "       << m_ui64SampleTime                                 << "\n"
       << "Total Values: "      << m_ui32TotalValues                                << "\n"
       << "Vector Dimension: "  << ( KUINT16 )m_ui8VecDim                           << "\n";

    vector<GridAxisDescriptor>::const_iterator citrAxis = m_vpGridAxisDesc.begin();
    vector<GridAxisDescriptor>::const_iterator citrAxisEnd = m_vpGridAxisDesc.end();
    for( ; citrAxis != citrAxisEnd; ++citrAxis )
    {
        ss << ( *citrAxis )->GetAsString();
    }

    vector<GridDataPtr>::const_iterator citrData = m_vGridData.begin();
    vector<GridDataPtr>::const_iterator citrDataEnd = m_vGridData.end();
    for( ; citrData != citrDataEnd; ++citrData )
    {
        ss << ( *citrData )->GetAsString();
    }

    return ss.str();
}

//////////////////////////////////////////////////////////////////////////

void Gridded_Data_PDU::Decode( KDataStream & stream ) throw( KException )
{
    if( stream.GetBufferSize() < GRIDDED_DATA_PDU_SIZE )throw KException( __FUNCTION__, NOT_ENOUGH_DATA_IN_BUFFER );

    m_vpGridAxisDesc.clear();
    m_vGridData.clear();

    Header::Decode( stream );

    stream >> KDIS_STREAM m_EnvProcID
           >> m_ui16FieldNum
           >> m_ui16PDUNum
           >> m_ui16PDUTotal
           >> m_ui16CordSys
           >> m_ui8NumAxis
           >> m_ui8ConstGrid
           >> KDIS_STREAM m_EnvType
           >> KDIS_STREAM m_Ori
           >> m_ui64SampleTime
           >> m_ui32TotalValues
           >> m_ui8VecDim
           >> m_ui16Padding1
           >> m_ui8Padding1;

    // We must first decode 4 other values before we can get to the grid axis type so
    // a special constructor is provided in the grid axis classes so that we can pass half the decoded data.
    KFLOAT64 InitialXi = 0;
    KFLOAT64 FinalXi = 0;
    KUINT16 PointsXi = 0;
    KUINT8 InterleafFactor = 0;
    KUINT8 AxisType = 0;
    for( KUINT8 i = 0; i < m_ui8NumAxis; ++i )
    {
        stream >> InitialXi
               >> FinalXi
               >> PointsXi
               >> InterleafFactor
               >> AxisType;

        if( AxisType == 0 )
        {
            // Regular grid
            m_vpGridAxisDesc.push_back( new GridAxisRegular( InitialXi, FinalXi, PointsXi, InterleafFactor, AxisType, stream ) );
        }
        else
        {
            // Irregular grid.
            m_vpGridAxisDesc.push_back( new GridAxisIrregular( InitialXi, FinalXi, PointsXi, InterleafFactor, AxisType, stream ) );
        }
    }

    // We must first decode 2 other values before we can get to the grid data type so
    // a special constructor is provided in the grid data type classes so that we can pass half the decoded data.
    KUINT16 SmpTyp = 0;
    KUINT16 DtRep = 0;

    for( KUINT8 j = 0; j < m_ui8VecDim; ++j )
    {
        stream >> SmpTyp
               >> DtRep;

        switch( DtRep )
        {
        case 0:
            m_vGridData.push_back( new GridDataType0( SmpTyp, DtRep, stream ) );
        case 1 :
            m_vGridData.push_back( new GridDataType1( SmpTyp, DtRep, stream ) );
        case 2:
            m_vGridData.push_back( new GridDataType2( SmpTyp, DtRep, stream ) );
        default:
            throw KException( __FUNCTION__, UNSUPPORTED_DATATYPE, "Unknown Grid Data Representation" );
        }
    }
}

//////////////////////////////////////////////////////////////////////////

KDataStream Gridded_Data_PDU::Encode() const
{
    KDataStream stream;

    Gridded_Data_PDU::Encode( stream );

    return stream;
}

//////////////////////////////////////////////////////////////////////////

void Gridded_Data_PDU::Encode( KDataStream & stream ) const
{
    Header::Encode( stream );

    stream << KDIS_STREAM m_EnvProcID
           << m_ui16FieldNum
           << m_ui16PDUNum
           << m_ui16PDUTotal
           << m_ui16CordSys
           << m_ui8NumAxis
           << m_ui8ConstGrid
           << KDIS_STREAM m_EnvType
           << KDIS_STREAM m_Ori
           << m_ui64SampleTime
           << m_ui32TotalValues
           << m_ui8VecDim
           << m_ui16Padding1
           << m_ui8Padding1;

    vector<GridAxisDescriptor>::const_iterator citrAxis = m_vpGridAxisDesc.begin();
    vector<GridAxisDescriptor>::const_iterator citrAxisEnd = m_vpGridAxisDesc.end();
    for( ; citrAxis != citrAxisEnd; ++citrAxis )
    {
        ( *citrAxis )->Encode( stream );
    }

    vector<GridDataPtr>::const_iterator citrData = m_vGridData.begin();
    vector<GridDataPtr>::const_iterator citrDataEnd = m_vGridData.end();
    for( ; citrData != citrDataEnd; ++citrData )
    {
        ( *citrData )->Encode( stream );
    }
}

//////////////////////////////////////////////////////////////////////////

KBOOL Gridded_Data_PDU::operator == ( const Gridded_Data_PDU & Value ) const
{
    if( Header::operator  != ( Value ) )               return false;
    if( m_EnvProcID       != Value.m_EnvProcID )       return false;
    if( m_ui16FieldNum    != Value.m_ui16FieldNum )    return false;
    if( m_ui16PDUNum      != Value.m_ui16PDUNum )      return false;
    if( m_ui16PDUTotal    != Value.m_ui16PDUTotal )    return false;
    if( m_ui16CordSys     != Value.m_ui16CordSys )     return false;
    if( m_ui8NumAxis      != Value.m_ui8NumAxis )      return false;
    if( m_ui8ConstGrid    != Value.m_ui8ConstGrid )    return false;
    if( m_EnvType         != Value.m_EnvType )         return false;
    if( m_Ori             != Value.m_Ori )             return false;
    if( m_ui64SampleTime  != Value.m_ui64SampleTime )  return false;
    if( m_ui32TotalValues != Value.m_ui32TotalValues ) return false;
    if( m_ui8VecDim       != Value.m_ui8VecDim )       return false;
    if( m_vpGridAxisDesc  != Value.m_vpGridAxisDesc )  return false;
    if( m_vGridData       != Value.m_vGridData )       return false;
    return true;
}

//////////////////////////////////////////////////////////////////////////

KBOOL Gridded_Data_PDU::operator != ( const Gridded_Data_PDU & Value ) const
{
    return !( *this == Value );
}

//////////////////////////////////////////////////////////////////////////


