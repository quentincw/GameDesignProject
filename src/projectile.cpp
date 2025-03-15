#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"
#include "projectile.h"

// constructor
Projectile::Projectile(int x, int y, float startXSpeed, float startYSpeed) : GameProcess() {
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

// get the damage the projectile causes to the player on contact
int Projectile::getDamage() const {
    return damage;
}

