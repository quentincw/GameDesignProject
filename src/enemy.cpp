#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "enemy.h"

// constructor
Enemy::Enemy(int x, int y) : Entity() {
    interactions.push_back("Player");
    interactions.push_back("Wall");
    tags.push_back("Enemy");
    hitbox.x = x;
    hitbox.y = y;
    damage = 0;
}
