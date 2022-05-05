#pragma once
#include <array>
#include "Texture.h"
#include <string>

#include <iostream>
#include <vector>

using namespace std;

const string IMAGES_PATH = "Images/";

enum TextureName 
{
	/*
	* Ordenadas por orden de carpetas, y ficheros (alfabetico)
	* Index - Nombre de seccion - Numero de sprites por seccion
	*/

	//1-Background (UI Menu) - 4
		bckg_GameTitle,
		bckg_Image,
		bckg_options,
		bckg_woodWall,
	
	//3-Decorations (House) - 8
		Trohpy_Coco,
		Trohpy_Eagle,
		Trohpy_Fish,
		Trohpy_Fox,
		Trohpy_Frog,
		Trohpy_Hippo,
		Trohpy_Kangaroo,
		Trohpy_Toucan,
	
	//4-Enemies SpritesSheets - 10
		batSS_Death,
		batSS_Default,
		bullSS_Death,
		bullSS_Default,
		catSS_Death,
		catSS_Default,
		plantSS_Death,
		plantSS_Yellow,
		plantSS_Red,
		plantSS_Purple,
		plantSS_Orange,
		scorpionSS_Death,
		scorpionSS_Default,
	
	//5-Items (General) - 18
		Item_Banana,
		Item_Boots01,
		Item_Boots02,
		Item_Boots03,
		Item_Lantern01,
		Item_Package,
		Item_Soda01,
		Item_Soda02,
		Item_pickaxe01,
		Item_pickaxe02,
		Item_Spray,

	//5,2-Items (World)
		lanternCircular,
		lanternDown,
		lanternLeft,
		lanternUp,
		lightGeneric,

	//5,1-Items (Light)
		worldObject_Bed,
		worldObject_blockRock01,
		worldObject_blockRock02,
		worldObject_Chest_Closed,
		worldObject_Chest_Opened,
		worldObject_Gold,
		worldObject_Tutorial,
		worldObject_TutorialComplete,
		worldObject_HappyHippo,
	
	//6-Map - 4
		mapMarker,
		mapOverlay,
		minimapOverlay,
		minimapBorder,
		playerIconTex,
		minimapOverlay02,
	
	//7-Missions - 13
		mission_UI_Helper,
		mission_UI_Panel,
		mission_UI_Selector,
		Mission01,
		Mission02,
		Mission03,
		Mission04,
		Mission05,
		Mission06,
		Mission07,
		Mission08,
		Mission09,
		MissionPanel_Interact,
	
	//8-Monkey SpriteSheets - 3
		monkeySS_Default,
		monkeyTired_Icon,
		monkeyScared_Icon,
	
	//9-NPCS SpriteSheets - 10
		npc_Coco,
		npc_Eagle,
		npc_Fish,
		npc_Fox,
		npc_Frog,
		npc_Hipo,
		npc_Pavo,
		npc_Tucan,
		npc_Rabbit,
		npc_Kangaroo,
		npc_Seller,

	//10-Shop - 7
		shop_Banana,
		shop_Boots01,
		shop_Boots02,
		shop_Boots03,
		shop_Soda,
		shop_UI_PanelShop,
		shop_UI_Selector,
		ShopPanel_Interact,
		shop_UI_Controls,
		shop_Items,
	
	//11-UI Overlay (InGame) - 7
		UI_dialogueBox,
		UI_Coin,
		UI_energyLevel,
		UI_fearLevel,
		UI_InventoryBar,
		UI_InventoryBarOverlay,
		UI_InventorySelector,
		UI_playerHUD,
		UI_playerHUD_BackFill,
		UI_timer,

   //12-UI Overlay (InGame Buffs) - 3
		UI_energyBuff,
		UI_fearBuff,
		UI_speedBuff,
		UI_speedDebuff,

   //13-UI Overlay (Menu) - 21
		UI_Black,
		UI_Brightness,
		button_Back,
		button_Continue,
		button_Main_Credits,
		button_Main_ExitButton,
		button_Main_Options,
		button_Main_StartButton,
		button_Pause,
		button_Selector,
		UI_Fade,
		UI_label,
		UI_Checker00,
		UI_Checker01,
		UI_Checker02,
		UI_Checker03,
		UI_MissionsControls,
		UI_Controls,

		missingTex,
		transitionTex,
		coco_Icon,
		eagle_Icon,
		fish_Icon,
		frog_Icon,
		hipo_Icon,
		pavo_Icon,
		rabit_Icon,
		tucan_Icon,
		fox_Icon
};

const int NUM_TEXTURES = 135;

