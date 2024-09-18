#include "game.h"
#include "SDL2/SDL_main.h"
#include "SDL2/SDL.h"


int SDL_main(int argc, char* argv[]) {
    Game game;

    if (!game.init()) {
        return -1;
    }

    game.run();
    return 0;
}