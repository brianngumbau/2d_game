#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include "constants.h"

class Map {
public:
    Map();
    bool isWall(int x, int y) const;
    int getTile(int x, int y) const;
    void draw(SDL_Renderer* renderer) const;

private:
    int map[MAP_HEIGHT][MAP_WIDTH];
};

#endif