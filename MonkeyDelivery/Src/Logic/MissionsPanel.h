#pragma once
#include "GameObject.h"
#include "Mission.h"
#include <map>


struct MissionInfo {
	int level;
	bool completed;
	bool isExpress;
	bool isSpecial;
	string imgRoute;
	string target;
	int maxMoney;
	int minMoney;
	int minTime;
};

using sdl_resource_table = std::map<std::string, MissionInfo>;

// Clase que lleva control de las misiones, el nivel actual, y m�s adelante el fin del juego
class MissionsPanel : public GameObject
{
private:
	int currentLevel_; // nivel de misiones en el que se est�
	Mission* currentMission_; // Misi�n activa

	sdl_resource_table missions_; // Missions map (string -> mission)


public:
	MissionsPanel(Game* game);
	~MissionsPanel();
	// Debe activar el estado SeleccionDeMisi�n con ciertos par�metros que mira en el JSON
	void onPlayerInteraction(Player* player) override;
	void update() override;

	// llamado desde el estado de SeleccionDeMisi�n, cuando se sale de �l
	void onMissionSelected(string missionId);

	// el map en el que se guarda la info de las misiones
	inline sdl_resource_table getMissions() {
		return missions_;
	}

	void loadMissions(std::string filename);
};

