/*#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include "entity.h"


Entity::Entity() : Process({"Wall"}) {
    health = 0;
    maxHealth = 0;
    isAlive = true;
    speed = 0;
    xSpeed = 0;
    ySpeed = 0;
    hitbox.x = 0;
    hitbox.y = 0;
    hitbox.radius = 0;

}

// gets the current health
int Entity::getHealth() const {
    return health;
}

// subtracts the health damage from the current health
void Entity::adjustHealth(int healthDamage) {
    health = health - healthDamage;
    if (health <= 0) {
        isAlive = false;
    }
}

// gets the circle of the entity
Circle Entity::getHitbox() const {
    return hitbox;
}*/