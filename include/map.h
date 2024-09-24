#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include "constants.h"
#include <SDL2/SDL_image.h>

class Map {
public:
    Map(SDL_Renderer* renderer);
    ~Map();
    bool isWall(int x, int y) const;
    int getTile(int x, int y) const;
    void draw(SDL_Renderer* renderer) const;

private:
    int map[MAP_HEIGHT][MAP_WIDTH];
    SDL_Texture* wallTexture;
    SDL_Texture* floorTexture;
    SDL_Renderer* renderer;
    void loadTextures();
};

#endif