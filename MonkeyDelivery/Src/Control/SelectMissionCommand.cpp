#include "SelectMissionCommand.h"
#include "./States/PlayingState.h"
#include "../Logic/Mission.h"

bool SelectMissionCommand::parse(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;
		if (key == SDLK_e)
			return true;
	}
	return false;
}

void SelectMissionCommand::execute()
{
	// Comunicar cu�l es la misi�n seleccionada
	game->setActiveMission(new Mission(game->getMissionManager(), game->getiE(), 100, 100, 10, 1000, "Primera Misi�n"));
	
	//game->setState(new PlayingState(game));
	//delete this;
}
