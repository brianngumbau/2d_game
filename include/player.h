#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "Constants.h"
#include "map.h"

class Player {
public:
    Player(float x, float y, float angle);
    void handleInput(const Uint8* keyState);
    void update(const Map& map);
    float getX() const;
    float getY() const;
    float getAngle() const;

private:
    float x, y;
    float angle;
    float moveSpeed;
    float rotateSpeed;
};

#endif