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
    class:      Gridded_Data_PDU
    DIS:        (6) 1278.1a - 1998
    created:    06/10/2009
    author:     Karl Jones

    purpose:    Information about global, spatially varying environmental effects
                shall be communicated using one or more Gridded Data PDUs.

    size:       512 bits / 64 octets - Min size
*********************************************************************/

#pragma once

#include "./../Header.h"
#include "./../../DataTypes/EntityIdentifier.h"
#include "./../../DataTypes/EnvironmentType.h"
#include "./../../DataTypes/EulerAngles.h"
#include "./../../DataTypes/GridAxisIrregular.h"
#include "./../../DataTypes/GridDataType0.h"
#include "./../../DataTypes/GridDataType1.h"
#include "./../../DataTypes/GridDataType2.h"
#include "./../../Extras/KRef_Ptr.h"
#include <vector>

namespace KDIS {

namespace DATA_TYPE {

// Some PDU specific data types.
typedef KDIS::UTILS::KRef_Ptr<GridAxisRegular> GridAxisDescriptor;
typedef KDIS::UTILS::KRef_Ptr<GridData> GridDataPtr;

}; // End namespace DATA_TYPE

namespace PDU {

using KDIS::DATA_TYPE::EntityIdentifier;
using KDIS::DATA_TYPE::EnvironmentType;
using KDIS::DATA_TYPE::EulerAngles;
using KDIS::DATA_TYPE::GridAxisIrregular;
using KDIS::DATA_TYPE::GridAxisRegular;
using KDIS::DATA_TYPE::GridData;
using KDIS::DATA_TYPE::GridAxisDescriptor;
using KDIS::DATA_TYPE::GridDataPtr;
using KDIS::DATA_TYPE::ENUMS::CoordinateSystem;
using KDIS::DATA_TYPE::ENUMS::ConstantGrid;
using std::vector;

class KDIS_EXPORT Gridded_Data_PDU : public Header
{
protected:

    EntityIdentifier m_EnvProcID;

    KUINT16 m_ui16FieldNum;

    KUINT16 m_ui16PDUNum;

    KUINT16 m_ui16PDUTotal;

    KUINT16 m_ui16CordSys;

    KUINT8 m_ui8NumAxis;

    KUINT8 m_ui8ConstGrid;

    EnvironmentType m_EnvType;

    EulerAngles m_Ori;

    KUINT64 m_ui64SampleTime;

    KUINT32 m_ui32TotalValues;

    KUINT8 m_ui8VecDim;

    KUINT16 m_ui16Padding1; // 24 bits unused for alignment of Grid Axis Descriptor
    KUINT8 m_ui8Padding1;

    vector<GridAxisDescriptor> m_vpGridAxisDesc;

    vector<GridDataPtr> m_vGridData;

public:

    static const KUINT16 GRIDDED_DATA_PDU_SIZE = 64; // Min size

    Gridded_Data_PDU( void );

    Gridded_Data_PDU( KDataStream & stream ) throw( KException );

    Gridded_Data_PDU( const EntityIdentifier & EnvironmentalProcessID, KUINT16 FieldNumber, KUINT16 PduNum,
                      KUINT16 PduTotal, CoordinateSystem CS, ConstantGrid CG, const EnvironmentType & ET,
                      const EulerAngles & Ori, KUINT64 SampleTime );

    virtual ~Gridded_Data_PDU( void );

    //************************************
    // FullName:    KDIS::PDU::Gridded_Data_PDU::SetEnvironmentalProcessID
    //              KDIS::PDU::Gridded_Data_PDU::GetEnvironmentalProcessID
    // Description: Identifies the environmental simulation application issuing the PDU.
    //              This field is also known as "Environmental Simulation ID" in DIS version 7.
    // Parameter:   const EntityIdentifier & ID, void
    //************************************
    void SetEnvironmentalProcessID( const EntityIdentifier & ID );
    const EntityIdentifier & GetEnvironmentalProcessID() const;
    EntityIdentifier & GetEnvironmentalProcessID();

