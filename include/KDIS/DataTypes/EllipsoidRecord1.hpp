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
    class:      EllipsoidRecord1
    created:    18/08/2009
    author:     Karl Jones

    purpose:    A geometry record representing an elipsoid.
    size:       448 bits / 56 octets
*********************************************************************/

#pragma once

#include "KDIS/DataTypes/EnvironmentRecord.hpp"
#include "KDIS/DataTypes/EulerAngles.hpp"
#include "KDIS/DataTypes/WorldCoordinates.hpp"

namespace KDIS {
namespace DATA_TYPE {

class KDIS_EXPORT EllipsoidRecord1 : public EnvironmentRecord {
 protected:
  WorldCoordinates m_CentLocation;

  Vector m_Sigma;

  EulerAngles m_Ori;

 public:
  static const KUINT16 ELIPSOID_RECORD_1_SIZE = 56;

  EllipsoidRecord1();

  EllipsoidRecord1(KDataStream& stream);

  EllipsoidRecord1(KUINT8 Index, const WorldCoordinates& CentroidLocation,
                   const Vector& Sigma, const EulerAngles& Orientation);

  virtual ~EllipsoidRecord1();

  //************************************
  // FullName:    KDIS::DATA_TYPE::EllipsoidRecord1::SetCentroidLocation
  //              KDIS::DATA_TYPE::EllipsoidRecord1::GetCentroidLocation
  // Description: Specifies the location of the center of the sphere.
  // Parameter:   const WorldCoordinates & CL
  //************************************
  void SetCentroidLocation(const WorldCoordinates& CL);
  const WorldCoordinates& GetCentroidLocation() const;
  WorldCoordinates& GetCentroidLocation();

  //************************************
  // FullName:    KDIS::DATA_TYPE::EllipsoidRecord1::SetSigma
  //              KDIS::DATA_TYPE::EllipsoidRecord1::GetSigma
  // Description: Sigma (X, Y, Z) for the ellipsoid.
  // Parameter:   const Vector & S
  //************************************
  void SetSigma(const Vector& S);
  const Vector& GetSigma() const;
  Vector& GetSigma();

  //************************************
  // FullName:    KDIS::DATA_TYPE::EllipsoidRecord1::SetOrientation
  //              KDIS::DATA_TYPE::EllipsoidRecord1::GetOrientation
  // Description: Orientation for the ellipsoid.
  // Parameter:   const EulerAngles & O
  //************************************
  void SetOrientation(const EulerAngles& O);
  const EulerAngles& GetOrientation() const;
  EulerAngles& GetOrientation();

  //************************************
  // FullName:    KDIS::DATA_TYPE::EllipsoidRecord1::GetAsString
  // Description: Returns a string representation
  //************************************
  KString GetAsString() const override;

  //************************************
  // FullName:    KDIS::DATA_TYPE::EllipsoidRecord1::Decode
  // Description: Convert From Network Data.
  // Parameter:   KDataStream & stream
  //************************************
  void Decode(KDataStream& stream) override;

  //************************************
  // FullName:    KDIS::DATA_TYPE::EllipsoidRecord1::Encode
  // Description: Convert To Network Data.
  // Parameter:   KDataStream & stream
  //************************************
  KDataStream Encode() const override;
  void Encode(KDataStream& stream) const override;

  KBOOL operator==(const EllipsoidRecord1& Value) const;
  KBOOL operator!=(const EllipsoidRecord1& Value) const;
};

}  // namespace DATA_TYPE
}  // END namespace KDIS
