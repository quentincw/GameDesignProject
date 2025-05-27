#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"
#include "pickup.h"

// default constructor
Pickup::Pickup(int x, int y) : GameProcess() {
    hitbox.x = x;
    hitbox.y = y;
    pickupStats.health = 0;
    pickupStats.armor = 0;
    pickupStats.damage = 0;
    damage = 0;
    tags.insert("pickup");
}

// constructor
Pickup::Pickup(int x, int y, int health, int armor, int damage) : GameProcess() {
    hitbox.x = x;
    hitbox.y = y;
    pickupStats.health = health;
    pickupStats.armor = armor;
    pickupStats.damage = damage;
}

// updates the object
void Pickup::Update(float deltaTime) {
    
}

// get the stats associated with the pickup
Stats Pickup::getStats() const {
    return pickupStats;
}

void Pickup::handleInteraction(std::string tag) {
}