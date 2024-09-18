#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "player.h"
#include "map.h"

class Renderer {
public:
    Renderer(SDL_Renderer* renderer);
    void drawPlayer(const Player& player);
    void drawMap(const Map& map);
    void clear();
    void present();

private:
    SDL_Renderer* renderer;
};

#endif