typedef struct {
	string filename;
	int numRows; int numCols;
} TextureAttributes;


const TextureAttributes TEXTURE_ATTRIBUTES[NUM_TEXTURES] =
{ 
	//1-Background (UI Menu)
	{"background/bckg_GameTitle.png",1,1},
	{"background/bckg_Image.png",1,1},
	{"background/bckg_WoodPanneling.png",1,1},
	{"background/bckg_woodWall.webp",1,1},
	
	//3-Decorations (House)
	{"decor/Trohpy_Coco.png",1,1},
	{"decor/Trohpy_Eagle.png",1,1},
	{"decor/Trohpy_Fish.png",1,1},
	{"decor/Trohpy_Fox.png",1,1},
	{"decor/Trohpy_Frog.png",1,1},
	{"decor/Trohpy_Hippo.png",1,1},
	{"decor/Trohpy_Kangaroo.png",1,1},
	{"decor/Trohpy_Toucan.png",1,1},

	//4-Enemies SpritesSheets
	{"enemies/batSS_Death.png",1,1},
	{"enemies/batSS_Default.png",1,1},
	{"enemies/bullSS_Death.png",1,1},
	{"enemies/bullSS_Default.png",1,1},
	{"enemies/catSS_Death.png",1,1},
	{"enemies/catSS_Default.png",1,1},
	{"enemies/plantSS_Death.png",1,1},
	{"enemies/plantSS_Yellow.png",1,1},
	{"enemies/plantSS_Red.png",1,1},
	{"enemies/plantSS_Purple.png",1,1},
	{"enemies/plantSS_Orange.png",1,1},
	{"enemies/scorpionSS_Death.png",1,1},
	{"enemies/scorpionSS_Default.png",1,1},

	//5-Items
	{"items/Item_Banana.png",1,1},
	{"items/Item_Boots01.png",1,1},
	{"items/Item_Boots02.png",1,1},
	{"items/Item_Boots03.png",1,1},
	{"items/Item_Lantern01.png",1,1},
	{"items/Item_Package.png",1,1},
	{"items/Item_Soda01.png",1,1},
	{"items/Item_Soda02.png",1,1},
	{"items/Item_pickaxe01.png",1,1},
	{"items/Item_pickaxe02.png",1,1},
	{"items/Item_Spray.png",1,1},
	
	//Items Light
	{"items/light/lanternCircular.png",1,1},
	{"items/light/lanternDown.png",1,1},
	{"items/light/lanternLeft.png",1,1},
	{"items/light/lanternUp.png",1,1},
	{"items/light/lightGeneric.png",1,1},

	//Items World
	{"items/world/worldObject_Bed.png",1,1},
	{"items/world/worldObject_blockRock01.png",1,1},
	{"items/world/worldObject_blockRock02.png",1,1},
	{"items/world/worldObject_Chest_Closed.png",1,1},
	{"items/world/worldObject_Chest_Opened.png",1,1},
	{"items/world/worldObject_Gold.png",1,1},
	{"items/world/worldObject_Tutorial.png",1,1},
	{"items/world/worldObject_TutorialDone.png",1,1},
	{"items/world/Item_HappyHippo.png",1,1},

	//6-Map
	{"map/mapMarker.png",1,1},
	{"map/mapOverlay.png",1,1},
	{"map/minimapOverlay.png",1,1},
	{"map/minimapBorder.png",1,1},
	{"map/playerIcon.png",1,1},
	{"map/minimapOverlay02.png",1,1},

	//7-Missions
	{"missions/mission01_UI_Helper.png",1,1},
	{"missions/mission_UI_Panel.png",1,1},
	{"missions/mission_UI_Selector.png",1,1},
	{"missions/Mission01.png",1,1},
	{"missions/Mission02.png",1,1},
	{"missions/Mission03.png",1,1},
	{"missions/Mission04.png",1,1},
	{"missions/Mission05.png",1,1},
	{"missions/Mission06.png",1,1},
	{"missions/Mission07.png",1,1},
	{"missions/Mission08.png",1,1},
	{"missions/Mission09.png",1,1},
	{"missions/MissionPanel_Interact.png",1,1},

	//8-Monkey SpriteSheets
	{"monkeyAnims/monkeySS_Default.png",1,1},
	{"ui/tiredIcon.png",1,1},
	{"ui/scaredIcon.png",1,1},

	//9-NPCS SpriteSheets
	{"npcs/NPC_Coco.png",1,1},
	{"npcs/NPC_Eagle.png",1,1},
	{"npcs/NPC_Fish.png",1,1},
	{"npcs/NPC_Fox.png",1,1},
	{"npcs/NPC_Frog.png",1,1},
	{"npcs/NPC_Hipo.png",1,1},
	{"npcs/NPC_Pavo.png",1,1},
	{"NPCs/NPC_Tucan.png",1,1},
	{"npcs/NPC_Rabbit.png",1,1},
	{"npcs/NPC_Kangaroo.png",1,1},
	{"npcs/NPC_Seller.png",1,1 },

	//10-Shop
	{"shop/shop_Banana.png",1,1},
	{"shop/shop_Boots01.png",1,1},
	{"shop/shop_Boots02.png",1,1},
	{"shop/shop_Boots03.png",1,1},
	{"shop/shop_Soda.png",1,1},
	{"shop/shop_UI_PanelShop.png",1,1},
	{"shop/shop_UI_Selector.png",1,1},
	{"shop/ShopPanel_Interact.png",1,1},
	{"shop/shopControls.png",1,1},
	{"shop/items.png",1,1 },

	//UI Overlay (InGame)
	{"ui/InGame/dialoguebox.png",1,1},
	{"ui/InGame/UI_Coin.png",1,1},
	{"ui/InGame/UI_energyLevel.png",1,1},
	{"ui/InGame/UI_fearLevel.png",1,1},
	{"ui/InGame/UI_InventoryBar.png",1,1},
	{"ui/InGame/UI_InventoryBarOverlay.png",1,1},
	{"ui/InGame/UI_InventorySelector.png",1,1},
	{"ui/InGame/UI_playerHUD.png",1,1},
	{"ui/InGame/UI_playerHUD_BackFill.png",1,1},
	{"ui/InGame/timer.png",1,1},

    //UI Overlay (InGame Buffs)
	{"ui/InGame/UI_energyBuff.png",1,1 },
	{"ui/InGame/UI_fearBuff.png",1,1 },
	{"ui/InGame/UI_speedBuff.png",1,1 },
	{"ui/InGame/UI_speedDebuff.png",1,1 },
		
	//UI Overlay (Menu)
	{"ui/Menu/black.png",1,1},
	{"ui/Menu/Brightness.png",1,1},
	{"ui/Menu/button_Back.png",1,1 },
	{"ui/Menu/button_Continue.png",1,1 },
	{"ui/Menu/button_Main_Credits.png",1,1 },
	{"ui/Menu/button_Main_ExitButton.png",1,1 },
	{"ui/Menu/button_Main_Options.png",1,1 },
	{"ui/Menu/button_Main_StartButton.png",1,1 },
	{"ui/Menu/button_Pause.png",1,1 },
	{"ui/Menu/button_Selector.png",1,1 },
	{"ui/Menu/fade.png",1,1},
	{"ui/Menu/label.png",1,1},
	{"ui/Menu/UI_Checker00.png",1,1},
	{"ui/Menu/UI_Checker01.png",1,1},
	{"ui/Menu/UI_Checker02.png",1,1},
	{"ui/Menu/UI_Checker03.png",1,1},
	{"ui/controlsmissions.png",1,1},
	{"tutorial/Tutorial.png",1,1},

	{"missingTex.png",1,1},
	{"transition.png",1,1},

	{ "ui/cocoIcon.png",1,1 },
	{ "ui/eagleIcon.png",1,1 },
	{ "ui/fishIcon.png",1,1 },
	{ "ui/frogIcon.png",1,1 },
	{ "ui/hipoIcon.png",1,1 },
	{ "ui/pavoIcon.png",1,1 },
	{ "ui/rabitIcon.png",1,1 },
	{ "ui/tucanIcon.png",1,1 },
	{ "ui/foxIcon.png",1,1 }
};

class TextureContainer {

	array<Texture*, NUM_TEXTURES> textures;
	//vector<Texture*> textures;

public:
	TextureContainer(SDL_Renderer* renderer) { // SIN ARRAYS -> con vector
		//textures.resize(NUM_TEXTURES);

		std::cout << "Loading textures\n";
		for (int i = 0; i < NUM_TEXTURES; i++) {
			const TextureAttributes& attributes = TEXTURE_ATTRIBUTES[i];
			textures[i] = new Texture(renderer, IMAGES_PATH + attributes.filename, attributes.numRows, attributes.numCols);
		}
		std::cout << "Texture load finished\n";

	}

	~TextureContainer() {
		for (int i = 0; i < NUM_TEXTURES; i++) {

			if (textures[i] != nullptr) {
				textures[i]->free();
			}
			delete textures[i];
		}
	}

	Texture* getTexture(TextureName name) const 
	{
		return textures[name];
	};
};