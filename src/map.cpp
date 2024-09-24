#include "map.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>

Map::Map(SDL_Renderer* renderer) : renderer(renderer) {
    // Simple hardcoded map (1 = wall, 0 = empty space)
    int temp[MAP_HEIGHT][MAP_WIDTH] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    std::copy(&temp[0][0], &temp[0][0] + MAP_HEIGHT * MAP_WIDTH, &map[0][0]);

    loadTextures();
}

Map::~Map() {
    if (wallTexture) SDL_DestroyTexture(wallTexture);
    if (floorTexture) SDL_DestroyTexture(floorTexture);
}

void Map::loadTextures() {
    // Load wall texture
    SDL_Surface* wallSurface = IMG_Load("assets/wall_texture.jpeg");
    if (wallSurface == nullptr) {
        SDL_Log("Failed to load wall texture: %s", IMG_GetError());
    } else {
        wallTexture = SDL_CreateTextureFromSurface(renderer, wallSurface);
        SDL_FreeSurface(wallSurface);
    }

    // Load floor texture
    SDL_Surface* floorSurface = IMG_Load("assets/floor_texture.jpeg");
    if (floorSurface == nullptr) {
        SDL_Log("Failed to load floor texture: %s", IMG_GetError());
    } else {
        floorTexture = SDL_CreateTextureFromSurface(renderer, floorSurface);
        SDL_FreeSurface(floorSurface);
    }
}

bool Map::isWall(int x, int y) const {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        return true;
    }
    return map[y][x] == 1;
}

int Map::getTile(int x, int y) const {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        return -1;  // Return an invalid value if out of bounds
    }
    return map[y][x];  // Return the tile value (1 for wall, 0 for empty space)
}

void Map::draw(SDL_Renderer* renderer) const {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            SDL_Rect rect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
            if (map[y][x] == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Wall color (white)
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Empty space color (black)
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}