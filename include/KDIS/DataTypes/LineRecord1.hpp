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
    class:      LineRecord1
    created:    17/08/2009
    author:     Karl Jones

    purpose:    A geometry record representing a line.
    size:       448 bits / 56 octets
*********************************************************************/

#pragma once

#include "KDIS/DataTypes/EnvironmentRecord.hpp"
#include "KDIS/DataTypes/WorldCoordinates.hpp"

namespace KDIS {
namespace DATA_TYPE {

class KDIS_EXPORT LineRecord1 : public EnvironmentRecord {
 protected:
  WorldCoordinates m_StartLocation;

  WorldCoordinates m_EndLocation;

 public:
  static const KUINT16 LINE_RECORD_1_SIZE = 56;

  LineRecord1();

  LineRecord1(KDataStream& stream);

  LineRecord1(KUINT8 Index, const WorldCoordinates& Start,
              const WorldCoordinates& End);

  virtual ~LineRecord1();

  //************************************
  // FullName:    KDIS::DATA_TYPE::LineRecord1::SetLocation
  // Description: Specifies the start and end location of the line.
  // Parameter:   const WorldCoordinates & Start
  // Parameter:   const WorldCoordinates & End
  //************************************
  void SetLocation(const WorldCoordinates& Start, const WorldCoordinates& End);

  //************************************
  // FullName:    KDIS::DATA_TYPE::LineRecord1::SetStartLocation
  //              KDIS::DATA_TYPE::LineRecord1::GetStartLocation
  // Description: Specifies the start location of the line.
  // Parameter:   const WorldCoordinates & L, void
  //************************************
  void SetStartLocation(const WorldCoordinates& L);
  const WorldCoordinates& GetStartLocation() const;
  WorldCoordinates& GetStartLocation();

  //************************************
  // FullName:    KDIS::DATA_TYPE::LineRecord1::SetEndLocation
  //              KDIS::DATA_TYPE::LineRecord1::GetEndLocation
  // Description: Specifies the end location of the line.
  // Parameter:   const WorldCoordinates & L, void
  //************************************
  void SetEndLocation(const WorldCoordinates& L);
  const WorldCoordinates& GetEndLocation() const;
  WorldCoordinates& GetEndLocation();

  //************************************
  // FullName:    KDIS::DATA_TYPE::LineRecord1::GetAsString
  // Description: Returns a string representation
  //************************************
  KString GetAsString() const override;

  //************************************
  // FullName:    KDIS::DATA_TYPE::LineRecord1::Decode
  // Description: Convert From Network Data.
  // Parameter:   KDataStream & stream
  //************************************
  void Decode(KDataStream& stream) override;

  //************************************
  // FullName:    KDIS::DATA_TYPE::LineRecord1::Encode
  // Description: Convert To Network Data.
  // Parameter:   KDataStream & stream
  //************************************
  KDataStream Encode() const override;
  void Encode(KDataStream& stream) const override;

  KBOOL operator==(const LineRecord1& Value) const;
  KBOOL operator!=(const LineRecord1& Value) const;
};

}  // namespace DATA_TYPE
}  // END namespace KDIS
