#include "InventoryObject.h"
#include "../Player/Player.h"
#include "Game.h"
InventoryObject::InventoryObject(Texture* tex, Game* game,Player* player) : myTexture_(tex), game_(game),player_(player){
	 typeObject = UNSIGNED; 
}

InventoryObject::~InventoryObject(){	
	myTexture_ = nullptr;
}

/// <summary>
/// M�todo virtual que realiza el uso del objeto y devuelve si el objeto es deshechable(true) o reutilizable
/// </summary>
/// <returns>True si el objeto debe ser eliminado del inventario o false si se debe mantener</returns>
bool InventoryObject::useObject()
{
	return false;
}

/// <summary>
/// A�ade el Player al InventoryObject para poder utilizar sus m�todos cuando se llame a useObject()
/// Este m�todo debe ser llamado cuando se a�ada el InventoryObject al innventario
/// </summary>
/// <param name="player">Jugador del Game</param>
void InventoryObject::attachPlayer(Player* player)
{
	player_ = player;
}

void InventoryObject::setMyTexture(Texture* tex)
{
	if (myTexture_ != nullptr)
		myTexture_ = tex;
}

void InventoryObject::setCorrectTexture(){
	setMyTexture(game_->getTexture(missingTex));
}
