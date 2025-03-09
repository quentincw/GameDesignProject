/*#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameObject.h"
#include "projectile.h"

// constructor
Projectile::Projectile(int x, int y, float startXSpeed, float startYSpeed) {
    xPos = x;
    yPos = y;
    radius = 10;
    xSpeed = startXSpeed;
    ySpeed = startYSpeed;
    damage = 10;
}

// updates the object
void Projectile::Update(float deltaTime) {
    xPos = xPos + xSpeed;
    yPos = yPos + ySpeed;
}

// draws the object
void Projectile::Render(SDL_Renderer* renderer) {
    filledCircleRGBA(renderer, xPos, yPos, radius, 0, 255, 0, 255);
}

// get the x position of the projectile
int Projectile::getXpos() const {
    return xPos;
}

// get the y position of the projectile
int Projectile::getYpos() const {
    return yPos;
}

// get the radius of the projectile (for collision detection)
int Projectile::getRadius() const {
    return radius;
}

// get the damage the projectile causes to the player on contact
int Projectile::getDamage() const {
    return damage;
}

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