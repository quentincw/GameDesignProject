#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"
#include "projectile.h"

// constructor
Projectile::Projectile(int x, int y, float startXSpeed, float startYSpeed) : GameProcess() {
    hitbox.x = x;
    hitbox.y = y;
    radius = 10;
    xSpeed = startXSpeed;
    ySpeed = startYSpeed;
    damage = 10;
    tags.insert("projectile");
    interactions.insert("wall");
    interactions.insert("door");
}

// updates the object
void Projectile::Update(float deltaTime) {
    hitbox.x = hitbox.x + xSpeed;
    hitbox.y = hitbox.y + ySpeed;
}

void Projectile::handleInteraction(std::string tag) {
    if (tag == "wall" || tag == "player" || tag == "enemy" || tag == "door") {
        markForDeletion();
    }
}