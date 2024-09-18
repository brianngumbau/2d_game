#include "renderer.h"
#include <SDL2/SDL.h>

Renderer::Renderer(SDL_Renderer* renderer) : renderer(renderer) {}

void Renderer::drawPlayer(const Player& player) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Player color (red)
    SDL_Rect rect = { (int)player.getX(), (int)player.getY(), 10, 10 };
    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::drawMap(const Map& map) {
    map.draw(renderer);
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
}