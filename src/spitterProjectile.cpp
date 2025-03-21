#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"
#include "projectile.h"
#include "spitterProjectile.h"

// constructor
SpitterProjectile::SpitterProjectile(int x, int y, float startXSpeed, float startYSpeed) : Projectile(x, y, startXSpeed, startYSpeed) {

    radius = 10;
    damage = 10;
    hitbox.height = 15;
    hitbox.width = 15;
    tags.push_back("Player");
}

// updates the object
void SpitterProjectile::Update(float deltaTime) {
    hitbox.x = hitbox.x + xSpeed;
    hitbox.y = hitbox.y + ySpeed;
}

// draws the object
void SpitterProjectile::Render(SDL_Renderer* renderer) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x, point.y, radius, 0, 255, 0, 255);
}

// handles the interactions with other objects
void SpitterProjectile::handleInteractions(int tag) {
    switch (tag) {
        case 1: //Wall X
            markForDeletion();
            break;
        case 2: //Wall Y
            markForDeletion();
            break;
    }
}