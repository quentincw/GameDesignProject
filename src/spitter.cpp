#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#include "enemy.h"
#include "spitter.h"
#include "spitterProjectile.h"


// constructor
Spitter::Spitter(int x, int y) : Enemy(x, y) {

    health = 150;
    hitbox.radius = 15;
    xSpeed = 0;
    ySpeed = 0;
    damage = 50;
    cooldown = 240;
    windup = 0;
    spitSpeed = 10;
}

// updates the object
void Spitter::Update(float deltaTime) {
    hitbox.x = hitbox.x + xSpeed;
    hitbox.y = hitbox.y + ySpeed;
    cooldown = cooldown - 1;
}

// draws the object
void Spitter::Render(SDL_Renderer* renderer) {
    filledCircleRGBA(renderer, hitbox.x, hitbox.y, hitbox.radius, 255, 255, 0, 255);
}

// updates the ai based on the player's position
void Spitter::UpdateAI(Circle phitbox) {

    if(cooldown <= 0){
        spitProjectile(phitbox);
        cooldown = 240;
    }

    // calculate vector
    float dx = phitbox.x - hitbox.x;
    float dy = phitbox.y - hitbox.y;

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

// creates a projectile object
void Spitter::spitProjectile(Circle phitbox) {

    // calculate vector
    float dx = phitbox.x - hitbox.x;
    float dy = phitbox.y - hitbox.y;

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
    //SpitterProjectile spit(hitbox.x, hitbox.y, projXspeed, projYspeed);
    SpitterProjectile* spit = new SpitterProjectile(hitbox.x, hitbox.y, projXspeed, projYspeed);
    //child = spit;
    // put spit in childrenList
    childrenList.clear();
    childrenList.push_back(spit);

    
    // set the flag for child to true
    children = true;
}


// handles the interactions with other objects
void Spitter::handleInteractions(int tag) {

}



