#include "Inventory.h"
#include "InventoryObject.h"

Inventory::Inventory()
{
	inventory_.resize(INVENTORY_SIZE);
	for (int i = 0; i < inventory_.size(); i++) {
		inventory_[i] = nullptr;
	}
	missionObject = nullptr;
}

Inventory::~Inventory()
{
	clearInventory();
	delete this;
}

bool Inventory::addObject(InventoryObject* iO)
{
	//Comprobamos que el inventario no est� lleno
	if (inventoryFull())
		return false;
	int i = 0;

	//Se posiciona en el primer espacio de inventario que est� vac�o
	while (inventory_[i] != nullptr)
		i++;

	//Se a�ade el objeto
	inventory_[i] = iO;
}

/// <summary>
/// A�ade el paquete de entrega al slot reservado para ello en el inentario. Si ya tiene uno,
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

void Inventory::useObject(int indexObject)
{
}

void Inventory::removeObject(int indexObject)
{
	delete inventory_[indexObject];
	inventory_[indexObject] = nullptr;
}

void Inventory::removeMisionObject()
{
	delete missionObject;
	missionObject = nullptr;
}


void Inventory::clearInventory()
{
	for (int i = 0; i < inventory_.size(); i++) {
		delete inventory_[i];
		inventory_[i] = nullptr;
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
	
	int i = 0;
	while (i < inventory_.size() && inventory_[i] != nullptr)
		i++;
	return i == inventory_.size();
}


