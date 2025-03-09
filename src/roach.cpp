#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <string>
#include <vector>
#include "enemy.h"
#include "roach.h"

// constructor
Roach::Roach(int x, int y) : Enemy(x, y) {

    health = 100;
    hitbox.radius = 10;
    xSpeed = 0;
    ySpeed = 0;
    damage = 50;
}

// updates the object
void Roach::Update(float deltaTime) {
    hitbox.x = hitbox.x + xSpeed;
    hitbox.y = hitbox.y + ySpeed;
}

// draws the object
void Roach::Render(SDL_Renderer* renderer) {
    filledCircleRGBA(renderer, hitbox.x, hitbox.y, hitbox.radius, 255, 0, 0, 255);
}

// updates the ai based on the player's position
void Roach::UpdateAI(Circle phitbox) {

    // calculate vector
    float dx = phitbox.x - hitbox.x;
    float dy = phitbox.y - hitbox.y;

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



