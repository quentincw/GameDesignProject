#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include "gameProcess.h"
#include "stairway.h"


// constructor
Stairway::Stairway(int x, int y, int height, int width)  {
    hitbox.x = x;
    hitbox.y = y;
    hitbox.height = height;
    hitbox.width = width;
    open = false;
    tags.insert("stairway");
}
// draw the wall
void Stairway::Render(SDL_Renderer* renderer) {
    //rectangleRGBA(renderer, hitbox.x, hitbox.y, hitbox.x + hitbox.width, hitbox.y + hitbox.height, 0, 100, 255, 255);
    RenderCam(renderer, 0, 0);
}

// updates the object
void Stairway::Update(float deltaTime) {
}

// draws the object based on the camera's position
void Stairway::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    //rectangleRGBA(renderer, hitbox.x - camX, hitbox.y - camY, hitbox.x - camX + hitbox.width, hitbox.y - camY + hitbox.height, 0, 100, 255, 255);

    SDL_Rect rect;

    rect.x = hitbox.x - camX;
    rect.y = hitbox.y - camY;
    rect.w = hitbox.width;
    rect.h = hitbox.height;

    SDL_SetRenderDrawColor( renderer, 105, 105, 105, 255 );
    SDL_RenderFillRect( renderer, &rect );

    // if the door is open, draw 2nd rectangle
    if(open) {
        rect.x = rect.x + 10;
        rect.y = rect.y + 10;
        rect.w = rect.w - 20;
        rect.h = rect.h - 20;
        SDL_SetRenderDrawColor( renderer, 50, 50, 50, 255 );
        SDL_RenderFillRect( renderer, &rect );
    }
}

// handles the interactions with other objects
void Stairway::handleInteraction(std::string tag) {
    if (tag == "player") {
        triggered = true;
    }
}

bool Stairway::isTriggered() {
    return triggered;
}

void Stairway::openStairs() {

    open = true;
    // interact with player again
    interactions.insert("player");
}