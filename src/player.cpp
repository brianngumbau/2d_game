#include "player.h"
#include "SDL2/SDL.h"
#include <cmath>

Player::Player(float x, float y, float angle)
    : x(x), y(y), angle(angle), moveSpeed(MOVE_SPEED), rotateSpeed(ROTATE_SPEED) {}

void Player::handleInput(const Uint8* keyState) {
    if (keyState[SDL_SCANCODE_W]) {
        x += cos(angle) * moveSpeed;
        y += sin(angle) * moveSpeed;
    }
    if (keyState[SDL_SCANCODE_S]) {
        x -= cos(angle) * moveSpeed;
        y -= sin(angle) * moveSpeed;
    }
    if (keyState[SDL_SCANCODE_A]) {
        angle -= rotateSpeed;
    }
    if (keyState[SDL_SCANCODE_D]) {
        angle += rotateSpeed;
    }
}

void Player::update(const Map& map) {
    float newX = x + cos(angle) * moveSpeed;
    float newY = y + sin(angle) * moveSpeed;

    int mapX = (int)(newX / TILE_SIZE);
    int mapY = (int)(newY / TILE_SIZE);

    if (!map.isWall(mapX, mapY)) {
        x = newX;
        y = newY;
    }

    if (angle < 0) angle += 2 * M_PI;
    if (angle > 2 * M_PI) angle -= 2 * M_PI;
}

float Player::getX() const { return x; }
float Player::getY() const { return y; }
float Player::getAngle() const { return angle; }