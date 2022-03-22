#pragma once

#include "../Logic/GameObject.h"
#include "../Control/ViewController.h"
class Game;

class Button : public GameObject {
protected:
	int x_;
	int y_;

public:
	Button(Game* game, int wight, int height, int x, int y);
	Button(Game* game, int x, int y);
	~Button() { };
	bool onClick();
	virtual void  update() override;
    virtual void onCursorCollision()=0;
	//bool parse(SDL_Event& event);

};
