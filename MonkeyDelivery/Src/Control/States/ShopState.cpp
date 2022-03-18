#include "ShopState.h"
#include "../PauseCommand.h"
#include "../CommandExit.h"
#include "../ShopCommand.h"
#include "../../Logic/Shop.h"

ShopState::ShopState(Game* game) : State(game){
	registerCommands();

	panelTexture=game->getTexture(shopPanel);
	font_ = new Font("../Images/TheMoon.ttf", 40);

	shop_ = game->getShop();
	shop_->actualice();
}

ShopState::~ShopState()
{
	//delete panelTexture;
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

	int i = 0;

	//renderizado de los objetos

	
	//pruebas
	while (i < 4 && i < shop_->getSize())
	{
		shop_->objects[i]->getTexture()->render({ xOffset + xObj * i, yOffset, wObj, hObj });
		i++;
	}
	
	while (i < shop_->getSize())
	{
		shop_->objects[i]->getTexture()->render({ xOffset + xObj * (i-4), yOffset + yObj, wObj, hObj });
		i++;
	}

	//renderizado del objeto seleccionado

	if(selected_ < 4)
		rectPanel = { xOffset + xObj * selected_ - 15, yOffset + 3, (int)(wObj*1.3), (int)(hObj * 0.9) };
	else
		rectPanel = { xOffset + xObj * (selected_-4) - 15, yOffset + yObj + 3, (int)(wObj * 1.3), (int)(hObj * 0.9) };
	
	game->getTexture(seleccionShopPanel)->render(rectPanel);

	//renderizado del texto
	font_->render(game->getRenderer(),"1000", xText, yText, BLACK);

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

void ShopState::moveSelected(int to)
{
	//pruebas, sustituir 6 shop_->getSize()-1
	if (selected_ == shop_->getSize() - 1 && to > 0)
		selected_ = 0;
	else if (selected_ == 0 && to < 0)
		selected_ = shop_->getSize() - 1;
	else
		selected_ += to;
}

void ShopState::buySelected()
{
	//falta �adir el precio ya sea en shop o shopstate
	shop_->buyObject(selected_, 100);
}
