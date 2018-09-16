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

#include "fps_counter.h"
#include "../config/config.h"

// NOTE switch to nested namespace definition (namespace A::B::C { ... }) (since C++17)
namespace viewizard {
namespace astromenace {

/*
 * Switch fps counter show/hide status.
 */
void cFPS::Switch()
{
	ChangeGameConfig().ShowFPS = !GameConfig().ShowFPS;

	if (!GameConfig().ShowFPS)
		return;

	LastTick = SDL_GetTicks();
	CurrentFPS = 0.0f;
	CurrentFrame = 0;
}

/*
 * Check keyboard.
 */
void cFPS::CheckKeyboard()
{
	if (!vw_GetKeyStatus(SDLK_F2))
		return;

	vw_SetKeyStatus(SDLK_F2, false);
	Switch();

}

/*
 * Draw fps counter.
 * Note, caller should setup 2D mode rendering first.
 */
void cFPS::Draw()
{
	if (!GameConfig().ShowFPS)
		return;

	if (GameConfig().VSync)
		vw_DrawText(6, 5, 0, 0, 1.0f, TextColor, 0.99f,
			    "%s %.1f (VSync - %s)", vw_GetText("fps"), CurrentFPS, vw_GetText("On"));
	else
		vw_DrawText(6, 5, 0, 0, 1.0f, TextColor, 0.99f,
			    "%s %.1f", vw_GetText("fps"), CurrentFPS);
}

/*
 * Update fps counter.
 */
void cFPS::Update()
{
	CheckKeyboard();
	if (!GameConfig().ShowFPS)
		return;

	uint32_t CurrentTick = SDL_GetTicks();
	if (LastTick > CurrentTick) { // game was restarted, or SDL was re-inited
			LastTick = CurrentTick;
			CurrentFPS = 0.0f;
			CurrentFrame = 0;
	} else {
		uint32_t TicksDelta = CurrentTick - LastTick;
		constexpr uint32_t TicksInSecond{1000};

		if (TicksDelta >= TicksInSecond) {
			CurrentFPS = static_cast<float>(CurrentFrame * TicksInSecond) / TicksDelta;
			CurrentFrame = 0;
			LastTick = CurrentTick;
		}
	}

	CurrentFrame++;
}

} // astromenace namespace
} // viewizard namespace