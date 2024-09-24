#include "raycaster.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

Raycaster::Raycaster(SDL_Renderer* renderer) : renderer(renderer) {}

float Raycaster::degToRad(float deg) {
    return deg * M_PI / 180.0f;
}

void Raycaster::castRays(const Player& player, const Map& map) {
    int screenWidth = 640;
    int screenHeight = 480;

    // Player's position and angle
    float posX = player.getX();
    float posY = player.getY();
    float angle = player.getAngle();

    //player's direction vector
    float dirX = cos(angle);
    float dirY = sin(angle);

    //Defining the camera plane
    float planeX = -dirY * 0.66;
    float planeY = dirX * 0.66;

    for (int x = 0; x < screenWidth; x++) {
        // Calculate cameraX and ray direction
        float cameraX = 2 * x / static_cast<float>(screenWidth) - 1;
        float rayDirX = dirX + planeX * cameraX;
        float rayDirY = dirY + planeY * cameraX;


        // Initial position of the ray (the player's position)
        int mapX = static_cast<int>(posX);
        int mapY = static_cast<int>(posY);

        // Ray length from one x or y to the next x or y side
        float deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        float deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        float sideDistX, sideDistY;

        //Direction to step in x or y(+1 or -1)
        int stepX, stepY;


        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        // Perform DDA to detect wall hit
        bool hit = false;
        int side; // was it a NS or a EW wall?
        while (!hit) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            // Check if ray hit a wall
            if (map.getTile(mapX, mapY) > 0) hit = true;
        }

        // Calculate distance to the wall
        float perpWallDist;
        if (side == 0) {
            perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
        } else {
            perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
        }       

        // Calculate the height of the wall slice to draw
        int lineHeight = static_cast<int>(screenHeight / perpWallDist);

        // Calculate lowest and highest pixel to fill in the current stripe
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        // Choose wall color
        SDL_Color color;
        if (side == 0) {
            color = {255, 0, 0, 255};
        } else {
            color = {128, 0, 0, 255};
        }        

        // Render the wall slice
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        for (int y = drawStart; y <= drawEnd; ++y) {
            SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
        }
    }
}