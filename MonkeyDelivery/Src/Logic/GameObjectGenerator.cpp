#include "GameObjectGenerator.h"

GameObjectGenerator GameObjectGenerator::gOGenerator;

void GameObjectGenerator::createChest()
{
	posChest.push_back({ 400, 150 });		posChest.push_back({ 6350, 250 });
	posChest.push_back({ 4300, 1150 });		posChest.push_back({ 2060, 2500 });
	posChest.push_back({ 2320, 3320 });		posChest.push_back({ 6700, 4220 });
	posChest.push_back({ 6720, 5250 });		posChest.push_back({ 3530, 5900 });
}

void GameObjectGenerator::creteBulls()
{
	posBulls.push_back({ 6800, 1950 }); posBulls.push_back({ 6200, 5450 });
	posBulls.push_back({ 5300, 4700 }); posBulls.push_back({ 550, 4600 });
}

void GameObjectGenerator::createCats()
{
	posCats.push_back({ 4250, 5100 });		posCats.push_back({ 1800, 5350 });
	posCats.push_back({ 3100, 6000 });		posCats.push_back({ 1850, 2100 });
	posCats.push_back({ 5550, 1850 });		posCats.push_back({ 4800, 2150 });
	posCats.push_back({ 1500, 2600 });		posCats.push_back({ 1500, 2900 });
	posCats.push_back({ 2320, 4100 });		posCats.push_back({ 4700, 1200 });
	posCats.push_back({ 5800, 2800 });		posCats.push_back({ 6050, 3200 });
	posCats.push_back({ 4900, 3300 });
}

void GameObjectGenerator::createPlants()
{
	posPlants.push_back({ 300, 2200 });			posPlants.push_back({ 2400, 1900 });
	posPlants.push_back({ 3400, 2800 });		posPlants.push_back({ 800, 5700 });
	posPlants.push_back({ 1200, 440 });			posPlants.push_back({ 1600, 4800 });
	posPlants.push_back({ 7250, 2950 });		posPlants.push_back({ 7100, 800 });
	posPlants.push_back({ 6100, 1000 });		posPlants.push_back({ 4150, 750 });
	posPlants.push_back({ 4850, 5600 });		posPlants.push_back({ 6400, 5600 });
	posPlants.push_back({ 6000, 4650 });		posPlants.push_back({ 5450, 3700 });
}

void GameObjectGenerator::createBats()
{
	posBats.push_back({ 1200, 300 });		posBats.push_back({ 5000, 500 });
	posBats.push_back({ 6800, 2800 });		posBats.push_back({ 3700, 3700 });
	posBats.push_back({ 2900, 4200 });		posBats.push_back({ 3900, 4300 });
	posBats.push_back({ 2700, 5500 });		posBats.push_back({ 400, 5600 });
	posBats.push_back({ 400, 1600 });		posBats.push_back({ 450, 3250 });
}

void GameObjectGenerator::createScorpions()
{
	posScorpions.push_back({ 6000, 1900 });		posScorpions.push_back({ 5000, 4000 });
	posScorpions.push_back({ 5100, 5600 });		posScorpions.push_back({ 2300, 4700 });
	posScorpions.push_back({ 1750, 2800 });		posScorpions.push_back({ 300, 2600 });
	posScorpions.push_back({ 3200, 2300 });		posScorpions.push_back({ 5100, 1000 });
}
