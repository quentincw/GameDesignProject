#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "enemy.h"
#include "roach.h"

// constructor
Roach::Roach(int x, int y) : Enemy(x, y) {
    xPos = x;
    yPos = y;
    health = 100;
    radius = 10;
    xSpeed = 0;
    ySpeed = 0;
    damage = 50;
    alive = true;
}

// updates the object
void Roach::Update(float deltaTime) {
    xPos = xPos + xSpeed;
    yPos = yPos + ySpeed;
}

// draws the object
void Roach::Render(SDL_Renderer* renderer) {
    filledCircleRGBA(renderer, xPos, yPos, radius, 255, 0, 0, 255);
}

// updates the ai based on the player's position
void Roach::UpdateAI(int pX, int pY) {

    // calculate vector
    float dx = pX - xPos;
    float dy = pY - yPos;

    // normalize
    float length = sqrt((dx * dx) + (dy * dy));

    if(length != 0) {
        dx = dx / length;
        dy = dy / length;
    }

    // set the speed based on speed
    xSpeed = dx * 3;
    ySpeed = dy * 3;
}



