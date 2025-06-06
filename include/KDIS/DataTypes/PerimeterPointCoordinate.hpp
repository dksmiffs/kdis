/*********************************************************************
Copyright 2013 Karl Jones
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

For Further Information Please Contact me at
Karljj1@yahoo.com
http://p.sf.net/kdis/UserGuide
*********************************************************************/

/********************************************************************
    class:      PerimeterPointCoordinate
    created:    09/05/2010
    author:     Karl Jones

    purpose:    The location of each perimeter point, relative to the Minefield
Location field. size:       64 bits / 8 octets
*********************************************************************/

#pragma once

#include "KDIS/DataTypes/DataTypeBase.hpp"

namespace KDIS {
namespace DATA_TYPE {

class KDIS_EXPORT PerimeterPointCoordinate : public DataTypeBase {
 protected:
  KFLOAT32 m_f32X;

  KFLOAT32 m_f32Y;

 public:
  static const KUINT16 PERIMETER_POINT_COORDINATE_SIZE = 8;

  PerimeterPointCoordinate();

  PerimeterPointCoordinate(KFLOAT32 X, KFLOAT32 Y);

  PerimeterPointCoordinate(KDataStream& stream);

  virtual ~PerimeterPointCoordinate();

  //************************************
  // FullName:    KDIS::DATA_TYPE::PerimeterPointCoordinate::SetX
  //              KDIS::DATA_TYPE::PerimeterPointCoordinate::GetX
  // Description: First Value / X
  // Parameter:   KFLOAT32  X, void
  //************************************
  void SetX(KFLOAT32 X);
  KFLOAT32 GetX() const;

  //************************************
  // FullName:    KDIS::DATA_TYPE::PerimeterPointCoordinate::SetY
  //              KDIS::DATA_TYPE::PerimeterPointCoordinate::GetY
  // Description: Second Value / Y
  // Parameter:   KFLOAT32 Y, void
  //************************************
  void SetY(KFLOAT32 Y);
  KFLOAT32 GetY() const;

  //************************************
  // FullName:    KDIS::DATA_TYPE::PerimeterPointCoordinate::GetAsString
  // Description: Returns a string representation
  //************************************
  KString GetAsString() const override;

  //************************************
  // FullName:    KDIS::DATA_TYPE::PerimeterPointCoordinate::Decode
  // Description: Convert From Network Data.
  // Parameter:   KDataStream & stream
  //************************************
  void Decode(KDataStream& stream) override;

  //************************************
  // FullName:    KDIS::DATA_TYPE::PerimeterPointCoordinate::Encode
  // Description: Convert To Network Data.
  // Parameter:   KDataStream & stream
  //************************************
  KDataStream Encode() const override;
  void Encode(KDataStream& stream) const override;

  KBOOL operator==(const PerimeterPointCoordinate& Value) const;
  KBOOL operator!=(const PerimeterPointCoordinate& Value) const;

  // Valid values 0 - X, 1 - Y. throws OUT_OF_BOUNDS exception for any other
  // value.
  KFLOAT32& operator[](KUINT16 i);
  const KFLOAT32& operator[](KUINT16 i) const;
};

}  // namespace DATA_TYPE
}  // END namespace KDIS
