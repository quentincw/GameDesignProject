#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"
#include "projectile.h"
#include "playerProjectile.h"

// constructor
PlayerProjectile::PlayerProjectile(int x, int y, float startXSpeed, float startYSpeed) : Projectile(x, y, startXSpeed, startYSpeed) {

    radius = 15;
    hitbox.height = 30;
    hitbox.width = 30;
    damage = 100;
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

// draws the object based on the camera's position
void PlayerProjectile::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 0, 0, 255, 255);
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