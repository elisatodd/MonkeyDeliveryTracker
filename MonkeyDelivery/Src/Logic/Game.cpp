#include "Game.h"

Game::Game(string n, int w, int h) : name(n), width(w), height(h), doExit(false)
{    
}

Game::~Game() {
    cout << "[DEBUG] deleting game" << endl;
    delete player;
    delete iE;
    delete textureContainer;
    delete missions_;
}

string Game::getGameName() {
    return name;
}

void Game::start()
{
    player = new Player(this); //Creacion del jugador
    iE = new InteractiveEntity(this);

    missions_ = new MissionManager(this);
    missions_->AddMission(new Mission(missions_, iE, 100, 100, 10));
}

void Game::update()
{
    player->update();
    iE->update();
}

void Game::setUserExit() {
    doExit = true;
}

bool Game::isUserExit() {
    return doExit;
}

void Game::draw()
{
    player->draw();
    iE->draw();
   

}
Point2D<int> Game::getOrigin() {
    return { int(-(player->getX() - player->getWidth())), 0 };
}

int Game::getWindowWidth() {
    return width;
}

int Game::getWindowHeight() {
    return height;
}

void Game::setRenderer(SDL_Renderer* _renderer) {
    renderer = _renderer;
}

void Game::loadTextures() {
    if (renderer == nullptr)
        throw string("Renderer is null");

    textureContainer = new TextureContainer(renderer);
}

Texture* Game::getTexture(TextureName name) {
    return textureContainer->getTexture(name);
}

SDL_Renderer* Game::getRenderer() {
    return renderer;
}

//economy
//modifica el dinero del jugador y devulve bool de confirmaci�n en caso de compra
//actua como enlace al m�todo del jugador
bool Game::changeMoneyPlayer(int money)
{
   return player->moneyChange(money);
}

//al pulsar el bot�n de interactuar(space), se relizan los cambios necesarios
void Game::interactions()
{
    missions_->checkCurrentMission();
}
