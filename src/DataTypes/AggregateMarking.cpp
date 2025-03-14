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

#include "KDIS/DataTypes/AggregateMarking.hpp"

using namespace KDIS;
using namespace DATA_TYPE;
using namespace ENUMS;

//////////////////////////////////////////////////////////////////////////
// Public:
//////////////////////////////////////////////////////////////////////////

AggregateMarking::AggregateMarking(KDataStream& stream) { Decode(stream); }

//////////////////////////////////////////////////////////////////////////

AggregateMarking::AggregateMarking(EntityMarkingCharacterSet MarkingCharSet,
                                   const KString& MarkingText) {
  SetAggregateMarkingCharacterSet(MarkingCharSet);
  SetAggregateMarkingString(MarkingText);
}

//////////////////////////////////////////////////////////////////////////

void AggregateMarking::SetAggregateMarkingCharacterSet(
    const EntityMarkingCharacterSet EMCS) {
  m_ui8AggregateMarkingCharacterSet = EMCS;
}

//////////////////////////////////////////////////////////////////////////

EntityMarkingCharacterSet AggregateMarking::GetAggregateMarkingCharacterSet()
    const {
  return static_cast<EntityMarkingCharacterSet>(
      m_ui8AggregateMarkingCharacterSet);
}

//////////////////////////////////////////////////////////////////////////

void AggregateMarking::SetAggregateMarkingString(const KString& s) {
  m_sAggregateMarkingString.assign(s);
}

//////////////////////////////////////////////////////////////////////////

KString AggregateMarking::GetAggregateMarkingString() const {
  return m_sAggregateMarkingString.str();
}

//////////////////////////////////////////////////////////////////////////

KString AggregateMarking::GetAsString() const {
  KStringStream ss;

  ss << "Aggregate Marking:" << "\n\tMarking Char Set:      "
     << m_ui8AggregateMarkingCharacterSet
     << "\n\tMarking String:       " << GetAggregateMarkingString() << "\n";

  return ss.str();
}

//////////////////////////////////////////////////////////////////////////

void AggregateMarking::Decode(KDataStream& stream) {
  const std::size_t bounded_len{m_sAggregateMarkingString.max_size()};
  if (stream.GetBufferSize() < bounded_len)
    throw KException(ErrorCode::NOT_ENOUGH_DATA_IN_BUFFER, __FUNCTION__);

  stream >> m_ui8AggregateMarkingCharacterSet;

  for (KUINT16 i = 0; i < bounded_len - 1; ++i) {
    stream >> m_sAggregateMarkingString[i];
  }
  m_sAggregateMarkingString[bounded_len - 1] = '\0';
}

//////////////////////////////////////////////////////////////////////////

KDataStream AggregateMarking::Encode() const {
  KDataStream stream;

  AggregateMarking::Encode(stream);

  return stream;
}

//////////////////////////////////////////////////////////////////////////

void AggregateMarking::Encode(KDataStream& stream) const {
  stream << m_ui8AggregateMarkingCharacterSet;

  for (KUINT16 i = 0; i < m_sAggregateMarkingString.max_size() - 1; ++i) {
    stream << m_sAggregateMarkingString[i];
  }
}

//////////////////////////////////////////////////////////////////////////

KBOOL AggregateMarking::operator==(const AggregateMarking& Value) const {
  if (m_ui8AggregateMarkingCharacterSet !=
      Value.m_ui8AggregateMarkingCharacterSet)
    return false;
  return (m_sAggregateMarkingString == Value.m_sAggregateMarkingString);
}

//////////////////////////////////////////////////////////////////////////

KBOOL AggregateMarking::operator!=(const AggregateMarking& Value) const {
  return !(*this == Value);
}

//////////////////////////////////////////////////////////////////////////
