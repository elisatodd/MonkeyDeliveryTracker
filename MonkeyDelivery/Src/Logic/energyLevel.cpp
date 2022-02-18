#include "energyLevel.h"

energyLevel::energyLevel(Game* game) :GameObject(game) {
	this->game = game;

	place_ = 50;
	energy_ = 200;
	maxEnergy_ = 200;
	setTexture(energyLevelTexture);
	setPosition(place_, 10);
	setDimension(200, 20);
}

void energyLevel::drain(float energyDrained)
{
	energy_ -= energyDrained;
	if (energy_ > 0) {
		setDimension(energy_, 20);
		setPosition(50 - (energyDrained/2), 10);
	}
	else {
		// avisa al player de que est� sin energ�a
		cout << "ME DUERMO" << endl;
	}
}


void energyLevel::draw()
{
	drawTexture(texture);
}
