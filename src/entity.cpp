#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include "entity.h"
#include "gameProcess.h"
#include "bloodStain.h"


Entity::Entity() : GameProcess() {
    tags.insert("entity");
    interactions.insert("wall");
    interactions.insert("door");
    health = 0;
    maxHealth = 0;
    isAlive = true;
    speed = 0;
    xSpeed = 0;
    ySpeed = 0;
}

// updates the position of an entity
void Entity::Update(float deltaTime) {
    lastX = hitbox.x;
    lastY = hitbox.y;

    hitbox.x += xSpeed;
    hitbox.y += ySpeed;
}

// gets the current health
int Entity::getHealth() const {
    return health;
}

// subtracts the health damage from the current health
void Entity::adjustHealth(int healthDamage) {
    health = health - healthDamage;
    if (health <= 0) {
        health = 0;
        isAlive = false;
        markForDeletion();
    }
}

void Entity::spawnBloodStain(int color) {
    BloodStain* blood = new BloodStain(hitbox.x, hitbox.y, hitbox.height, hitbox.width, color);
    childrenList.push_back(blood);
    children = true;
}

void Entity::handleInteraction(std::string tag) {
    if (tag == "wall" || tag == "door") {
        revertPosition();
    }
}