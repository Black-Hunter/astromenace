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


#include "game_level_text.h"




CGameLvlText * StartText = nullptr;
CGameLvlText * EndText = nullptr;




//-----------------------------------------------------------------------------
//	Присоеденяем Text к списку
//-----------------------------------------------------------------------------
void AttachGameLvlText(CGameLvlText * NewText)
{
	if (NewText == nullptr)
		return;

	// первый в списке...
	if (EndText == nullptr) {
		NewText->Prev = nullptr;
		NewText->Next = nullptr;
		StartText = NewText;
		EndText = NewText;
	} else { // продолжаем заполнение...
		NewText->Prev = EndText;
		NewText->Next = nullptr;
		EndText->Next = NewText;
		EndText = NewText;
	}

}




//-----------------------------------------------------------------------------
//	Удаляем Text из списка
//-----------------------------------------------------------------------------
void DetachGameLvlText(CGameLvlText * OldText)
{
	if (OldText == nullptr)
		return;

	// переустанавливаем указатели...
	if (StartText == OldText)
		StartText = OldText->Next;
	if (EndText == OldText)
		EndText = OldText->Prev;

	if (OldText->Next != nullptr)
		OldText->Next->Prev = OldText->Prev;
	else if (OldText->Prev != nullptr)
		OldText->Prev->Next = nullptr;

	if (OldText->Prev != nullptr)
		OldText->Prev->Next = OldText->Next;
	else if (OldText->Next != nullptr)
		OldText->Next->Prev = nullptr;
}




//-----------------------------------------------------------------------------
//	Удаляем все Text в списке
//-----------------------------------------------------------------------------
void ReleaseAllGameLvlText()
{
	// для всех Text
	CGameLvlText *tmp = StartText;
	while (tmp != nullptr) {
		CGameLvlText *tmp2 = tmp->Next;
		// удаляем и очищаем всю память, в релизе стоит DetachShip
		delete tmp;
		tmp = tmp2;
	}

	StartText = nullptr;
	EndText = nullptr;
}











//-----------------------------------------------------------------------------
//	Прорисовываем все Text
//-----------------------------------------------------------------------------
void DrawAllGameLvlText()
{
	// для всех
	CGameLvlText *tmp = StartText;
	while (tmp != nullptr) {
		CGameLvlText *tmp2 = tmp->Next;
		tmp->Draw();
		tmp = tmp2;
	}
}





//-----------------------------------------------------------------------------
//	Апдейтим все Text
//-----------------------------------------------------------------------------
void UpdateAllGameLvlText(float Time)
{
	// для всех
	CGameLvlText *tmp = StartText;
	while (tmp != nullptr) {
		CGameLvlText *tmp2 = tmp->Next;
		if (!tmp->Update(Time)) delete tmp;
		tmp = tmp2;
	}
}



