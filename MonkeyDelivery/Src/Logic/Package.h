#pragma once
#include "InventoryObject.h"

class Package : public InventoryObject
{
public:
	/*Package();
	~Package();*/
	inline bool useObject() override { return false; }; // no se llamar� nunca -> los paquetes no se usan

private:

};

