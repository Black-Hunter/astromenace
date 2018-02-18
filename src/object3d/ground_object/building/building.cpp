/************************************************************************************

	AstroMenace (Hardcore 3D space shooter with spaceship upgrade possibilities)
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
	along with AstroMenace. If not, see <http://www.gnu.org/licenses/>.


	Web Site: http://www.viewizard.com/
	Project: https://github.com/viewizard/astromenace
	E-mail: viewizard@viewizard.com

*************************************************************************************/


/// подключаем нужные файлы
#include "building.h"



struct BuildingData
{
	float	Strength;
	const	char *Name;
};

static BuildingData PresetBuildingData[] =
{
	{150,	"models/building/bld-01.vw3d"},
	{150,	"models/building/bld-02.vw3d"},
	{150,	"models/building/bld-03.vw3d"},
	{150,	"models/building/bld-04.vw3d"},
	{150,	"models/building/bld-05.vw3d"},
	{150,	"models/building/bld-06.vw3d"},
	{150,	"models/building/bld-07.vw3d"},
	{150,	"models/building/bld-08.vw3d"},
	{150,	"models/building/bld-09.vw3d"},
	{150,	"models/building/bld-10.vw3d"},
	{150,	"models/building/bld-11.vw3d"}
};
#define PresetBuildingDataCount sizeof(PresetBuildingData)/sizeof(PresetBuildingData[0])



//-----------------------------------------------------------------------------
// Конструктор, инициализация всех переменных
//-----------------------------------------------------------------------------
void CBuilding::Create(int	BuildingNum)
{
	if ((BuildingNum <= 0) || ((unsigned int)BuildingNum > PresetBuildingDataCount))
	{
		fprintf(stderr, "!!! Couldn't init CBuilding object with Number %i.\n", BuildingNum);
		return;
	}

	ObjectType = 12;
	ObjectCreationType = BuildingNum;
	// здания неразрушимы, не показываем вообще их жизнь
	ShowStrength = false;
	PromptDrawDist2 = 100.0f;

	LoadObjectData(PresetBuildingData[BuildingNum-1].Name, this, 0, -1.0f, Setup.UseGLSL);

	for (int i=0; i<DrawObjectQuantity; i++)
	{
		Texture[i] = vw_FindTextureByName("models/building/bld.vw2d");
		TextureIllum[i] = vw_FindTextureByName("models/building/bld_illum.vw2d");
		NormalMap[i] = vw_FindTextureByName("models/normalmap/buildings_nm.tga");
	}

	ResistanceHull = 1.0f;
	ResistanceSystems = 1.0f;

	Strength = StrengthStart = PresetBuildingData[BuildingNum-1].Strength/GameNPCArmorPenalty;


	// находим все данные по геометрии
	::CObject3D::InitByDrawObjectList();
}
