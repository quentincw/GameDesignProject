#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#include "enemy.h"
#include "spewer.h"
#include "spitterProjectile.h"


// constructor
Spewer::Spewer(int x, int y) : Enemy(x, y) {

    health = 250;
    radius = 20;
    hitbox.height = 40;
    hitbox.width = 40;
    xSpeed = 0;
    ySpeed = 0;
    damage = 50;
    cooldown = 300;
    windup = 0;
    spitSpeed = 3;
}

// updates the object
void Spewer::Update(float deltaTime) {
    Entity::Update(deltaTime);
    cooldown = cooldown - 1;
}

// draws the object
void Spewer::Render(SDL_Renderer* renderer) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x, point.y, radius, 255, 100, 0, 255);
}

// draws the object based on the camera's position
void Spewer::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 255, 100, 0, 255);
}

// updates the ai based on the player's position
void Spewer::UpdateAI(Rectangle phitbox) {

    if(deleteFlag == true){
        spawnBloodStain();
    }

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
    xSpeed = dx * 2;
    ySpeed = dy * 2;

    // if the player is too close, reverse
    if(length <= 150){
        xSpeed = -xSpeed;
        ySpeed = -ySpeed;
    }
    // buffer to stop stuttering when on the boundary of too close/far to player
    else if(length < 200){
        xSpeed = 0;
        ySpeed = 0;
    }
}

// creates a projectile object
void Spewer::spitProjectile(Rectangle phitbox) {


    //SpitterProjectile spit(hitbox.x, hitbox.y, projXspeed, projYspeed);
    SpitterProjectile* spit = new SpitterProjectile(hitbox.x, hitbox.y, spitSpeed, spitSpeed);
    //child = spit;
    // put spit in childrenList
    //childrenList.clear();
    childrenList.push_back(spit);

    spit = new SpitterProjectile(hitbox.x, hitbox.y, -spitSpeed, spitSpeed);
    childrenList.push_back(spit);

    spit = new SpitterProjectile(hitbox.x, hitbox.y, -spitSpeed, -spitSpeed);
    childrenList.push_back(spit);

    spit = new SpitterProjectile(hitbox.x, hitbox.y, spitSpeed, -spitSpeed);
    childrenList.push_back(spit);

    // up, down, left, right

    spit = new SpitterProjectile(hitbox.x, hitbox.y, -spitSpeed, 0);
    childrenList.push_back(spit);

    spit = new SpitterProjectile(hitbox.x, hitbox.y, 0, -spitSpeed);
    childrenList.push_back(spit);

    spit = new SpitterProjectile(hitbox.x, hitbox.y, spitSpeed, 0);
    childrenList.push_back(spit);

    spit = new SpitterProjectile(hitbox.x, hitbox.y, 0, spitSpeed);
    childrenList.push_back(spit);


    
    // set the flag for child to true
    children = true;
}