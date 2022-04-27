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
#include "../Items/Banana.h"
#include "../Items/Repel.h"
#include "../Items/Monkeycola.h"
#include "Game.h"

Shop::Shop(Player* player, Game* game)
{
	this->player = player;
	this->game = game;
	
}

Shop::~Shop()
{
	clearElements();
	game = nullptr;
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
		objects.push_back({ new EnergyDrink(game->getTexture(shop_Soda), game,game->getPlayer()), 0, 0, 3, 20 });
		objects.push_back({ new Bike(game->getTexture(shop_Boots01), game,game->getPlayer()), 1, 0, 1, 30});
		objects.push_back({ new Skates(game->getTexture(shop_Boots02), game,game->getPlayer()), 2, 0, 1, 25});
		objects.push_back({ new Flashlight(game->getTexture(shop_Boots02), game,game->getPlayer()), 3, 0, 1, 10});
		//objects.push_back({ new Bike(game->getTexture(bullTexture)), 0, 105, 1, 1000});
		//objects.push_back({ new Bike(game->getTexture(bullTexture)), 1, 105, 1, 1000});
		//objects.push_back({ new Bike(game->getTexture(bullTexture)), 2, 105, 1, 1000});
		break;
	case 2:
		objects.push_back({ new Lantern(game->getTexture(Item_Lantern01), game,game->getPlayer()), 0, 0, 1, 10 });
		objects.push_back({ new Banana(game->getTexture(Item_Banana), game,game->getPlayer()), 1, 0, 1, 20 });
		break;
	case 3:
		objects.push_back({ new Repel(game->getTexture(Item_Spray), game,game->getPlayer()), 0, 0, 3, 40 });
		break;
	default:
		std::cout << "nivel de tienda no valido" << endl;
		break;
	}
}

bool Shop::buyObject(int id, int price)
{
	if (id < objects.size() && objects[id].stock>0 &&!player->inventoryFull(objects[id].inventoryObject) && player->moneyChange(-price)){
		player->addObjectToInventory(objects[id].inventoryObject);		
		objects[id].inventoryObject = nullptr;
		objects[id].stock--;		
		return true;
	}
	else return false; 	
}

bool Shop::inventoryFull(int selected)
{
	return player->inventoryFull(objects[selected].inventoryObject);
}