    //************************************
    // FullName:    KDIS::PDU::Gridded_Data_PDU::SetFieldNumber
    //              KDIS::PDU::Gridded_Data_PDU::GetFieldNumber
    // Description: Specifies a unique identifier for each environmental variable transmitted
    //              during an exercise.
    // Parameter:   KUINT16 FN, void
    //************************************
    void SetFieldNumber( KUINT16 FN );
    KUINT16 GetFieldNumber() const;

    //************************************
    // FullName:    KDIS::PDU::Gridded_Data_PDU::SetPDUNumber
    //              KDIS::PDU::Gridded_Data_PDU::GetPDUNumber
    // Description: Specifies an index number of the current PDU within the total number
    //              of PDUs used to transmit the environmental data.
    //              SetPDUNumberAndTotal will throw an exception if Num is greater than Total.
    //              No error checking is done if you use the 2 separate accessors SetPDUNumber
    //              and SetPDUTotal so be careful not to make the PDU number greater than the total.
    // Parameter:   KUINT16 PN, void
    //************************************
    void SetPDUNumber( KUINT16 PN );
    KUINT16 GetPDUNumber() const;
    void SetPDUNumberAndTotal( KUINT16 Num, KUINT16 Total ) throw( KException );

    //************************************
    // FullName:    KDIS::PDU::Gridded_Data_PDU::SetPDUTotal
    //              KDIS::PDU::Gridded_Data_PDU::GetPDUTotal
    // Description: Specifies the total number of PDUs used to transmit this environmental data.
    //              This value should not be less than PDU number.
    // Parameter:   KUINT16 PT, void
    //************************************
    void SetPDUTotal( KUINT16 PT );
    KUINT16 GetPDUTotal() const;

    //************************************
    // FullName:    KDIS::PDU::Gridded_Data_PDU::SetCoordinateSystem
    //              KDIS::PDU::Gridded_Data_PDU::GetCoordinateSystem
    // Description: Specifies the coordinate system of the grid for the environmental
    //              data contained in the Gridded Data PDU.
    // Parameter:   CoordinateSystem CS, void
    //************************************
    void SetCoordinateSystem( CoordinateSystem CS );
    CoordinateSystem GetCoordinateSystem() const;

    //************************************
    // FullName:    KDIS::PDU::Gridded_Data_PDU::Decode
    // Description: Number of grid axis in the PDU.
    //              e.g. three grid axes for an x, y, z coordinate system.
    //************************************
    KUINT8 GetNumberAxis() const;

    //************************************
    // FullName:    KDIS::PDU::Gridded_Data_PDU::SetConstantGrid
    //              KDIS::PDU::Gridded_Data_PDU::GetConstantGrid
    // Description: Specifies whether the domain grid axes are identical to those of the previous
    //              domain update grid for the environmental data sample contained in the PDU
    // Parameter:   ConstantGrid CG, void
    //************************************
    void SetConstantGrid( ConstantGrid CG );
    ConstantGrid GetConstantGrid() const;

    //************************************
    // FullName:    KDIS::PDU::Gridded_Data_PDU::SetEnvironmentType
    //              KDIS::PDU::Gridded_Data_PDU::GetEnvironmentType
    // Description: DIS enumeration identifying the type of environmental effect being described.
    // Parameter:   const EnvironmentType & ET, void
    //************************************
    void SetEnvironmentType( const EnvironmentType & ET );
    const EnvironmentType & GetEnvironmentType() const;
    EnvironmentType & GetEnvironmentType();

    //************************************
    // FullName:    KDIS::PDU::Gridded_Data_PDU::SetOrientation
    //              KDIS::PDU::Gridded_Data_PDU::GetOrientation
    // Description: Specifies the orientation of the data grid.
    // Parameter:   const EulerAngles & O, void
    //************************************
    void SetOrientation( const EulerAngles & O );
    const EulerAngles & GetOrientation() const;
    EulerAngles & GetOrientation();

