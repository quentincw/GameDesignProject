#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"
#include "projectile.h"
#include "spitterProjectile.h"

// constructor
SpitterProjectile::SpitterProjectile(int x, int y, float startXSpeed, float startYSpeed) : Projectile(x, y, startXSpeed, startYSpeed) {

    hitbox.radius = 10;
    damage = 10;
    tags.push_back("Player");
}

// updates the object
void SpitterProjectile::Update(float deltaTime) {
    hitbox.x = hitbox.x + xSpeed;
    hitbox.y = hitbox.y + ySpeed;
}

// draws the object
void SpitterProjectile::Render(SDL_Renderer* renderer) {
    filledCircleRGBA(renderer, hitbox.x, hitbox.y, hitbox.radius, 0, 255, 0, 255);
}