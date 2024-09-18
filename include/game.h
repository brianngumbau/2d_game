#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "player.h"
#include "map.h"
#include "renderer.h"
#include "raycaster.h"

class Game {
public:
    Game();
    ~Game();
    bool init();
    void run();
    void handleEvents();
    void update();
    void render();
    void clean();

private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;

    Player* player;
    Map* map;
    Renderer* gameRenderer;
    Raycaster* raycaster;
};

#endif