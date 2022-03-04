#include "Inventory.h"
#include "InventoryObject.h"
#include <iostream>

Inventory::Inventory(Player* player) : player_(player)
{
	missionObject = nullptr;
}

Inventory::~Inventory()
{
	clearInventory();
}

bool Inventory::addObject(InventoryObject* iO)
{
	//Comprobamos que el inventario no est� lleno
	if (inventoryFull())
		return false;
	
	//Se a�ade el objeto y se le asigna el player
	inventory_.push_back(iO);
	iO->attachPlayer(player_);

	return true;
}

/// <summary>
/// A�ade el paquete de entrega al slot reservado para ello en el inventario. Si ya tiene uno,
/// significa que a�n no ha terminado la misi�n por lo que el m�todo te dice si el jugador ha entregado el 
/// paquete o no. �til para no solapar misiones
/// </summary>
/// <param name="io">Paquete de entrega a a�adir en el inventario</param>
/// <returns></returns>
bool Inventory::addMisionObject(InventoryObject* io)
{
	if (missionObject == nullptr)
	{
		missionObject = io;
		return true;
	}
	else
		return false;
}

bool Inventory::useObject(int indexObject)
{
	//Devuelve false si el objeto no pudo ser utilizado
	if (indexObject >= inventory_.size())
		return false;
	//Si el objeto es de un solo uso (useObject() devuelve true)
	//Lo eliminamos
	//Si no hab�a que eliminarlo, no se hace nada
	if (inventory_[indexObject]->useObject()) //useObject() devuelve un booleano!!
	{
		removeObject(indexObject);
	}
	return true;
}

void Inventory::removeObject(int indexObject)
{
	delete inventory_[indexObject];
	inventory_.erase(inventory_.begin() + indexObject);
}

void Inventory::removeMisionObject()
{
	delete missionObject;
	missionObject = nullptr;
}


void Inventory::clearInventory()
{
	// iteradores
	for (auto gO : inventory_) {
		delete gO;
	}

	if (missionObject != nullptr) {
		delete missionObject;
		missionObject = nullptr;
	}
}

/// <summary>
/// Recorre el inventario en b�squeda de objetos que sean nullptr. Si no encuentra ninguno
/// devuelve true
/// </summary>
/// <returns>True si el inventario est� lleno</returns>
bool Inventory::inventoryFull() {
	
	//int i = 0;
	//// error grave, saca elementos del vector
	//while (i < inventory_.size() && inventory_[i] != nullptr)
	//	i++;
	//return i == inventory_.size();
	// quer�is esto:
	return inventory_.size() == INVENTORY_SIZE;
}

void Inventory::draw() {

}




