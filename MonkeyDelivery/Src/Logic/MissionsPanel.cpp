#include "MissionsPanel.h"
#include "Game.h"

#include "../Control/States/MissionSelectionState.h"

MissionsPanel::MissionsPanel(Game* game) : GameObject(game)
{
	setTexture(missionPanelTexture);
}

MissionsPanel::~MissionsPanel()
{
}

void MissionsPanel::onPlayerInteraction(Player* player)
{
	if (game->getSavedState() == nullptr) {
		// show pannel
		game->saveState(game->getState());
		game->setState(new MissionSelectionState(game));
	}
}

void MissionsPanel::onMissionSelected()
{
	// Esto se lee del JSON seg�n un par�metro que se va a pasar a este m�todo
	currentMission_ = new Mission(game->getMissionManager(), game->getiE(), 100, 100, 10, 1000, "Misi�n 1"); 

	// hide pannel
	State* tmp = game->getState();
	State* saved = game->getSavedState();
	saved->resetInitTime();
	saved->registerCommands();
	game->setState(saved);
	game->clearSavedState();
	delete tmp;

	// spawn Vecino

}
