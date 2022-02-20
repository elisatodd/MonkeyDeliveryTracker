//
// Created by espeto on 20/8/45.
//

#pragma once
#include <iostream>
#include <string>
#include <vector>

#include"../Control/States/StateMachine.h"
#include "../View/Texture.h"
#include "../View/TextureContainer.h"

#include "../View/Font.h"

#include "Player.h"
#include "InteractiveEntity.h"

#include "Mission.h"
#include "MissionManager.h"

using namespace std;

class Game : public StateMachine {

private:
    string name;
    bool doExit;
    int width, height;

    TextureContainer* textureContainer;
    SDL_Renderer* renderer = nullptr;
    Player* player = nullptr;
    InteractiveEntity* iE = nullptr;
    MissionManager* missions_ = nullptr;
    vector<GameObject*> gameObjects_;
    
    Font* font_;

public:
  

    Game(string name, int width, int height);
    ~Game();

    string getGameName();

    void add(GameObject* gameObject);

    void start();
    void update();

    void setUserExit();
    bool isUserExit();
    void draw();
    Point2D<int> getOrigin();
    int getWindowWidth();
    int getWindowHeight();

    //Player movement
    inline void move(pair<double, double> speed) { player->move(speed); };
    inline void setIsRunning(bool run) { player->setIsRunning(run); };

    // rendering
    void setRenderer(SDL_Renderer* renderer);
    void loadTextures();
    Texture* getTexture(TextureName name);
    SDL_Renderer* getRenderer();
    inline Player* getPlayer() { return player; }
    void renderText(string text, int x, int y, SDL_Color color = { 0,0,0 }); // Escribir una sola l�nea
    void renderText(vector<string> text, int x, int y, int incX, int incY, SDL_Color color = { 0,0,0 }); // Escribir varias l�neas

    // missions
    bool changeMoneyPlayer(int money);
    void interactions();
    vector<GameObject*>getCollisions(SDL_Rect rect);
};



