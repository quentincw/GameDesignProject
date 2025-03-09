#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"
#include "projectile.h"

// constructor
Projectile::Projectile(int x, int y, float startXSpeed, float startYSpeed) {
    hitbox.x = x;
    hitbox.y = y;
    hitbox.radius = 10;
    xSpeed = startXSpeed;
    ySpeed = startYSpeed;
    damage = 10;
}

// updates the object
void Projectile::Update(float deltaTime) {
    hitbox.x = hitbox.x + xSpeed;
    hitbox.y = hitbox.y + ySpeed;
}

// draws the object
void Projectile::Render(SDL_Renderer* renderer) {
    filledCircleRGBA(renderer, hitbox.x, hitbox.y, hitbox.radius, 0, 255, 0, 255);
}

// get the x position of the projectile
Circle Projectile::getHitbox() const {
    return hitbox;
}


// get the damage the projectile causes to the player on contact
int Projectile::getDamage() const {
    return damage;
}

/*
// projectile collided with top/bottom of obstacle
void Projectile::bounceX(int newX){
    xSpeed = -xSpeed;
    xPos = newX;
}

// projectile collided with right/left of obstacle
void Projectile::bounceY(int newY){
    ySpeed = -ySpeed;
    yPos = newY;
}*/