#include "Shop.h"
#include <iostream>
#include "InventoryObject.h"
#include "Inventory.h"
#include "../Player/Player.h"
#include "../Items/Bike.h"
#include "../Items/EnergyDrink.h"
#include "../Items/Skates.h"
#include "../Items/Flashlight.h"
#include "../Items/Lantern.h"
#include "Game.h"

Shop::Shop(Player* player, Game* game)
{
	this->player = player;
	this->game = game;
	
}

Shop::~Shop()
{
	clearElements();
	player = nullptr;
}

void Shop::actualice()
{
	clearElements();
	addElements(1);
}

void Shop::clearElements()
{
	if (objects.size() > 0)
	{
		for (auto e : objects)
		{
			if (e.inventoryObject != nullptr)
				delete e.inventoryObject;
			//objects2.erase(objects2.begin());
		}
		objects.clear();
	}
	
}

void Shop::addElements(int level)
{
	switch (level)
	{
	case 1:
		objects.push_back({ new EnergyDrink(game->getTexture(shop_Soda), game), 0, 0, 1, 20 });
		objects.push_back({ new Bike(game->getTexture(shop_Boots01), game), 1, 0, 1, 30});
		objects.push_back({ new Skates(game->getTexture(shop_Boots02), game), 2, 0, 1, 25});
		objects.push_back({ new Flashlight(game->getTexture(shop_Boots02), game), 3, 0, 1, 10});
		//objects.push_back({ new Bike(game->getTexture(bullTexture)), 0, 105, 1, 1000});
		//objects.push_back({ new Bike(game->getTexture(bullTexture)), 1, 105, 1, 1000});
		//objects.push_back({ new Bike(game->getTexture(bullTexture)), 2, 105, 1, 1000});
		break;
	case 2:
		objects.push_back({ new Lantern(game->getTexture(Item_Lantern01), game), 3, 0, 1, 10 });
		break;
	case 3:
		break;
	default:
		std::cout << "nivel de tienda no valido" << endl;
		break;
	}
}

bool Shop::buyObject(int id, int price)
{
	if (id < objects.size() && objects[id].stock>0 &&!player->inventoryFull() && player->moneyChange(-price)){	
		player->addObjectToInventory(objects[id].inventoryObject);		
		objects[id].inventoryObject = nullptr;
		objects[id].stock--;		
		return true;
	}
	else return false; 	
}

bool Shop::inventoryFull()
{
	return player->inventoryFull();
}
