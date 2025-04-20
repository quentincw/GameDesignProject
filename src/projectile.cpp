#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"
#include "projectile.h"
#include <iostream>

// constructor
Projectile::Projectile(int x, int y, float startXSpeed, float startYSpeed) : GameProcess() {
    hitbox.x = x;
    hitbox.y = y;
    radius = 10;
    xSpeed = startXSpeed;
    ySpeed = startYSpeed;
    damage = 10;
    tags.insert("projectile");
}

// updates the object
void Projectile::Update(float deltaTime) {
    hitbox.x = hitbox.x + xSpeed;
    hitbox.y = hitbox.y + ySpeed;
    
    std::cout << hitbox.x << std::endl;
    std::cout << hitbox.y << std::endl;
}

// get the damage the projectile causes to the player on contact
int Projectile::getDamage() const {
    return damage;
}

void Projectile::handleInteraction(std::string tag) {
    if (tag == "enemy") {
        std::cout << "hit enemy";
    }
    if (tag == "wall" || tag == "player" || tag == "enemy") {
        markForDeletion();
    }
}