    //************************************
    // FullName:    KDIS::PDU::Gridded_Data_PDU::SetSampleTime
    //              KDIS::PDU::Gridded_Data_PDU::GetSampleTime
    // Description: Specifies the valid time of the environmental data sample contained in the PDU.
    // Parameter:   KUINT64 ST, void
    //************************************
    void SetSampleTime( KUINT64 ST );
    KUINT64 GetSampleTime() const;

    //************************************
    // FullName:    KDIS::PDU::Gridded_Data_PDU::SetTotalValues
    //              KDIS::PDU::Gridded_Data_PDU::GetTotalValues
    // Description: Specifies the total number of data values for all PDUs for an environmental
    //              sample. This total includes vector-valued environmental data and equals the
    //              product of the vector dimension and the total number of grid points.
    // Parameter:   KUINT32 TV, void
    //************************************
    void SetTotalValues( KUINT32 TV );
    KUINT32 GetTotalValues() const;

    //************************************
    // FullName:    KDIS::PDU::Gridded_Data_PDU::SetVectorDimension
    //              KDIS::PDU::Gridded_Data_PDU::GetVectorDimension
    // Description: This field shall specify the total number of data values at each grid point and
    //              accommodates scalar or vector-valued environmental data.
    //              Vector Dimension shall be one for scalar data, and shall be greater than one when
    //              multiple enumerated environmental data values are sent for each grid location
    //              (e.g., u, v, w wind components have V = 3). (I.E Number of GridData values).
    // Parameter:   KUINT8 VD, void
    //************************************
    void SetVectorDimension( KUINT8 VD );
    KUINT8 GetVectorDimension() const;

    //************************************
    // FullName:    KDIS::PDU::Gridded_Data_PDU::AddGridAxisDescriptor
    //              KDIS::PDU::Gridded_Data_PDU::SetGridAxisDescriptors
    //              KDIS::PDU::Gridded_Data_PDU::GetSetGridAxisDescriptors
    // Description: Specifies the detailed information about the grid dimensions (axes)
    //              and coordinates for environmental state variables.
    //              More than one Grid Data record is allowed in a single Gridded Data PDU
    //              corresponding to each enumerated sample type.
    // Parameter:   const GridAxisDescriptor & GAD, const vector<GridAxisDescriptor> & GADS, void
    //************************************
    void AddGridAxisDescriptor( const GridAxisDescriptor & GAD );
    void SetGridAxisDescriptors( const vector<GridAxisDescriptor> & GADS );
    const vector<GridAxisDescriptor> & GetSetGridAxisDescriptors() const;

    //************************************
    // FullName:    KDIS::PDU::Gridded_Data_PDU::AddGridData
    //              KDIS::PDU::Gridded_Data_PDU::SetGridData
    //              KDIS::PDU::Gridded_Data_PDU::GetGridData
    // Description: Specifies the environmental state data at the grid locations specified by
    //              parameters in the Grid Axis Descriptor record.
    // Parameter:   const GridDataPtr & GD, const vector<GridDataPtr> & GD, void
    //************************************
    void AddGridData( const GridDataPtr & GD );
    void SetGridData( const vector<GridDataPtr> & GD );
    const vector<GridDataPtr> & GetGridData() const;

    //************************************
    // FullName:    KDIS::PDU::Gridded_Data_PDU::GetAsString
    // Description: Returns a string representation of the PDU.
    //************************************
    virtual KString GetAsString() const;

    //************************************
    // FullName:    KDIS::PDU::Gridded_Data_PDU::Decode
    // Description: Convert From Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual void Decode( KDataStream & stream ) throw( KException );

    //************************************
    // FullName:    KDIS::PDU::Gridded_Data_PDU::Encode
    // Description: Convert To Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual KDataStream Encode() const;
    virtual void Encode( KDataStream & stream ) const;

    KBOOL operator == ( const Gridded_Data_PDU & Value ) const;
    KBOOL operator != ( const Gridded_Data_PDU & Value ) const;
};

}; // END namespace PDU
}; // END namespace KDIS