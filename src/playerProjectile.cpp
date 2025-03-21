#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"
#include "projectile.h"
#include "playerProjectile.h"

// constructor
PlayerProjectile::PlayerProjectile(int x, int y, float startXSpeed, float startYSpeed) : Projectile(x, y, startXSpeed, startYSpeed) {

    radius = 15;
    hitbox.height = 15;
    hitbox.width = 15;
    damage = 10;
    tags.push_back("Player");
    tags.push_back("Enemy");
}

// updates the object
void PlayerProjectile::Update(float deltaTime) {
    hitbox.x = hitbox.x + xSpeed;
    hitbox.y = hitbox.y + ySpeed;
}

// draws the object
void PlayerProjectile::Render(SDL_Renderer* renderer) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x, point.y, radius, 0, 0, 255, 255);
}

// handles the interactions with other objects
void PlayerProjectile::handleInteractions(int tag) {
    switch (tag) {
        case 1: //Wall X
            bounceX(hitbox.x);
            break;
        case 2: // Wall Y
            bounceY(hitbox.y);
            break;
    }
}


// projectile collided with top/bottom of obstacle
void PlayerProjectile::bounceX(int newX){
    xSpeed = -xSpeed;
    hitbox.x = newX;
}

// projectile collided with right/left of obstacle
void PlayerProjectile::bounceY(int newY){
    ySpeed = -ySpeed;
    hitbox.y = newY;
}