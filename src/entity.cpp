#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include "entity.h"
#include "gameProcess.h"


Entity::Entity() : GameProcess() {
    health = 0;
    maxHealth = 0;
    isAlive = true;
    speed = 0;
    xSpeed = 0;
    ySpeed = 0;

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
