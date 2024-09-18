#include "map.h"
#include <SDL2/SDL.h>
#include <algorithm>

Map::Map() {
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