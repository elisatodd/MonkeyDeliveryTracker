#pragma once
#include "InventoryObject.h"

class Player;

// 15% m�s  velocidad de movimiento durante 30 segundos
// Aumenta la energ�a un 20% 
class EnergyDrink : public InventoryObject
{
public:

	EnergyDrink() { isConsumable_ = true; };
	bool useObject() override;
};

