#include "Lantern.h"
#include "Player.h"
#include "Flashlight.h"

Lantern::Lantern(Texture* tex) : active(false), InventoryObject(tex)
{

}

bool Lantern::useObject() {
	if (!player_->isAsleep()) {
		if (!active) {
			cout << " Hola linternita circular";
			player_->changeLState(true);
			player_->changeFLState(false);
			//Flashlight::setActive(false);
		}
		else {
			cout << "Adios linternita circular";
			player_->changeLState(false);
			player_->setOrientation("off");
		}
		cout << endl;
		active = !active;
		return false; //devolvemos false indicando que el objeto no debe destruirse tras ser usado
	}
}