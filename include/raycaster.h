#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "player.h"
#include "map.h"
#include "constants.h"
#include <SDL2/SDL.h>

class Raycaster {
public:
    Raycaster(SDL_Renderer* renderer);
    void castRays(const Player& player, const Map& map);

private:
    SDL_Renderer* renderer;
    float degToRad(float deg);
};

#endif