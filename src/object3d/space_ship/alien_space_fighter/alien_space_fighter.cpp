/************************************************************************************

	AstroMenace
	Hardcore 3D space scroll-shooter with spaceship upgrade possibilities.
	Copyright (c) 2006-2018 Mikhail Kurinnoi, Viewizard


	AstroMenace is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	AstroMenace is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with AstroMenace. If not, see <https://www.gnu.org/licenses/>.


	Website: https://www.viewizard.com/
	Project: https://github.com/viewizard/astromenace
	E-mail: viewizard@viewizard.com

*************************************************************************************/

#include "alien_space_fighter.h"
#include "../../../assets/audio.h"
#include "../../../assets/texture.h"

// NOTE switch to nested namespace definition (namespace A::B::C { ... }) (since C++17)
namespace viewizard {
namespace astromenace {

struct sAlienSpaceFighterData {
	unsigned int WeaponQuantity;
	unsigned int EngineQuantity;
	float Strength;
	float ShieldStrength;
	const char *Name;
};

const sAlienSpaceFighterData PresetAlienSpaceFighterData[] = {
	{1,	4,	5,	0,	"models/alienfighter/al-01.vw3d"},
	{1,	5,	15,	0,	"models/alienfighter/al-02.vw3d"},
	{1,	5,	60,	0,	"models/alienfighter/al-03.vw3d"},
	{4,	8,	40,	0, 	"models/alienfighter/al-04.vw3d"},
	{1,	7,	30,	0,	"models/alienfighter/al-05.vw3d"},
	{1,	6,	120,	0,	"models/alienfighter/al-06.vw3d"},
	{1,	8,	250,	100,	"models/alienfighter/al-07.vw3d"},
	{1,	7,	200,	50,	"models/alienfighter/al-08.vw3d"},
	{2,	11,	500,	200,	"models/alienfighter/al-09.vw3d"},
	{1,	7,	250,	50,	"models/alienfighter/al-10.vw3d"},
	{2,	6,	150,	100,	"models/alienfighter/al-11.vw3d"},
	{1,	5,	200,	100,	"models/alienfighter/al-12.vw3d"},
	{2,	5,	300,	200,	"models/alienfighter/al-13.vw3d"},
	{2,	8,	400,	300,	"models/alienfighter/al-14.vw3d"},
	{6,	4,	50,	100,	"models/alienfighter/al-15.vw3d"},
	{3,	4,	100,	150,	"models/alienfighter/al-16.vw3d"},
	{5,	6,	150,	200,	"models/alienfighter/al-17.vw3d"}
};
#define PresetAlienSpaceFighterDataCount sizeof(PresetAlienSpaceFighterData)/sizeof(PresetAlienSpaceFighterData[0])



//-----------------------------------------------------------------------------
// Создание двигателя
//-----------------------------------------------------------------------------
static void SetAlienSpaceFighterEngine(std::shared_ptr<cParticleSystem> &ParticleSystem, int EngineType)
{
	ParticleSystem->Texture = GetPreloadedTextureAsset("gfx/flare1.tga");
	ParticleSystem->Direction = sVECTOR3D(0.0f, 0.0f, -1.0f);

	switch(EngineType) {
	case 1:
		// большой двигатель
		ParticleSystem->ColorStart.r = 0.00f;
		ParticleSystem->ColorStart.g = 0.70f;
		ParticleSystem->ColorStart.b = 1.00f;
		ParticleSystem->ColorEnd.r = 0.70f;
		ParticleSystem->ColorEnd.g = 1.00f;
		ParticleSystem->ColorEnd.b = 1.00f;
		ParticleSystem->AlphaStart = 1.00f;
		ParticleSystem->AlphaEnd   = 0.00f;
		ParticleSystem->SizeStart  = 0.30f;
		ParticleSystem->SizeVar    = 0.10f;
		ParticleSystem->SizeEnd    = 0.50f;
		ParticleSystem->Speed      = 10.00f;
		ParticleSystem->SpeedOnCreation	   = 10.00f;
		ParticleSystem->Theta      = 0.00f;
		ParticleSystem->Life       = 1.00f;
		ParticleSystem->ParticlesPerSec = 50;
		ParticleSystem->CreationType = eParticleCreationType::Sphere;
		ParticleSystem->CreationSize = sVECTOR3D(0.8f,0.8f,0.8f);
		ParticleSystem->IsMagnet = true;
		ParticleSystem->Light = vw_CreatePointLight(sVECTOR3D(0.0f,0.0f,0.0f), 0.35f, 0.85f, 1.0f, 0.0f, 0.1f);
		ParticleSystem->LightNeedDeviation = true;
		break;
	case 2:
		// малый двигатель
		ParticleSystem->ColorStart.r = 0.00f;
		ParticleSystem->ColorStart.g = 0.70f;
		ParticleSystem->ColorStart.b = 1.00f;
		ParticleSystem->ColorEnd.r = 0.70f;
		ParticleSystem->ColorEnd.g = 1.00f;
		ParticleSystem->ColorEnd.b = 1.00f;
		ParticleSystem->AlphaStart = 1.00f;
		ParticleSystem->AlphaEnd   = 0.20f;
		ParticleSystem->SizeStart  = 0.30f;
		ParticleSystem->SizeVar    = 0.00f;
		ParticleSystem->SizeEnd    = 0.10f;
		ParticleSystem->Speed      = 6.00f;
		ParticleSystem->SpeedOnCreation	   = 6.00f;
		ParticleSystem->Theta      = 20.00f;
		ParticleSystem->Life       = 0.30f;
		ParticleSystem->ParticlesPerSec = 50;
		ParticleSystem->CreationType = eParticleCreationType::Sphere;
		ParticleSystem->CreationSize = sVECTOR3D(0.4f,0.7f,0.1f);
		ParticleSystem->IsMagnet = true;
		ParticleSystem->Light = vw_CreatePointLight(sVECTOR3D(0.0f,0.0f,0.0f), 0.35f, 0.85f, 1.0f, 0.0f, 0.3f);
		ParticleSystem->LightNeedDeviation = true;
		break;
	case 3:
		// кабина
		ParticleSystem->ColorStart.r = 0.00f;
		ParticleSystem->ColorStart.g = 0.70f;
		ParticleSystem->ColorStart.b = 1.00f;
		ParticleSystem->ColorEnd.r = 0.70f;
		ParticleSystem->ColorEnd.g = 1.00f;
		ParticleSystem->ColorEnd.b = 1.00f;
		ParticleSystem->AlphaStart = 0.50f;
		ParticleSystem->AlphaEnd   = 0.00f;
		ParticleSystem->SizeStart  = 0.30f;
		ParticleSystem->SizeVar    = 0.30f;
		ParticleSystem->SizeEnd    = 0.20f;
		ParticleSystem->Speed      = 3.0f;
		ParticleSystem->SpeedOnCreation	   = -1.0f;
		ParticleSystem->Theta      = 360.00f;
		ParticleSystem->Life       = 1.0f;
		ParticleSystem->ParticlesPerSec = 15;
		ParticleSystem->IsMagnet = true;
		break;
	case 4:
		// кабина - высокая, двойная
		ParticleSystem->ColorStart.r = 0.00f;
		ParticleSystem->ColorStart.g = 0.70f;
		ParticleSystem->ColorStart.b = 1.00f;
		ParticleSystem->ColorEnd.r = 0.70f;
		ParticleSystem->ColorEnd.g = 1.00f;
		ParticleSystem->ColorEnd.b = 1.00f;
		ParticleSystem->AlphaStart = 0.50f;
		ParticleSystem->AlphaEnd   = 0.00f;
		ParticleSystem->SizeStart  = 0.50f;
		ParticleSystem->SizeVar    = 0.30f;
		ParticleSystem->SizeEnd    = 0.20f;
		ParticleSystem->Speed      = 3.0f;
		ParticleSystem->SpeedOnCreation	   = -1.0f;
		ParticleSystem->Theta      = 360.00f;
		ParticleSystem->Life       = 1.0f;
		ParticleSystem->ParticlesPerSec = 20;
		ParticleSystem->IsMagnet = true;
		ParticleSystem->CreationType = eParticleCreationType::Sphere;
		ParticleSystem->CreationSize = sVECTOR3D(0.1f,0.9f,0.1f);
		break;
	case 5:
		// основа для очень большого двигателя
		ParticleSystem->ColorStart.r = 0.00f;
		ParticleSystem->ColorStart.g = 0.40f;
		ParticleSystem->ColorStart.b = 1.00f;
		ParticleSystem->ColorEnd.r = 0.00f;
		ParticleSystem->ColorEnd.g = 0.70f;
		ParticleSystem->ColorEnd.b = 1.00f;
		ParticleSystem->AlphaStart = 1.00f;
		ParticleSystem->AlphaEnd   = 0.00f;
		ParticleSystem->SizeStart  = 0.50f;
		ParticleSystem->SizeVar    = 0.10f;
		ParticleSystem->SizeEnd    = 0.10f;
		ParticleSystem->Speed      = 7.00f;
		ParticleSystem->SpeedOnCreation	   = -1.00f;
		ParticleSystem->Theta      = 360.00f;
		ParticleSystem->Life       = 1.50f;
		ParticleSystem->ParticlesPerSec = 40;
		ParticleSystem->IsMagnet = true;
		ParticleSystem->Light = vw_CreatePointLight(sVECTOR3D(0.0f,0.0f,0.0f), 0.0f, 0.55f, 1.0f, 0.0f, 0.1f);
		ParticleSystem->LightNeedDeviation = true;
		break;
	case 6:
		// малый двигатель 2
		ParticleSystem->ColorStart.r = 0.00f;
		ParticleSystem->ColorStart.g = 0.70f;
		ParticleSystem->ColorStart.b = 1.00f;
		ParticleSystem->ColorEnd.r = 0.70f;
		ParticleSystem->ColorEnd.g = 1.00f;
		ParticleSystem->ColorEnd.b = 1.00f;
		ParticleSystem->AlphaStart = 1.00f;
		ParticleSystem->AlphaEnd   = 0.20f;
		ParticleSystem->SizeStart  = 0.30f;
		ParticleSystem->SizeVar    = 0.00f;
		ParticleSystem->SizeEnd    = 0.10f;
		ParticleSystem->Speed      = 6.00f;
		ParticleSystem->SpeedOnCreation	   = 6.00f;
		ParticleSystem->Theta      = 20.00f;
		ParticleSystem->Life       = 0.30f;
		ParticleSystem->ParticlesPerSec = 50;
		ParticleSystem->CreationType = eParticleCreationType::Sphere;
		ParticleSystem->CreationSize = sVECTOR3D(0.5f,0.5f,0.1f);
		ParticleSystem->IsMagnet = true;
		ParticleSystem->Light = vw_CreatePointLight(sVECTOR3D(0.0f,0.0f,0.0f), 0.35f, 0.85f, 1.0f, 0.0f, 0.3f);
		ParticleSystem->LightNeedDeviation = true;
		break;
	case 7:
		// свечение частей
		ParticleSystem->ColorStart.r = 0.00f;
		ParticleSystem->ColorStart.g = 0.70f;
		ParticleSystem->ColorStart.b = 1.00f;
		ParticleSystem->ColorEnd.r = 0.70f;
		ParticleSystem->ColorEnd.g = 1.00f;
		ParticleSystem->ColorEnd.b = 1.00f;
		ParticleSystem->AlphaStart = 1.00f;
		ParticleSystem->AlphaEnd   = 0.20f;
		ParticleSystem->SizeStart  = 0.30f;
		ParticleSystem->SizeVar    = 0.10f;
		ParticleSystem->SizeEnd    = 0.10f;
		ParticleSystem->Speed      = 8.00f;
		ParticleSystem->SpeedOnCreation	   = -1.00f;
		ParticleSystem->Theta      = 0.00f;
		ParticleSystem->Life       = 0.30f;
		ParticleSystem->ParticlesPerSec = 20;
		ParticleSystem->CreationType = eParticleCreationType::Sphere;
		ParticleSystem->CreationSize = sVECTOR3D(0.1f,0.2f,0.1f);
		ParticleSystem->IsMagnet = true;
		break;

	default:
		std::cerr << __func__ << "(): " << "wrong EngineType.\n";
		break;
	}
}

//-----------------------------------------------------------------------------
// Конструктор, инициализация всех переменных
//-----------------------------------------------------------------------------
cAlienSpaceFighter::cAlienSpaceFighter(int SpaceShipNum)
{
	if ((SpaceShipNum <= 0) || ((unsigned int)SpaceShipNum > PresetAlienSpaceFighterDataCount)) {
		std::cerr << __func__ << "(): "
			  << "Could not init cAlienSpaceFighter object with Number " << SpaceShipNum << "\n";
		return;
	}

	ObjectStatus = eObjectStatus::Enemy;
	ObjectType = eObjectType::AlienFighter;
	InternalType = SpaceShipNum;
	PromptDrawDist2 = 100.0f;

	ResistanceHull = 1.0f;
	ResistanceSystems = 1.0f;
	MaxSpeed = 40.0f;
	MaxAcceler = 20.0f;
	MaxSpeedRotate = 40.0f;
	Strength = StrengthStart = PresetAlienSpaceFighterData[SpaceShipNum-1].Strength/GameEnemyArmorPenalty;
	ShieldStrength = ShieldStrengthStart = PresetAlienSpaceFighterData[SpaceShipNum-1].ShieldStrength/GameEnemyArmorPenalty;
	ShieldRecharge = ShieldStrengthStart/10.0f;

	WeaponSlots.resize(PresetAlienSpaceFighterData[SpaceShipNum-1].WeaponQuantity);


	LoadObjectData(PresetAlienSpaceFighterData[SpaceShipNum-1].Name, *this);

	// всегда только эти текстуры и 1 объект
	for (unsigned int i = 0; i < Chunks.size(); i++) {
		Texture[i] = GetPreloadedTextureAsset("models/alienfighter/al-text04.vw2d");
		TextureIllum[i] = GetPreloadedTextureAsset("models/alienfighter/al-illum04.vw2d");
	}

	// начальные установки для двигателей
	Engines.resize(PresetAlienSpaceFighterData[SpaceShipNum - 1].EngineQuantity);
	EnginesLocation.resize(Engines.size());










	// перебираем и ставим нужные данные
	switch (SpaceShipNum) {
	case 1:
		// оружие
		WeaponSlots[0](CreateWeapon(101), sVECTOR3D(0.0f, 0.25f, 1.85f));
		// двигатели
		Engines[0] = vw_CreateParticleSystem();
		EnginesLocation[0] = sVECTOR3D(0.0f, 0.65f, -2.3f);
		if (auto sharedEngine = Engines[0].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[1] = vw_CreateParticleSystem();
		EnginesLocation[1] = sVECTOR3D(-1.9f, 0.45f, -3.8f);
		if (auto sharedEngine = Engines[1].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[2] = vw_CreateParticleSystem();
		EnginesLocation[2] = sVECTOR3D(1.9f, 0.45f, -3.8f);
		if (auto sharedEngine = Engines[2].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[3] = vw_CreateParticleSystem();
		EnginesLocation[3] = sVECTOR3D(0.0f, 0.25f, 1.85f);
		if (auto sharedEngine = Engines[3].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 3);
		break;
	case 2:
		// оружие
		WeaponSlots[0](CreateWeapon(101), sVECTOR3D(0.0f, -0.30f, 3.95f));
		// двигатели
		Engines[0] = vw_CreateParticleSystem();
		EnginesLocation[0] = sVECTOR3D(0.0f, 0.8f, -3.1f);
		if (auto sharedEngine = Engines[0].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[1] = vw_CreateParticleSystem();
		EnginesLocation[1] = sVECTOR3D(0.0f, -1.0f, -4.3f);
		if (auto sharedEngine = Engines[1].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[2] = vw_CreateParticleSystem();
		EnginesLocation[2] = sVECTOR3D(2.85f, 1.1f, -5.8f);
		if (auto sharedEngine = Engines[2].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[3] = vw_CreateParticleSystem();
		EnginesLocation[3] = sVECTOR3D(-2.85f, 1.1f, -5.8f);
		if (auto sharedEngine = Engines[3].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[4] = vw_CreateParticleSystem();
		EnginesLocation[4] = sVECTOR3D(0.0f, -0.30f, 3.95f);
		if (auto sharedEngine = Engines[4].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 7);
			sharedEngine->Direction = sVECTOR3D(0.0f, 0.3f, -1.0f);
		}
		break;
	case 3:
		// оружие
		WeaponSlots[0](CreateWeapon(102), sVECTOR3D(0.0f, -0.35f, 3.9f));
		// двигатели
		Engines[0] = vw_CreateParticleSystem();
		EnginesLocation[0] = sVECTOR3D(0.0f, 0.8f, -5.5f);
		if (auto sharedEngine = Engines[0].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[1] = vw_CreateParticleSystem();
		EnginesLocation[1] = sVECTOR3D(0.0f, -1.1f, -6.5f);
		if (auto sharedEngine = Engines[1].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[2] = vw_CreateParticleSystem();
		EnginesLocation[2] = sVECTOR3D(5.6f, 1.1f, -3.3f);
		if (auto sharedEngine = Engines[2].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[3] = vw_CreateParticleSystem();
		EnginesLocation[3] = sVECTOR3D(-5.6f, 1.1f, -3.3f);
		if (auto sharedEngine = Engines[3].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[4] = vw_CreateParticleSystem();
		EnginesLocation[4] = sVECTOR3D(0.0f, -0.35f, 3.9f);
		if (auto sharedEngine = Engines[4].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 7);
			sharedEngine->SizeStart = 0.40f;
			sharedEngine->SizeVar = 0.20f;
			sharedEngine->Speed = 9.0f;
			sharedEngine->Direction = sVECTOR3D(0.0f, -0.3f, 1.0f);
		}
		break;
	case 4:
		// оружие
		WeaponSlots[0](CreateWeapon(101), sVECTOR3D(0.75f, -0.15f, 5.1f));
		WeaponSlots[1](CreateWeapon(101), sVECTOR3D(-0.75f, -0.15f, 5.1f));
		WeaponSlots[2](CreateWeapon(101), sVECTOR3D(0.85f, -1.4f, 6.5f));
		WeaponSlots[3](CreateWeapon(101), sVECTOR3D(-0.85f, -1.4f, 6.5f));
		WeaponSlots[1].Weapon->SFX = eGameSFX::none;
		WeaponSlots[2].Weapon->SFX = eGameSFX::none;
		WeaponSlots[3].Weapon->SFX = eGameSFX::none;
		WeaponFireType = 1;

		// двигатели
		Engines[0] = vw_CreateParticleSystem();
		EnginesLocation[0] = sVECTOR3D(0.0f, 1.4f, -3.7f);
		if (auto sharedEngine = Engines[0].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[1] = vw_CreateParticleSystem();
		EnginesLocation[1] = sVECTOR3D(0.0f, -0.6f, -5.0f);
		if (auto sharedEngine = Engines[1].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[2] = vw_CreateParticleSystem();
		EnginesLocation[2] = sVECTOR3D(1.5f, 1.9f, -7.1f);
		if (auto sharedEngine = Engines[2].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[3] = vw_CreateParticleSystem();
		EnginesLocation[3] = sVECTOR3D(-1.5f, 1.9f, -7.1f);
		if (auto sharedEngine = Engines[3].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[4] = vw_CreateParticleSystem();
		EnginesLocation[4] = sVECTOR3D(0.75f, -0.15f, 5.1f);
		if (auto sharedEngine = Engines[4].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 3);
		Engines[5] = vw_CreateParticleSystem();
		EnginesLocation[5] = sVECTOR3D(-0.75f, -0.15f, 5.1f);
		if (auto sharedEngine = Engines[5].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 3);
		Engines[6] = vw_CreateParticleSystem();
		EnginesLocation[6] = sVECTOR3D(0.85f, -1.4f, 6.5f);
		if (auto sharedEngine = Engines[6].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 3);
		Engines[7] = vw_CreateParticleSystem();
		EnginesLocation[7] = sVECTOR3D(-0.85f, -1.4f, 6.5f);
		if (auto sharedEngine = Engines[7].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 3);
		break;
	case 5:
		MaxSpeedRotate = 720.0f;
		// оружие
		WeaponSlots[0](CreateWeapon(103), sVECTOR3D(0.0f, 0.0f, 0.0f));
		// двигатели
		Engines[0] = vw_CreateParticleSystem();
		EnginesLocation[0] = sVECTOR3D(1.0f, 0.0f, -4.0f);
		if (auto sharedEngine = Engines[0].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[1] = vw_CreateParticleSystem();
		EnginesLocation[1] = sVECTOR3D(-1.0f, 0.0f, -4.0f);
		if (auto sharedEngine = Engines[1].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[2] = vw_CreateParticleSystem();
		EnginesLocation[2] = sVECTOR3D(0.0f, 0.0f, -2.2f);
		if (auto sharedEngine = Engines[2].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 4);
		Engines[3] = vw_CreateParticleSystem();
		EnginesLocation[3] = sVECTOR3D(1.0f, 0.0f, -2.0f);
		if (auto sharedEngine = Engines[3].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 4);
		Engines[4] = vw_CreateParticleSystem();
		EnginesLocation[4] = sVECTOR3D(-1.0f, 0.0f, -2.0f);
		if (auto sharedEngine = Engines[4].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 4);
		Engines[5] = vw_CreateParticleSystem();
		EnginesLocation[5] = sVECTOR3D(1.7f, 0.0f, -1.3f);
		if (auto sharedEngine = Engines[5].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 4);
		Engines[6] = vw_CreateParticleSystem();
		EnginesLocation[6] = sVECTOR3D(-1.7f, 0.0f, -1.3f);
		if (auto sharedEngine = Engines[6].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 4);
		break;
	case 6:
		// оружие
		WeaponSlots[0](CreateWeapon(104), sVECTOR3D(0.0f, 0.35f, 2.65f));
		// двигатели
		Engines[0] = vw_CreateParticleSystem();
		EnginesLocation[0] = sVECTOR3D(0.0f, 2.4f, -7.4f);
		if (auto sharedEngine = Engines[0].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[1] = vw_CreateParticleSystem();
		EnginesLocation[1] = sVECTOR3D(0.0f, 2.4f, -7.4f);
		if (auto sharedEngine = Engines[1].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 5);
		Engines[2] = vw_CreateParticleSystem();
		EnginesLocation[2] = sVECTOR3D(0.0f, -1.3f, -5.0f);
		if (auto sharedEngine = Engines[2].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[3] = vw_CreateParticleSystem();
		EnginesLocation[3] = sVECTOR3D(4.05f, 1.4f, -6.8f);
		if (auto sharedEngine = Engines[3].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[4] = vw_CreateParticleSystem();
		EnginesLocation[4] = sVECTOR3D(-4.05f, 1.4f, -6.8f);
		if (auto sharedEngine = Engines[4].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[5] = vw_CreateParticleSystem();
		EnginesLocation[5] = sVECTOR3D(0.0f, 0.35f, 2.65f);
		if (auto sharedEngine = Engines[5].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 3);
			sharedEngine->SizeStart = 0.50f;
		}
		break;
	case 7:
		// оружие
		WeaponSlots[0](CreateWeapon(105), sVECTOR3D(0.0f, -0.70f, 7.0f));
		// двигатели
		Engines[0] = vw_CreateParticleSystem();
		EnginesLocation[0] = sVECTOR3D(0.0f, 1.8f, -10.2f);
		if (auto sharedEngine = Engines[0].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[1] = vw_CreateParticleSystem();
		EnginesLocation[1] = sVECTOR3D(0.0f, -1.8f, -3.1f);
		if (auto sharedEngine = Engines[1].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[2] = vw_CreateParticleSystem();
		EnginesLocation[2] = sVECTOR3D(3.4f, 1.0f, -5.6f);
		if (auto sharedEngine = Engines[2].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 6);
		Engines[3] = vw_CreateParticleSystem();
		EnginesLocation[3] = sVECTOR3D(-3.4f, 1.0f, -5.6f);
		if (auto sharedEngine = Engines[3].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 6);
		Engines[4] = vw_CreateParticleSystem();
		EnginesLocation[4] = sVECTOR3D(0.0f, -0.70f, 7.0f);
		if (auto sharedEngine = Engines[4].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 7);
			sharedEngine->SizeStart = 0.40f;
			sharedEngine->SizeVar = 0.20f;
			sharedEngine->Direction = sVECTOR3D(0.0f, 0.3f, -1.0f);
		}
		Engines[5] = vw_CreateParticleSystem();
		EnginesLocation[5] = sVECTOR3D(1.6f, -2.2f, 6.5f);
		if (auto sharedEngine = Engines[5].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 7);
			sharedEngine->Direction = sVECTOR3D(-0.3f, 0.0f, 1.0f);
		}
		Engines[6] = vw_CreateParticleSystem();
		EnginesLocation[6] = sVECTOR3D(-1.6f, -2.2f, 6.5f);
		if (auto sharedEngine = Engines[6].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 7);
			sharedEngine->Direction = sVECTOR3D(0.3f, 0.0f, 1.0f);
		}
		Engines[7] = vw_CreateParticleSystem();
		EnginesLocation[7] = sVECTOR3D(0.0f, 1.8f, -10.2f);
		if (auto sharedEngine = Engines[7].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 5);
		break;
	case 8:
		// оружие
		WeaponSlots[0](CreateWeapon(103), sVECTOR3D(0.0f, 1.10f, -0.5f));
		WeaponSlots[0].Weapon->NextFireTime /= 4.0f;
		// двигатели
		Engines[0] = vw_CreateParticleSystem();
		EnginesLocation[0] = sVECTOR3D(0.0f, 1.4f, -8.6f);
		if (auto sharedEngine = Engines[0].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[1] = vw_CreateParticleSystem();
		EnginesLocation[1] = sVECTOR3D(0.0f, -0.2f, -9.7f);
		if (auto sharedEngine = Engines[1].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[2] = vw_CreateParticleSystem();
		EnginesLocation[2] = sVECTOR3D(5.0f, 2.25f, -7.3f);
		if (auto sharedEngine = Engines[2].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 6);
		Engines[3] = vw_CreateParticleSystem();
		EnginesLocation[3] = sVECTOR3D(-5.0f, 2.25f, -7.3f);
		if (auto sharedEngine = Engines[3].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 6);
		Engines[4] = vw_CreateParticleSystem();
		EnginesLocation[4] = sVECTOR3D(0.0f, 1.10f, -0.5f);
		if (auto sharedEngine = Engines[4].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 7);
			sharedEngine->SizeStart = 0.60f;
			sharedEngine->SizeVar = 0.10f;
			sharedEngine->Direction = sVECTOR3D(0.0f, -0.3f, 1.0f);
		}
		Engines[5] = vw_CreateParticleSystem();
		EnginesLocation[5] = sVECTOR3D(1.25f, -0.95f, 5.4f);
		if (auto sharedEngine = Engines[5].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 7);
			sharedEngine->Direction = sVECTOR3D(-0.22f, 0.25f, 1.0f);
		}
		Engines[6] = vw_CreateParticleSystem();
		EnginesLocation[6] = sVECTOR3D(-1.25f, -0.95f, 5.4f);
		if (auto sharedEngine = Engines[6].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 7);
			sharedEngine->Direction = sVECTOR3D(0.22f, 0.25f, 1.0f);
		}
		break;
	case 9:
		// оружие
		WeaponSlots[0](CreateWeapon(103), sVECTOR3D(0.0f, 0.10f, 4.9f));
		WeaponSlots[0].Weapon->NextFireTime /= 3.0f;
		WeaponSlots[1](CreateWeapon(107), sVECTOR3D(0.0f, 0.0f, 0.0f));
		WeaponFireType = 1;
		// двигатели
		Engines[0] = vw_CreateParticleSystem();
		EnginesLocation[0] = sVECTOR3D(0.0f, 0.2f, -5.8f);
		if (auto sharedEngine = Engines[0].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[1] = vw_CreateParticleSystem();
		EnginesLocation[1] = sVECTOR3D(0.0f, -1.4f, -6.6f);
		if (auto sharedEngine = Engines[1].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[2] = vw_CreateParticleSystem();
		EnginesLocation[2] = sVECTOR3D(3.0f, 1.5f, -8.0f);
		if (auto sharedEngine = Engines[2].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[3] = vw_CreateParticleSystem();
		EnginesLocation[3] = sVECTOR3D(-3.0f, 1.5f, -8.0f);
		if (auto sharedEngine = Engines[3].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[4] = vw_CreateParticleSystem();
		EnginesLocation[4] = sVECTOR3D(3.0f, 1.5f, -8.0f);
		if (auto sharedEngine = Engines[4].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 5);
		Engines[5] = vw_CreateParticleSystem();
		EnginesLocation[5] = sVECTOR3D(-3.0f, 1.5f, -8.0f);
		if (auto sharedEngine = Engines[5].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 5);
		Engines[6] = vw_CreateParticleSystem();
		EnginesLocation[6] = sVECTOR3D(7.1f, 0.6f, -4.9f);
		if (auto sharedEngine = Engines[6].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 6);
		Engines[7] = vw_CreateParticleSystem();
		EnginesLocation[7] = sVECTOR3D(-7.1f, 0.6f, -4.9f);
		if (auto sharedEngine = Engines[7].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 6);
		Engines[8] = vw_CreateParticleSystem();
		EnginesLocation[8] = sVECTOR3D(0.0f, 0.10f, 4.9f);
		if (auto sharedEngine = Engines[8].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 7);
			sharedEngine->SizeStart = 0.50f;
			sharedEngine->Direction = sVECTOR3D(0.0f, 0.3f, -1.0f);
		}
		Engines[9] = vw_CreateParticleSystem();
		EnginesLocation[9] = sVECTOR3D(2.05f, -1.15f, 4.15f);
		if (auto sharedEngine = Engines[9].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 7);
			sharedEngine->Direction = sVECTOR3D(-0.6f, 0.0f, 0.5f);
			sharedEngine->SizeVar = sharedEngine->SizeEnd = 0.20f;
		}
		Engines[10] = vw_CreateParticleSystem();
		EnginesLocation[10] = sVECTOR3D(-2.05f, -1.15f, 4.15f);
		if (auto sharedEngine = Engines[10].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 7);
			sharedEngine->Direction = sVECTOR3D(0.6f, 0.0f, 0.5f);
			sharedEngine->SizeVar = sharedEngine->SizeEnd = 0.20f;
		}
		break;
	case 10:
		// оружие
		WeaponSlots[0](CreateWeapon(106), sVECTOR3D(0.0f, 0.0f, 0.0f));
		// двигатели
		Engines[0] = vw_CreateParticleSystem();
		EnginesLocation[0] = sVECTOR3D(0.0f, 0.8f, -4.0f);
		if (auto sharedEngine = Engines[0].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[1] = vw_CreateParticleSystem();
		EnginesLocation[1] = sVECTOR3D(0.0f, -1.2f, -4.8f);
		if (auto sharedEngine = Engines[1].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[2] = vw_CreateParticleSystem();
		EnginesLocation[2] = sVECTOR3D(3.8f, 0.7f, -5.7f);
		if (auto sharedEngine = Engines[2].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[3] = vw_CreateParticleSystem();
		EnginesLocation[3] = sVECTOR3D(-3.8f, 0.7f, -5.7f);
		if (auto sharedEngine = Engines[3].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[4] = vw_CreateParticleSystem();
		EnginesLocation[4] = sVECTOR3D(3.8f, 0.7f, -5.7f);
		if (auto sharedEngine = Engines[4].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 5);
		Engines[5] = vw_CreateParticleSystem();
		EnginesLocation[5] = sVECTOR3D(-3.8f, 0.7f, -5.7f);
		if (auto sharedEngine = Engines[5].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 5);
		Engines[6] = vw_CreateParticleSystem();
		EnginesLocation[6] = sVECTOR3D(0.0f, 0.65f, 4.65f);
		if (auto sharedEngine = Engines[6].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 4);
			sharedEngine->CreationSize = sVECTOR3D(2.4f,0.6f,0.1f);
			sharedEngine->ParticlesPerSec = 50;
		}
		break;
	case 11:
		// оружие
		WeaponSlots[0](CreateWeapon(104), sVECTOR3D(3.9f, 1.3f, 1.0f));
		WeaponSlots[1](CreateWeapon(104), sVECTOR3D(-3.9f, 1.3f, 1.0f));
		// двигатели
		Engines[0] = vw_CreateParticleSystem();
		EnginesLocation[0] = sVECTOR3D(0.0f, 1.0f, -5.4f);
		if (auto sharedEngine = Engines[0].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[1] = vw_CreateParticleSystem();
		EnginesLocation[1] = sVECTOR3D(0.0f, -0.3f, -6.2f);
		if (auto sharedEngine = Engines[1].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 1);
		Engines[2] = vw_CreateParticleSystem();
		EnginesLocation[2] = sVECTOR3D(2.25f, -1.1f, -4.1f);
		if (auto sharedEngine = Engines[2].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[3] = vw_CreateParticleSystem();
		EnginesLocation[3] = sVECTOR3D(-2.25f, -1.1f, -4.1f);
		if (auto sharedEngine = Engines[3].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[4] = vw_CreateParticleSystem();
		EnginesLocation[4] = sVECTOR3D(0.0f, 0.50f, 0.15f);
		if (auto sharedEngine = Engines[4].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 3);
			sharedEngine->SizeStart = 0.2f;
			sharedEngine->SizeVar = 0.1f;
			sharedEngine->Speed = 2.0f;
		}
		Engines[5] = vw_CreateParticleSystem();
		EnginesLocation[5] = sVECTOR3D(0.0f, 1.15f, -1.1f);
		if (auto sharedEngine = Engines[5].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 7);
			sharedEngine->Direction = sVECTOR3D(0.0f, -0.3f, 1.0f);
			sharedEngine->Speed = 5.0f;
		}
		break;
	case 12:
		// оружие
		WeaponSlots[0](CreateWeapon(108), sVECTOR3D(0.0f, 0.50f, 0.8f));
		// двигатели
		Engines[0] = vw_CreateParticleSystem();
		EnginesLocation[0] = sVECTOR3D(1.1f, 1.0f, -4.4f);
		if (auto sharedEngine = Engines[0].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[1] = vw_CreateParticleSystem();
		EnginesLocation[1] = sVECTOR3D(-1.1f, 1.0f, -4.4f);
		if (auto sharedEngine = Engines[1].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[2] = vw_CreateParticleSystem();
		EnginesLocation[2] = sVECTOR3D(1.1f, -1.0f, -4.4f);
		if (auto sharedEngine = Engines[2].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[3] = vw_CreateParticleSystem();
		EnginesLocation[3] = sVECTOR3D(-1.1f, -1.0f, -4.4f);
		if (auto sharedEngine = Engines[3].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[4] = vw_CreateParticleSystem();
		EnginesLocation[4] = sVECTOR3D(0.0f, 0.50f, 1.1f);
		if (auto sharedEngine = Engines[4].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 4);
			sharedEngine->CreationSize = sVECTOR3D(1.0f,0.1f,0.1f);
		}
		break;
	case 13:
		// оружие
		WeaponSlots[0](CreateWeapon(109), sVECTOR3D(3.0f, 0.0f, 0.5f));
		WeaponSlots[1](CreateWeapon(109), sVECTOR3D(-3.0f, 0.0f, 0.5f));
		// двигатели
		Engines[0] = vw_CreateParticleSystem();
		EnginesLocation[0] = sVECTOR3D(1.1f, 1.0f, -4.4f);
		if (auto sharedEngine = Engines[0].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[1] = vw_CreateParticleSystem();
		EnginesLocation[1] = sVECTOR3D(-1.1f, 1.0f, -4.4f);
		if (auto sharedEngine = Engines[1].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[2] = vw_CreateParticleSystem();
		EnginesLocation[2] = sVECTOR3D(1.1f, -1.0f, -4.4f);
		if (auto sharedEngine = Engines[2].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[3] = vw_CreateParticleSystem();
		EnginesLocation[3] = sVECTOR3D(-1.1f, -1.0f, -4.4f);
		if (auto sharedEngine = Engines[3].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[4] = vw_CreateParticleSystem();
		EnginesLocation[4] = sVECTOR3D(0.0f, 0.00f, 1.1f);
		if (auto sharedEngine = Engines[4].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 4);
			sharedEngine->CreationSize = sVECTOR3D(0.1f,1.2f,0.1f);
		}
		break;
	case 14:
		// оружие
		WeaponSlots[0](CreateWeapon(108), sVECTOR3D(3.0f, 0.0f, 0.5f));
		WeaponSlots[1](CreateWeapon(108), sVECTOR3D(-3.0f, 0.0f, 0.5f));
		// двигатели
		Engines[0] = vw_CreateParticleSystem();
		EnginesLocation[0] = sVECTOR3D(1.1f, 1.1f, -4.9f);
		if (auto sharedEngine = Engines[0].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[1] = vw_CreateParticleSystem();
		EnginesLocation[1] = sVECTOR3D(-1.1f, 1.1f, -4.9f);
		if (auto sharedEngine = Engines[1].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[2] = vw_CreateParticleSystem();
		EnginesLocation[2] = sVECTOR3D(1.1f, -1.1f, -4.9f);
		if (auto sharedEngine = Engines[2].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[3] = vw_CreateParticleSystem();
		EnginesLocation[3] = sVECTOR3D(-1.1f, -1.1f, -4.9f);
		if (auto sharedEngine = Engines[3].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[4] = vw_CreateParticleSystem();
		EnginesLocation[4] = sVECTOR3D(0.75f, -0.25f, 3.8f);
		if (auto sharedEngine = Engines[4].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 3);
		Engines[5] = vw_CreateParticleSystem();
		EnginesLocation[5] = sVECTOR3D(-0.75f, -0.25f, 3.8f);
		if (auto sharedEngine = Engines[5].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 3);
		Engines[6] = vw_CreateParticleSystem();
		EnginesLocation[6] = sVECTOR3D(0.8f, -1.7f, 4.4f);
		if (auto sharedEngine = Engines[6].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 3);
		Engines[7] = vw_CreateParticleSystem();
		EnginesLocation[7] = sVECTOR3D(-0.8f, -1.7f, 4.4f);
		if (auto sharedEngine = Engines[7].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 3);
		break;
	case 15:
		// оружие
		WeaponSlots[0](CreateWeapon(102), sVECTOR3D(3.8f, -1.8f, 0.5f));
		WeaponSlots[1](CreateWeapon(102), sVECTOR3D(-3.8f, -1.8f, 0.5f));
		WeaponSlots[2](CreateWeapon(101), sVECTOR3D(0.2f, 1.9f, -3.0f));
		WeaponSlots[3](CreateWeapon(101), sVECTOR3D(-0.2f, 1.6f, -3.0f));
		WeaponSlots[4](CreateWeapon(101), sVECTOR3D(0.2f, 1.4f, -3.0f));
		WeaponSlots[5](CreateWeapon(101), sVECTOR3D(-0.2f, 1.1f, -3.0f));
		// двигатели
		Engines[0] = vw_CreateParticleSystem();
		EnginesLocation[0] = sVECTOR3D(0.0f, 2.4f, -4.0f);
		if (auto sharedEngine = Engines[0].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[1] = vw_CreateParticleSystem();
		EnginesLocation[1] = sVECTOR3D(0.0f, -0.1f, -4.0f);
		if (auto sharedEngine = Engines[1].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[2] = vw_CreateParticleSystem();
		EnginesLocation[2] = sVECTOR3D(0.0f, 1.2f, -4.0f);
		if (auto sharedEngine = Engines[2].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[3] = vw_CreateParticleSystem();
		EnginesLocation[3] = sVECTOR3D(0.0f, 1.0f, -2.1f);
		if (auto sharedEngine = Engines[3].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 4);
			sharedEngine->CreationSize = sVECTOR3D(1.0f,2.4f,0.1f);
			sharedEngine->ParticlesPerSec = 40;
		}
		break;
	case 16:
		// оружие
		WeaponSlots[0](CreateWeapon(102), sVECTOR3D(3.7f, -1.9f, 1.5f));
		WeaponSlots[1](CreateWeapon(102), sVECTOR3D(-3.7f, -1.9f, 1.5f));
		WeaponSlots[2](CreateWeapon(108), sVECTOR3D(0.0f, 0.2f, -0.8f));
		// двигатели
		Engines[0] = vw_CreateParticleSystem();
		EnginesLocation[0] = sVECTOR3D(2.8f, 0.2f, -7.2f);
		if (auto sharedEngine = Engines[0].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[1] = vw_CreateParticleSystem();
		EnginesLocation[1] = sVECTOR3D(-2.8f, 0.2f, -7.2f);
		if (auto sharedEngine = Engines[1].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 2);
		Engines[2] = vw_CreateParticleSystem();
		EnginesLocation[2] = sVECTOR3D(0.0f, 1.2f, -0.8f);
		if (auto sharedEngine = Engines[2].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 4);
			sharedEngine->CreationSize = sVECTOR3D(0.6f,1.7f,0.4f);
			sharedEngine->ParticlesPerSec = 40;
		}
		Engines[3] = vw_CreateParticleSystem();
		EnginesLocation[3] = sVECTOR3D(0.0f, 0.2f, -0.8f);
		if (auto sharedEngine = Engines[3].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 4);
			sharedEngine->CreationSize = sVECTOR3D(3.0f,0.4f,0.8f);
			sharedEngine->ParticlesPerSec = 40;
		}
		break;
	case 17:
		// оружие
		WeaponSlots[0](CreateWeapon(108), sVECTOR3D(0.0f, -0.85f, 1.0f));
		WeaponSlots[1](CreateWeapon(105), sVECTOR3D(1.7f, -0.85f, 1.9f));
		WeaponSlots[2](CreateWeapon(105), sVECTOR3D(-1.7f, -0.85f, 1.9f));
		WeaponSlots[3](CreateWeapon(105), sVECTOR3D(1.0f, -0.85f, 1.1f));
		WeaponSlots[4](CreateWeapon(105), sVECTOR3D(-1.0f, -0.85f, 1.1f));
		// двигатели
		Engines[0] = vw_CreateParticleSystem();
		EnginesLocation[0] = sVECTOR3D(1.8f, 1.0f, -7.2f);
		if (auto sharedEngine = Engines[0].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 2);
			sharedEngine->CreationSize = sVECTOR3D(0.4f,0.4f,0.1f);
		}
		Engines[1] = vw_CreateParticleSystem();
		EnginesLocation[1] = sVECTOR3D(-1.8f, 1.0f, -7.2f);
		if (auto sharedEngine = Engines[1].lock()) {
			SetAlienSpaceFighterEngine(sharedEngine, 2);
			sharedEngine->CreationSize = sVECTOR3D(0.4f,0.4f,0.1f);
		}
		Engines[2] = vw_CreateParticleSystem();
		EnginesLocation[2] = sVECTOR3D(1.0f, -0.85f, 1.1f);
		if (auto sharedEngine = Engines[2].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 4);
		Engines[3] = vw_CreateParticleSystem();
		EnginesLocation[3] = sVECTOR3D(-1.0f, -0.85f, 1.1f);
		if (auto sharedEngine = Engines[3].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 4);
		Engines[4] = vw_CreateParticleSystem();
		EnginesLocation[4] = sVECTOR3D(1.7f, -0.85f, 1.9f);
		if (auto sharedEngine = Engines[4].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 4);
		Engines[5] = vw_CreateParticleSystem();
		EnginesLocation[5] = sVECTOR3D(-1.7f, -0.85f, 1.9f);
		if (auto sharedEngine = Engines[5].lock())
			SetAlienSpaceFighterEngine(sharedEngine, 4);
		break;


	default:
		std::cerr << __func__ << "(): " << "wrong SpaceShipNum.\n";
		return;
	}

	for (unsigned int i = 0; i < Engines.size(); i++) {
		if (auto sharedEngine = Engines[i].lock()) {
			sharedEngine->SetStartLocation(EnginesLocation[i]);
			// находим кол-во внутренних источников света
			if (!sharedEngine->Light.expired())
				InternalLights++;
		}
	}
}

} // astromenace namespace
} // viewizard namespace
