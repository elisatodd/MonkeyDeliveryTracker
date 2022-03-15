#pragma once
#include "State.h"

class Shop;
class ShopState : public State
{
	Texture* panelTexture;
	int xPanel=100, yPanel=50, wPanel=500, hPanel=250;
	int xObj=100, yObj=50, wObj=100, hObj=100, xOffset = 100, yOffset = 100;

	Shop* shop_;
	
public:
	ShopState(Game* game);
	~ShopState();

	void update()override;
	void draw()override;
	void next()override;

	string getStateName() const {
		return "Pause state";
	};

	void registerCommands()override;
};


