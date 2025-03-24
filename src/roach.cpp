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
    hitbox.height = 10;
    hitbox.width = 10;
    radius = 10;
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
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x, point.y, radius, 255, 0, 0, 255);
}

// draws the object based on the camera's position
void Roach::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 255, 0, 0, 255);
}

// updates the ai based on the player's position
void Roach::UpdateAI(Rectangle phitbox) {

    Point playerCenter = getCenter(&phitbox);
    Point enemyCenter = getCenter(&hitbox);
    // calculate vector
    float dx = playerCenter.x - enemyCenter.x;
    float dy = playerCenter.y - enemyCenter.y;

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


// handles the interactions with other objects
void Roach::handleInteractions(int tag) {

}


