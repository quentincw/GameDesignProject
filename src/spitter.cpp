/*#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#include "enemy.h"
#include "spitter.h"
#include "projectile.h"


// constructor
Spitter::Spitter(int x, int y) : Enemy(x, y) {
    xPos = x;
    yPos = y;
    health = 150;
    radius = 15;
    xSpeed = 0;
    ySpeed = 0;
    damage = 50;
    alive = true;
    hasChild = false;
    player_x = 0;
    player_y = 0;
    cooldown = 240;
    windup = 0;
    spit = nullptr;
    spitSpeed = 10;
}

// updates the object
void Spitter::Update(float deltaTime) {
    xPos = xPos + xSpeed;
    yPos = yPos + ySpeed;
    cooldown = cooldown - 1;
}

// draws the object
void Spitter::Render(SDL_Renderer* renderer) {
    filledCircleRGBA(renderer, xPos, yPos, radius, 255, 255, 0, 255);
}

// updates the ai based on the player's position
void Spitter::UpdateAI(int pX, int pY) {

    if(cooldown <= 0){
        spitProjectile();
        cooldown = 240;
    }

    player_x = pX;
    player_y = pY;

    // calculate vector
    float dx = player_x - xPos;
    float dy = player_y - yPos;

    // normalize
    float length = sqrt((dx * dx) + (dy * dy));

    if(length != 0) {
        dx = dx / length;
        dy = dy / length;
    }

    // set the speed based on speed
    xSpeed = dx * 3;
    ySpeed = dy * 3;

    // if the player is too close, reverse
    if(length <= 250){
        xSpeed = -xSpeed;
        ySpeed = -ySpeed;
    }
    // buffer to stop stuttering when on the boundary of too close/far to player
    else if(length < 300){
        xSpeed = 0;
        ySpeed = 0;
    }
}

// returns whether the spitter has a child or not
bool Spitter::hasChildren() const {
    return hasChild;
}

// gets the projectile the spitter created
Projectile* Spitter::getChildren() {
    hasChild = false;
    return spit;
}

// creates a projectile object
void Spitter::spitProjectile() {

    // calculate vector
    float dx = player_x - xPos;
    float dy = player_y - yPos;

    // normalize
    float length = sqrt((dx * dx) + (dy * dy));

    if(length != 0) {
        dx = dx / length;
        dy = dy / length;
    }

    // set the speed based on spitSpeed
    float projXspeed = dx * spitSpeed;
    float projYspeed = dy * spitSpeed;

    // create spit at spitter's location w/ calculated speeds
    spit = new Projectile(xPos, yPos, projXspeed, projYspeed);
    
    // set the flag for child to true
    hasChild = true;
}*/



