#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"
#include "projectile.h"
#include "playerProjectile.h"

// constructor
PlayerProjectile::PlayerProjectile(int x, int y, float startXSpeed, float startYSpeed) : Projectile(x, y, startXSpeed, startYSpeed) {

    hitbox.radius = 15;
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
    filledCircleRGBA(renderer, hitbox.x, hitbox.y, hitbox.radius, 0, 255, 0, 255);
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