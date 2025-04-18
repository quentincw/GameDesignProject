#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include "gameProcess.h"
#include "gameDoor.h"


// constructor
GameDoor::GameDoor(int x, int y, int height, int width)  {
    hitbox.x = x;
    hitbox.y = y;
    hitbox.height = height;
    hitbox.width = width;
    tags.insert("door");
    tags.insert("wall");
}
// draw the wall
void GameDoor::Render(SDL_Renderer* renderer) {
    //rectangleRGBA(renderer, hitbox.x, hitbox.y, hitbox.x + hitbox.width, hitbox.y + hitbox.height, 0, 100, 255, 255);
    RenderCam(renderer, 0, 0);
}

// updates the object
void GameDoor::Update(float deltaTime) {
}

// draws the object based on the camera's position
void GameDoor::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    //rectangleRGBA(renderer, hitbox.x - camX, hitbox.y - camY, hitbox.x - camX + hitbox.width, hitbox.y - camY + hitbox.height, 0, 100, 255, 255);

    SDL_Rect rect;

    rect.x = hitbox.x - camX;
    rect.y = hitbox.y - camY;
    rect.w = hitbox.width;
    rect.h = hitbox.height;

    SDL_SetRenderDrawColor( renderer, 100, 0, 255, 255 );
    SDL_RenderFillRect( renderer, &rect );
}

// handles the interactions with other objects
void GameDoor::handleInteraction(std::string tag) {
}