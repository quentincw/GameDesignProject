#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#include "enemy.h"
#include "spawner.h"
#include "roach.h"


// constructor
Spawner::Spawner(int x, int y) : Enemy(x, y) {

    health = 200;
    radius = 20;
    hitbox.height = 40;
    hitbox.width = 40;
    xSpeed = 0;
    ySpeed = 0;
    damage = 50;
    cooldown = 240;
}

// updates the object
void Spawner::Update(float deltaTime) {
    hitbox.x = hitbox.x + xSpeed;
    hitbox.y = hitbox.y + ySpeed;
    cooldown = cooldown - 1;
}

// draws the object
void Spawner::Render(SDL_Renderer* renderer) {
    RenderCam(renderer, 0, 0);
}

// draws the object based on the camera's position
void Spawner::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 128, 128, 0, 255);
}

// updates the ai based on the player's position
void Spawner::UpdateAI(Rectangle phitbox) {

    if(deleteFlag == true){
        spawnBloodStain();
    }

    if(cooldown <= 0){
        spawnEnemy();
        cooldown = 240;
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
    xSpeed = dx * 1;
    ySpeed = dy * 1;

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
void Spawner::spawnEnemy() {

    // create spit at spitter's location w/ calculated speeds
    //SpitterProjectile spit(hitbox.x, hitbox.y, projXspeed, projYspeed);
    Roach* roach = new Roach(hitbox.x, hitbox.y);
    // put roach in childrenList
    childrenList.push_back(roach);

    
    // set the flag for child to true
    children = true;
}
