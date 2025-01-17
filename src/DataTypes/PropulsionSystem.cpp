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

#include "KDIS/DataTypes/PropulsionSystem.hpp"

using namespace KDIS;
using namespace DATA_TYPE;
using namespace ENUMS;

//////////////////////////////////////////////////////////////////////////
// Public:
//////////////////////////////////////////////////////////////////////////

PropulsionSystem::PropulsionSystem()
    : m_f32PowerSetting(0), m_f32EngineRPM(0) {}

//////////////////////////////////////////////////////////////////////////

PropulsionSystem::PropulsionSystem(KDataStream& stream) { Decode(stream); }

//////////////////////////////////////////////////////////////////////////

PropulsionSystem::PropulsionSystem(KFLOAT32 PowerSetting, KFLOAT32 EngineRPM)
    : m_f32PowerSetting(PowerSetting), m_f32EngineRPM(EngineRPM) {}

//////////////////////////////////////////////////////////////////////////

PropulsionSystem::~PropulsionSystem() {}

//////////////////////////////////////////////////////////////////////////

void PropulsionSystem::SetPowerSetting(KFLOAT32 PS) { m_f32PowerSetting = PS; }

//////////////////////////////////////////////////////////////////////////

void PropulsionSystem::SetPowerSetting(PowerSettingAircraft PS) {
  m_f32PowerSetting = PS;
}

//////////////////////////////////////////////////////////////////////////

void PropulsionSystem::SetPowerSetting(PowerSettingHelicopter PS) {
  m_f32PowerSetting = PS;
}

//////////////////////////////////////////////////////////////////////////

void PropulsionSystem::SetPowerSetting(ActiveEmissionParameterIndex PS) {
  m_f32PowerSetting = PS;
}

//////////////////////////////////////////////////////////////////////////

KFLOAT32 PropulsionSystem::GetPowerSetting() const { return m_f32PowerSetting; }

//////////////////////////////////////////////////////////////////////////

void PropulsionSystem::SetEngineRPM(KFLOAT32 RPM) { m_f32EngineRPM = RPM; }

//////////////////////////////////////////////////////////////////////////

KFLOAT32 PropulsionSystem::GetEngineRPM() const { return m_f32EngineRPM; }

//////////////////////////////////////////////////////////////////////////

KString PropulsionSystem::GetAsString() const {
  KStringStream ss;

  ss << "Propulsion System:" << "\n\tPower Setting:  " << m_f32PowerSetting
     << "\n\tEngine RPM:     " << m_f32EngineRPM << "\n";

  return ss.str();
}

//////////////////////////////////////////////////////////////////////////

void PropulsionSystem::Decode(KDataStream& stream) {
  if (stream.GetBufferSize() < PROPULSION_SYSTEM_SIZE)
    throw KException(ErrorCode::NOT_ENOUGH_DATA_IN_BUFFER, __FUNCTION__);

  stream >> m_f32PowerSetting >> m_f32EngineRPM;
}

//////////////////////////////////////////////////////////////////////////

KDataStream PropulsionSystem::Encode() const {
  KDataStream stream;

  PropulsionSystem::Encode(stream);

  return stream;
}

//////////////////////////////////////////////////////////////////////////

void PropulsionSystem::Encode(KDataStream& stream) const {
  stream << m_f32PowerSetting << m_f32EngineRPM;
}

//////////////////////////////////////////////////////////////////////////

KBOOL PropulsionSystem::operator==(const PropulsionSystem& Value) const {
  if (m_f32PowerSetting != Value.m_f32PowerSetting) return false;
  if (m_f32EngineRPM != Value.m_f32EngineRPM) return false;
  return true;
}

//////////////////////////////////////////////////////////////////////////

KBOOL PropulsionSystem::operator!=(const PropulsionSystem& Value) const {
  return !(*this == Value);
}

//////////////////////////////////////////////////////////////////////////
