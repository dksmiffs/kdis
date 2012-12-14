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

#include "./RectangularVolumeRecord2.h"

using namespace KDIS;
using namespace DATA_TYPE;
using namespace ENUMS;

//////////////////////////////////////////////////////////////////////////
// public:
//////////////////////////////////////////////////////////////////////////

RectangularVolumeRecord2::RectangularVolumeRecord2( void ) :
    m_f32Padding( 0 )
{
    m_ui32EnvRecTyp = RectangularVolumeRecord2Type;
    m_ui16Length = ( RECTANGLE_VOLUME_RECORD_2_SIZE - ENVIRONMENT_RECORD_SIZE ) * 8;
}

//////////////////////////////////////////////////////////////////////////

RectangularVolumeRecord2::RectangularVolumeRecord2( KDataStream & stream )throw( KException )
{
    Decode( stream );
}

//////////////////////////////////////////////////////////////////////////

RectangularVolumeRecord2::RectangularVolumeRecord2( KUINT8 Index, const WorldCoordinates & CornerLocation, const Vector & RectangleLength,
        const Vector & DDT, const EulerAngles & Orientation, const Vector & Velocity,
        const Vector & AngularVelocity ) :
    RectangularVolumeRecord1( Index, CornerLocation, RectangleLength, Orientation ),
    m_DDT( DDT ),
    m_Velocity( Velocity ),
    m_AngularVelocity( AngularVelocity ),
    m_f32Padding( 0 )
{
    m_ui32EnvRecTyp = RectangularVolumeRecord2Type;
    m_ui16Length = ( RECTANGLE_VOLUME_RECORD_2_SIZE - ENVIRONMENT_RECORD_SIZE ) * 8;
}

//////////////////////////////////////////////////////////////////////////

RectangularVolumeRecord2::~RectangularVolumeRecord2( void )
{
}

//////////////////////////////////////////////////////////////////////////

void RectangularVolumeRecord2::SetDOverDt( const Vector & DDT )
{
    m_DDT = DDT;
}

//////////////////////////////////////////////////////////////////////////

const Vector & RectangularVolumeRecord2::GetDOverDt() const
{
    return m_DDT;
}

//////////////////////////////////////////////////////////////////////////

Vector & RectangularVolumeRecord2::GetDOverDt()
{
    return m_DDT;
}

//////////////////////////////////////////////////////////////////////////

void RectangularVolumeRecord2::SetVelocity( const Vector & V )
{
    m_Velocity = V;
}

//////////////////////////////////////////////////////////////////////////

const Vector & RectangularVolumeRecord2::GetVelocity() const
{
    return m_Velocity;
}

//////////////////////////////////////////////////////////////////////////

Vector & RectangularVolumeRecord2::GetVelocity()
{
    return m_Velocity;
}

//////////////////////////////////////////////////////////////////////////

void RectangularVolumeRecord2::SetAngularVelocity( const Vector & V )
{
    m_AngularVelocity = V;
}

//////////////////////////////////////////////////////////////////////////

const Vector & RectangularVolumeRecord2::GetAngularVelocity() const
{
    return m_AngularVelocity;
}

//////////////////////////////////////////////////////////////////////////

Vector & RectangularVolumeRecord2::GetAngularVelocity()
{
    return m_AngularVelocity;
}

//////////////////////////////////////////////////////////////////////////

KString RectangularVolumeRecord2::GetAsString() const
{
    KStringStream ss;

    ss << RectangularVolumeRecord1::GetAsString()
       << "\td(Length)/dt: "      << m_DDT.GetAsString()
       << "\tVelocity: "          << m_Velocity.GetAsString()
       << "\tAngular Velocity: "  << m_AngularVelocity.GetAsString();

    return ss.str();
}

//////////////////////////////////////////////////////////////////////////

void RectangularVolumeRecord2::Decode( KDataStream & stream ) throw( KException )
{
    if( stream.GetBufferSize() < RECTANGLE_VOLUME_RECORD_2_SIZE )throw KException( __FUNCTION__, NOT_ENOUGH_DATA_IN_BUFFER );

    stream >> m_ui32EnvRecTyp
           >> m_ui16Length
           >> m_ui8Index
           >> m_ui8Padding
           >> KDIS_STREAM m_CornerLocation
           >> KDIS_STREAM m_RecLength
           >> KDIS_STREAM m_DDT
           >> KDIS_STREAM m_Ori
           >> KDIS_STREAM m_Velocity
           >> KDIS_STREAM m_AngularVelocity
           >> m_f32Padding;
}

//////////////////////////////////////////////////////////////////////////

KDataStream RectangularVolumeRecord2::Encode() const
{
    KDataStream stream;

    RectangularVolumeRecord2::Encode( stream );

    return stream;
}

//////////////////////////////////////////////////////////////////////////

void RectangularVolumeRecord2::Encode( KDataStream & stream ) const
{
    stream << m_ui32EnvRecTyp
           << m_ui16Length
           << m_ui8Index
           << m_ui8Padding
           << KDIS_STREAM m_CornerLocation
           << KDIS_STREAM m_RecLength
           << KDIS_STREAM m_DDT
           << KDIS_STREAM m_Ori
           << KDIS_STREAM m_Velocity
           << KDIS_STREAM m_AngularVelocity
           << m_f32Padding;
}

//////////////////////////////////////////////////////////////////////////

KBOOL RectangularVolumeRecord2::operator == ( const RectangularVolumeRecord2 & Value )const
{
    if( RectangularVolumeRecord1::operator !=( Value ) )  return false;
    if( m_DDT               != Value.m_DDT )              return false;
    if( m_Velocity          != Value.m_Velocity )         return false;
    if( m_AngularVelocity   != Value.m_AngularVelocity )  return false;
    return true;
}

//////////////////////////////////////////////////////////////////////////

KBOOL RectangularVolumeRecord2::operator != ( const RectangularVolumeRecord2 & Value )const
{
    return !( *this == Value );
}

//////////////////////////////////////////////////////////////////////////
