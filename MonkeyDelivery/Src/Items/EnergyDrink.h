	#pragma once
#include "../Logic/InventoryObject.h"

class Player;

// 15% m�s  velocidad de movimiento durante 30 segundos
// Aumenta la energ�a un 20% 
class EnergyDrink : public InventoryObject
{
	
public:

	EnergyDrink(Texture* tex, Game* game,Player* player);
	bool useObject() override;
};