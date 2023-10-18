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
    class:      Create_Entity_R_PDU
    DIS:        (5) 1278.1 - 1995
    created:    20:03:2009
    author:     Karl Jones

    purpose:    Create Entity PDU with reliability.
    size:       256 bits / 32 octets
*********************************************************************/

#pragma once

#include "KDIS/PDU/Simulation_Management/Create_Entity_PDU.hpp"
#include "KDIS/PDU/Simulation_Management_With_Reliability/Reliability_Header.hpp"

namespace KDIS {
namespace PDU {

class KDIS_EXPORT Create_Entity_R_PDU : public Create_Entity_PDU,
                                        public Reliability_Header {
 protected:
  Create_Entity_R_PDU* clone() const override;

 public:
  static const KUINT16 CREATE_ENTITY_R_PDU_SIZE = 32;

  Create_Entity_R_PDU();

  explicit Create_Entity_R_PDU(const Header& H);

  explicit Create_Entity_R_PDU(KDataStream& stream);

  Create_Entity_R_PDU(const Header& H, KDataStream& stream);

  Create_Entity_R_PDU(const KDIS::DATA_TYPE::EntityIdentifier& ReceivingEntity,
                      const KDIS::DATA_TYPE::EntityIdentifier& SupplyingEntity,
                      KUINT32 RequestID,
                      KDIS::DATA_TYPE::ENUMS::RequiredReliabilityService RRS);

  Create_Entity_R_PDU(const Simulation_Management_Header& SimMgrHeader,
                      KUINT32 RequestID,
                      KDIS::DATA_TYPE::ENUMS::RequiredReliabilityService RRS);

  virtual ~Create_Entity_R_PDU();

  //************************************
  // FullName:    KDIS::PDU::Create_Entity_R_PDU::GetString
  // Description: Returns a string representation of the PDU.
  //************************************
  virtual KString GetAsString() const;

  //************************************
  // FullName:    KDIS::PDU::Create_Entity_R_PDU::Decode
  // Description: Convert From Network Data.
  // Parameter:   KDataStream & stream
  // Parameter:   bool ignoreHeader = false - Decode the header from the stream?
  //************************************
  virtual void Decode(KDataStream& stream, bool ignoreHeader = false);

  //************************************
  // FullName:    KDIS::PDU::Create_Entity_R_PDU::Encode
  // Description: Convert To Network Data.
  // Parameter:   KDataStream & stream
  //************************************
  virtual KDataStream Encode() const;
  virtual void Encode(KDataStream& stream) const;

  KBOOL operator==(const Create_Entity_R_PDU& Value) const;
  KBOOL operator!=(const Create_Entity_R_PDU& Value) const;
};

}  // END namespace PDU
}  // END namespace KDIS
