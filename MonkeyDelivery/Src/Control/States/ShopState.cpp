#include "ShopState.h"
#include "../PauseCommand.h"
#include "../CommandExit.h"
#include "../ShopCommand.h"
#include "../../Logic/Shop.h"
#include <string>
ShopState::ShopState(Game* game) : State(game){
	registerCommands();

	panelTexture=game->getTexture(shopPanel);
	font_ = new Font("../Images/TheMoon.ttf", 40);

	shop_ = game->getShop();
	shop_->actualice();
}

ShopState::~ShopState()
{
	shop_->clearElements();
	panelTexture = nullptr;
	shop_ = nullptr;
}


void ShopState::update()
{
}

void ShopState::draw()
{
	//renderizado del fondo
	
	SDL_Rect rectPanel = { 0,0,game->getWindowWidth(),game->getWindowHeight() };
	panelTexture->render(rectPanel);
	std::cout << selected_ << std::endl;
	int i = 0;

	//renderizado de los objetos

	
	//pruebas
	//while (i < 4 && i < shop_->getSize())
	//{
	//	//shop_->objects[i]->getTexture()->render({ xOffset + xObj * i, yOffset, wObj, hObj });
	//	shop_->objects2[i].inventoryObject->getTexture()->render({ xOffset + xObj * shop_->objects2[i].positionRectX, yOffset, wObj, hObj });
	//	i++;
	//}	
	while (i < shop_->getSize())
	{
		//shop_->objects[i]->getTexture()->render({ xOffset + xObj * (i-4), yOffset + yObj, wObj, hObj });
		/*if(shop_->objects[i].stock>0)
		shop_->objects[i].inventoryObject->getTexture()->render(
			{ xOffset + xObj * shop_->objects[i].positionRectX, yOffset + shop_->objects[i].positionRectY, wObj, hObj });
		i++;*/
		if (shop_->objects[i].stock > 0)
			shop_->objects[i].inventoryObject->getTexture()->render(
				{ xOffset + xObj * shop_->objects[i].positionRectX, yOffset + (shop_->objects[i].positionRectY * 3), wObj, hObj });
		i++;
	}

	//renderizado del objeto seleccionado

	if(selected_ < 4)
		rectPanel = { xOffset + xObj * selected_ - 15, yOffset + 3, (int)(wObj*1.3), (int)(hObj * 0.9) };
	else
		rectPanel = { xOffset + xObj * (selected_-4) - 15, yOffset + yObj + 3, (int)(wObj * 1.3), (int)(hObj * 0.9) };
	
	game->getTexture(seleccionShopPanel)->render(rectPanel);

	//renderizado del texto
	if (shop_->objects.size()>selected_&&shop_->objects[selected_].stock > 0) {
		font_->render(game->getRenderer(), std::to_string(shop_->objects[selected_].price), xText, yText, BLACK);
	}
	else {
		font_->render(game->getRenderer(), " ", xText, yText, BLACK);
	}

	if (closeFailed_)
	{
		font_->render(game->getRenderer(), textError_, xText + 150, yText - 5, BLACK);
		if (SDL_GetTicks() > lastClicked_ + FAIL_TIMESHOWED) 
			closeFailed_ = false;
	}

}

void ShopState::next()
{
}

void ShopState::registerCommands()
{
	commandFactory->add(new PauseCommand());
	commandFactory->add(new CommandExit());
	commandFactory->add(new ShopCommand(this));
}

void ShopState::moveSelectedX(int to)
{
	//pruebas, sustituir 6 shop_->getSize()-1
	//if (selected_ == shop_->getSize() - 1 && to > 0)
	//	selected_ = 0;
	//else if (selected_ == 0 && to < 0)
	//	selected_ = shop_->getSize() - 1;
	//else
	//	selected_ += to;
	if (selected_ + to < MAX_SELECTED && selected_ + to >= 0)
		selected_ += to;	
}

void ShopState::moveSelectedY(int to)
{
	if (selected_+MAX_SELECTED/2 * to < MAX_SELECTED  && selected_+ MAX_SELECTED / 2 * to >= 0)
		selected_=selected_+ MAX_SELECTED / 2 *to ;
}

void ShopState::buySelected()
{
	
	if (!shop_->buyObject(selected_, shop_->objects[selected_].price))
	{
		lastClicked_ = SDL_GetTicks();

		if (shop_->inventoryFull())
			textError_ = "Inventory full";
		else 
			textError_ = "Not enough money";

		closeFailed_ = true;
	}
	else
		closeFailed_ = false;

}
