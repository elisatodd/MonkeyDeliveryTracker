#include "GameObject.h"
class Game;

class energyLevel: public GameObject {
private:
	
	float place_;
	float energy_;
	float maxEnergy_;


public:
	energyLevel(Game* game);
	~energyLevel() { };

	void update() override {};
	void drain(float energyDrained);
	void draw() override;

};

