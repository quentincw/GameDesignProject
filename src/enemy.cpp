#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "enemy.h"

// constructor
Enemy::Enemy(int x, int y) {
    xPos = x;
    yPos = y;
    health = 0;
    xSpeed = 0;
    ySpeed = 0;
    damage = 0;
    alive = true;
}

// checks if the enemy is dead or alive
bool Enemy::isAlive() const {
    return alive;
}
        
// damage the enemy and update alive status
void Enemy::takeDamage(int damage_taken) {
    health = health - damage_taken;
    //check if the enemy is dead
    if (health <= 0){
        alive = false;
    }
}

// get the x position of the enemy
int Enemy::getXpos() const {
    return xPos;
}

// get the y position of the enemy
int Enemy::getYpos() const {
    return yPos;
}

// get the radius of the enemy (for collision detection)
int Enemy::getRadius() const {
    return radius;
}

// get the damage the enemy causes to the player on contact
int Enemy::getDamage() const {
    return damage;
}

