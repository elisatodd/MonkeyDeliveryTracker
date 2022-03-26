#include "Brightness.h"
#include "../../../Logic/Game.h"
Brightness::Brightness(Game* game):game_(game),alpha_(0){
	tex_ = game->getTexture(BrightnessTexture);
	changeAlhpa(0);
}

Brightness::~Brightness(){
	delete tex_;	
}

void Brightness::draw(){

	tex_->render(rect_);
}

void Brightness::changeAlhpa(Uint8 newAlpha){
	tex_->changeAlpha(newAlpha);
}
