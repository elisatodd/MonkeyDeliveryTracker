#include "ViewController.h"
#include "../Logic/Game.h"

#include "States/MenuState.h"

#include "CommandMove.h"
#include "CommandRun.h"
#include "CommandInteract.h"


ViewController::ViewController(Game* _game) {
    game = _game;
    std::cout << "[DEBUG] frame duration: " << frameDuration() << " ms" << endl;
    initSDL();
    IMG_Init(IMG_INIT_PNG);
    
    game->setRenderer(renderer);
    game->loadTextures();
    commandFactory = new CommandFactory(game);
    commandFactory->add(new CommandMove());
    commandFactory->add(new CommandExit());
    commandFactory->add(new CommandInteract());
    commandFactory->add(new CommandRun());
    game->setState(new MenuState(game));
}

void ViewController::run() {
    uint32_t startTime = 0;
    uint32_t frameTime;

    game->start(); //Inicio del juego
    //!game->getState()->doQuit()
    while (!game->isUserExit()) {

        frameTime = SDL_GetTicks() - startTime;
        handleEvents();

        if (frameTime >= frameDuration()) {
            clearBackground();
            game->update();
            game->getState()->update();
            game->getState()->draw();
           // game->draw();
            SDL_RenderPresent(renderer);
            startTime = SDL_GetTicks();
        }
        else {
            SDL_Delay(frameDuration() - frameTime);
        }
    }
}

void ViewController::clearBackground() {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}


vector<SDL_Event>& ViewController::GetFrameEvents()
{
    static vector<SDL_Event> frame_events;
    return frame_events;
}

void ViewController::handleEvents() {
    SDL_Event event;
    //Registra los eventos
    while (SDL_PollEvent(&event) != 0)
    {
        GetFrameEvents().push_back(event);        
    }
    for (auto e:GetFrameEvents()) //Ejecutamos los executes de los comandos de los eventos registrados
    {
        vector<Command*> commands = commandFactory->getCommand(e);
        for (auto i:commands)
        {
            if (i != nullptr) {
                  i->execute();
            }
        }
    }
    
    GetFrameEvents().clear(); //Vaciar el vector de eventos y que no se acumulen
}

uint32_t ViewController::frameDuration() {
    return 1000 / FRAME_RATE;
}

void ViewController::initSDL() {
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(game->getGameName().c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        game->getWindowWidth(),
        game->getWindowHeight(),
        SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (window == nullptr || renderer == nullptr)
        throw string("Error creating SDL window or renderer");

    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, &screenSurface->clip_rect, 0xFF);
    SDL_UpdateWindowSurface(window);
}

ViewController::~ViewController() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete commandFactory;
    commandFactory = nullptr;
}
