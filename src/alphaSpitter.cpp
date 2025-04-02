#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#include "enemy.h"
#include "alphaSpitter.h"
#include "spitterProjectile.h"


// constructor
AlphaSpitter::AlphaSpitter(int x, int y) : Enemy(x, y) {

    health = 250;
    radius = 25;
    hitbox.height = 50;
    hitbox.width = 50;
    xSpeed = 0;
    ySpeed = 0;
    damage = 50;
    cooldown = 300;
    windup = 0;
    spitSpeed = 5;
}

// updates the object
void AlphaSpitter::Update(float deltaTime) {
    hitbox.x = hitbox.x + xSpeed;
    hitbox.y = hitbox.y + ySpeed;
    cooldown = cooldown - 1;
}

// draws the object
void AlphaSpitter::Render(SDL_Renderer* renderer) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x, point.y, radius, 255, 255, 0, 255);
}

// draws the object based on the camera's position
void AlphaSpitter::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 255, 255, 0, 255);
}

// updates the ai based on the player's position
void AlphaSpitter::UpdateAI(Rectangle phitbox) {

    if(cooldown <= 0){
        spitProjectile(phitbox);
        cooldown = 300;
    }

    // get center of hitboxes
    Point playerCenter = getCenter(&phitbox);
    Point enemyCenter = getCenter(&hitbox);

    // calculate vector
    float dx = playerCenter.x - enemyCenter.x;
    float dy = playerCenter.y - enemyCenter.y;

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
void AlphaSpitter::spitProjectile(Rectangle phitbox) {


    // get center of hitboxes
    Point playerCenter = getCenter(&phitbox);
    Point enemyCenter = getCenter(&hitbox);

    // calculate vector
    float dx = playerCenter.x - enemyCenter.x;
    float dy = playerCenter.y - enemyCenter.y;

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
void AlphaSpitter::handleInteractions(int tag) {

}



