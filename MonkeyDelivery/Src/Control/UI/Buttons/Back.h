#pragma once

#include "../../Button.h"
class Game;

class Back : public Button {

public:
	Back(int x, int y,int w , int h,Game* game);
	~Back() {};
	void onCursorCollision() override;
};
