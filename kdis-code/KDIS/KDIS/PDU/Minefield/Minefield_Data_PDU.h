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
    class:      Minefield_Data_PDU
    DIS:        (6) 1278.1a - 1998
    created:    25/05/2010
    author:     Karl Jones

    purpose:    Provides information on individual mines contained within a minefield.

                Note: This is a very complex PDU(The hardest one in the standard!), I do not have access to any software to test Minefield
                PDU's so it may contain traces of nuts(bugs). Please let me know if you have any problems. Karl.

    size:       352 bits / 44 octets  - Min size
*********************************************************************/

#pragma once

#include "./Minefield_Header.h"
#include "./../../DataTypes/MinefieldDataFilter.h"
#include "./../../DataTypes/EntityType.h"
#include "./../../DataTypes/Vector.h"
#include "./../../DataTypes/EulerAngles.h"
#include "./../../DataTypes/Mine.h"
#include <vector>

namespace KDIS {
namespace PDU {

using KDIS::DATA_TYPE::MinefieldDataFilter;
using KDIS::DATA_TYPE::EntityType;
using KDIS::DATA_TYPE::Vector;
using KDIS::DATA_TYPE::EulerAngles;
using KDIS::DATA_TYPE::Mine;
using KDIS::DATA_TYPE::EntityIdentifier;
using KDIS::DATA_TYPE::ENUMS::SensorType;
using std::vector;

class KDIS_EXPORT Minefield_Data_PDU : public Minefield_Header
{
protected:

    EntityIdentifier m_ReqID;

    union
    {
        struct
        {
            KUINT16 m_ui16Reserved : 1;
            KUINT16 m_ui16SeqNum15 : 15;
        };
        KUINT16 m_ui16SeqNum;
    } m_SeqNumUnion;

    KUINT8 m_ui8ReqID;

    KUINT8 m_ui8PduSeqNum;

    KUINT8 m_ui8NumPdus;

    KUINT8 m_ui8NumMines;

    KUINT8 m_ui8NumSensTyp;

    KUINT8 m_ui8Padding1;

    MinefieldDataFilter m_DataFilter;

    EntityType m_MineTyp;

    vector<KUINT16> m_vui16SensorTypes;

    vector<Mine> m_vMines;

    //************************************
    // FullName:    KDIS::PDU::Minefield_Data_PDU::calcPaddingPaintScheme
    // Description: Calculates the padding after the paint scheme.
    //              Padding � 8{[4 � N(2 F(8) + M F(9) + F(10) + 2)]    mod4} bits unused
    //              PDU lies on a 32 bit boundary.
    //************************************
    KUINT8 calcPaddingPaintScheme() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_Data_PDU::calcPaddingPaintScheme
    // Description: Calculates the padding after the Number of Vertices's field.
    //************************************
    KUINT8 calcPaddingVertices() const;

public:

    static const KUINT16 MINEFIELD_DATA_PDU_SIZE = 44; // Min size

    Minefield_Data_PDU( void );

    Minefield_Data_PDU( const EntityIdentifier & MinefieldID, const EntityIdentifier & RequestingSimulationID,
                        KUINT16 SeqNum, KUINT8 RequestID, KUINT8 PduSeqNum, KUINT8 NumPdus,
                        const MinefieldDataFilter & DF, const EntityType & MineType );

    Minefield_Data_PDU( KDataStream & stream ) throw( KException );

    virtual ~Minefield_Data_PDU( void );

    //************************************
    // FullName:    KDIS::PDU::Minefield_Data_PDU::SetRequestingSimulationID
    //              KDIS::PDU::Minefield_Data_PDU::GetRequestingSimulationID
    // Description: The simulation that is requesting the information.
    // Parameter:   const EntityIdentifier & ID
    //************************************
    void SetRequestingSimulationID( const EntityIdentifier & ID );
    const EntityIdentifier & GetRequestingSimulationID() const;
    EntityIdentifier & GetRequestingSimulationID();

