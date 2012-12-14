/*********************************************************************
For Further Information on KDIS:
http://p.sf.net/kdis/UserGuide

This example shows how to correctly use the Environmental_Process_PDU to create a point feature
in our simulation which will represent a cloud.
*********************************************************************/

#include <iostream>
#include "KDIS/PDU/Synthetic_Enviroment/Environmental_Process_PDU.h"
#include "KDIS/Network/Connection.h" // A cross platform connection class.

using namespace std;
using namespace KDIS;
using namespace DATA_TYPE;
using namespace PDU;
using namespace ENUMS;
using namespace UTILS;
using namespace NETWORK;

int main()
{
    // First lets create the PDU object.
    Environmental_Process_PDU ourEnvProcPDU;

    ourEnvProcPDU.SetEnvironmentalProcessID( EntityIdentifier( 1, 123, 1 ) ); // The ID of our application (SiteID, AppID, ObjectID)
    ourEnvProcPDU.SetEnvironmentType( EnvironmentType( Air, 0, 3, SmallSize, 0, 0 ) ); // This value is taken from section 4 of the SISO-REF-010-2006. It represents a small cloud.

    // Convert local coordinate systems to DIS
    // 51.5� N 3.2� W. Cardiff, Wales.
    // A cloud over Wales, what a surprise!
    // Convert Degrees, Minutes, Seconds to decimal and then convert to geocentric.
    KFLOAT64 Lat = KDIS::UTILS::DMSToDecimal( 51.0, 5.0, 0.0 );
    KFLOAT64 Lon = KDIS::UTILS::DMSToDecimal( 3.0, 2.0, 0.0 );
    KFLOAT64 Alt = KDIS::UTILS::FeetToMeters( 3000.0 );
    KFLOAT64 GeoX = 0.0, GeoY = 0.0, GeoZ = 0.0;
    KDIS::UTILS::GeodeticToGeocentric( Lat, Lon, Alt, GeoX, GeoY, GeoZ, WGS_1984 );
    WorldCoordinates loc( GeoX, GeoY, GeoZ );
    ourEnvProcPDU.SetEnvironmentStatusOn( true );
    ourEnvProcPDU.SetSequenceNumber( EP_NO_SEQUENCE );
    ourEnvProcPDU.AddEnviromentRecord( EnviromentRecordPtr( new PointRecord1( 0, loc ) ) );

    // Set the PDU Header values
    ourEnvProcPDU.SetExerciseID( 1 );

    // Set the time stamp to automatically calculate.
    ourEnvProcPDU.SetTimeStamp( TimeStamp( RelativeTime, 0, true ) );

    // Note this multi cast address will probably be different for your network.
    Connection conn( "192.168.3.255" );

    KOCTET cBuffer[MAX_PDU_SIZE]; // Somewhere to store the data we send.

    try
    {
        while( true )
        {
            // Keep sending the pdu.
            conn.SendPDU( ( Header * )&ourEnvProcPDU );
        }
    }
    catch( exception & e )
    {
        cout << e.what() << endl;
    }

    return 0;
}

