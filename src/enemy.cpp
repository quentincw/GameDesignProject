#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "enemy.h"
#include <iostream>

// constructor
Enemy::Enemy(int x, int y) : Entity() {
    interactions.insert("player");
    tags.insert("enemy");
    hitbox.x = x;
    hitbox.y = y;
    damage = 0;
}

// destructor
Enemy::~Enemy() {} 

void Enemy::handleInteraction(const std::string tag) {
    Entity::handleInteraction(tag);
}