    //************************************
    // FullName:    KDIS::PDU::Minefield_Data_PDU::SetSequenceNumber
    //              KDIS::PDU::Minefield_Data_PDU::GetSequenceNumber
    // Description: Identifies the matching minefield sequence number
    //              from the associated Minefield State PDU.
    // Parameter:   KUINT16 S
    //************************************
    void SetSequenceNumber( KUINT16 S );
    KUINT16 GetSequenceNumber() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_Data_PDU::SetRequestID
    //              KDIS::PDU::Minefield_Data_PDU::GetRequestID
    // Description: The matching response to a request for mine information from the
    //              minefield simulation made by means of a Minefield Query PDU
    //              in QRP mode. In heartbeat mode, this field shall contain the value zero.
    // Parameter:   KUINT8 ID
    //************************************
    void SetRequestID( KUINT8 ID );
    KUINT8 GetRequestID() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_Data_PDU::SetPDUSequenceNumber
    //              KDIS::PDU::Minefield_Data_PDU::GetPDUSequenceNumber
    // Description: Specifies the number of the current Minefield Data PDU in a
    //              sequence of Minefield Data PDUs sent in response to a Minefield
    //              Query PDU when operating in QRP mode.
    //              When operating in heartbeat mode, this field is unused and shall contain the value zero.
    // Parameter:   KUINT8 SN
    //************************************
    void SetPDUSequenceNumber( KUINT8 SN );
    KUINT8 GetPDUSequenceNumber() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_Data_PDU::GetNumberOfPDUs
    //              KDIS::PDU::Minefield_Data_PDU::SetNumberOfPDUs
    // Description: The total number of Minefield Data PDUs being sent in
    //              response to a Minefield Query PDU when operating in QRP mode.
    //              When operating in heartbeat mode, this field is unused and shall contain the value zero.
    // Parameter:   KUINT8 N
    //************************************
    void SetNumberOfPDUs( KUINT8 N );
    KUINT8 GetNumberOfPDUs() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_Data_PDU::GetNumberOfMines
    // Description: The number of mines of the same type contained in this PDU.
    //************************************
    KUINT8 GetNumberOfMines() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_Data_PDU::GetNumberOfSensorsTypes
    // Description: In QRP mode, this field shall specify the number of sensor types employed
    //              by the requesting simulation as specified in the Minefield Query PDU.
    //              In heartbeat mode, this field shall specify the number of sensor types
    //              employed in the exercise.
    //************************************
    KUINT8 GetNumberOfSensorsTypes() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_Data_PDU::SetDataFilter
    //              KDIS::PDU::Minefield_Data_PDU::GetDataFilter
    // Description: Identifies which of the optional data fields are set in
    //              the mines contained in this Minefield Data PDU.
    // Parameter:   const MinefieldDataFilter & DF
    //************************************
    void SetDataFilter( const MinefieldDataFilter & DF );
    const MinefieldDataFilter & GetDataFilter() const;
    MinefieldDataFilter & GetDataFilter();

    //************************************
    // FullName:    KDIS::PDU::Minefield_Data_PDU::SetMineType
    //              KDIS::PDU::Minefield_Data_PDU::GetMineType
    // Description: The type of mine contained in this PDU.
    // Parameter:   const MinefieldDataFilter & DF
    //************************************
    void SetMineType( const EntityType & MT );
    const EntityType & GetMineType() const;
    EntityType & GetMineType();

    //************************************
    // FullName:    KDIS::PDU::Minefield_Data_PDU::AddSensorType
    //              KDIS::PDU::Minefield_Data_PDU::SetSensorTypes
    //              KDIS::PDU::Minefield_Data_PDU::GetSensorTypes
    // Description: In QRP mode, this field shall specify the requesting sensor types
    //              which were specified in the Minefield Query PDU. In heartbeat mode,
    //              this field shall specify the sensor types that are being served by the minefield
    //              The sensor type is represented as a 16 bit enumeration where bits 0-3
    //              identify the category of the sensor type and bits 4-15 identify the
    //              subcategory within the specified category.
    //              The enum SensorType(EnumMinefield.h) provides all sensor types from SISO-REF-10-2006 which have all the bits set
    //              correctly for each sensor type.
    // Parameter:   SensorType ST, vector<KUINT16> & ST, void
    //************************************
    void AddSensorType( SensorType ST );
    void SetSensorTypes( const vector<KUINT16> & ST );
    const vector<KUINT16> & GetSensorTypes() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_Data_PDU::AddMine
    //              KDIS::PDU::Minefield_Data_PDU::SetMines
    //              KDIS::PDU::Minefield_Data_PDU::GetMines
    // Description: The Mine class encapsulates the common attributes for a mine.
    //              Note: All the mines must have the same optional values set as stated by the
    //              MinefieldDataFilter, if they are not then an INVALID_OPERATION exception is thrown.
    // Parameter:   const Mine & M, const vector<Mine> & M
    //************************************
    void AddMine( const Mine & M ) throw( KException );
    void SetMines( const vector<Mine> & M ) throw( KException );
    const vector<Mine> & GetMines() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_Data_PDU::GetAsString
    // Description: Returns a string representation of the PDU.
    //************************************
    virtual KString GetAsString() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_Data_PDU::Decode
    // Description: Convert From Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual void Decode( KDataStream & stream ) throw( KException );

    //************************************
    // FullName:    KDIS::PDU::Minefield_Data_PDU::Encode
    // Description: Convert To Network Data. Exception is thrown if each mine does not
    //              have a ScalarDetectionCoefficient value for each sensor type.
    // Parameter:   KDataStream & stream
    //************************************
    virtual KDataStream Encode() const throw( KException );
    virtual void Encode( KDataStream & stream ) const throw( KException );

    KBOOL operator == ( const Minefield_Data_PDU & Value ) const;
    KBOOL operator != ( const Minefield_Data_PDU & Value ) const;
};

}; // END namespace PDU
}; // END namespace KDIS