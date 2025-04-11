#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "enemy.h"

// constructor
Enemy::Enemy(int x, int y) : Entity() {
    interactions.push_back("player");
    interactions.push_back("wall");
    tags.push_back("enemy");
    hitbox.x = x;
    hitbox.y = y;
    damage = 0;
}

// destructor
Enemy::~Enemy() {} 

void Enemy::handleInteraction(const std::string tag) {
}