#pragma once
#include "InventoryObject.h"

class Package : public InventoryObject
{
public:
	Package(Texture* tex, Game* game);
	~Package();
	inline bool useObject() override { return false; }; // no se llamar� nunca -> los paquetes no se usan

private:
	
};

