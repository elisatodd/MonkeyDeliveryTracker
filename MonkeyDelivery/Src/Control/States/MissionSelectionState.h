#pragma once

#include "State.h"

class MissionSelectionState : public State
{
public:
	MissionSelectionState(Game* game);
	MissionSelectionState(Game* game, vector<pair<string, string>> missionImg);
	~MissionSelectionState();

	void draw() override;
	void update() override;
	void next() override;

	string getStateName() const {
		return "Mission Selection state";
	};

	void registerCommands()override;

	void moveBox(int i);
	string getSelectedMission();

private:
	Texture* background_;

	vector<Texture*> allTextures_;
	vector<Texture*> currentTextures_;

	vector<string> missionData_;

	int currentSelection_; // misi�n que est� seleccionada ahora mismo (en el vector)
	Texture* box_; // seleccionador
	int boxXPos_; // posici�n en la que est� el seleccionador

	int xInc_ = 550; // separacion entre cada papel de mision
};