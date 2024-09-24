#include "game.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "map.h"
#include <algorithm>

Game::Game() : window(nullptr), renderer(nullptr), isRunning(false) {}

Game::~Game() {
    clean();
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("2D Maze Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    player = new Player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
    map = new Map(renderer);
    gameRenderer = new Renderer(renderer);
    raycaster = new Raycaster(renderer);

    isRunning = true;
    return true;
}

void Game::run() {
    while (isRunning) {
        handleEvents();
        update();
        render();

        SDL_Delay(16);
    }
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
    }
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    player->handleInput(keyState);
}

void Game::update() {
    player->update(*map);
}

void Game::render() {
    gameRenderer->clear();
    gameRenderer->drawMap(*map);
    raycaster->castRays(*player, *map);
    gameRenderer->drawPlayer(*player);
    gameRenderer->present();
}

void Game::clean() {
    delete player;
    delete map;
    delete gameRenderer;
    delete raycaster;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}