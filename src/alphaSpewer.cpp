#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#include "enemy.h"
#include "alphaSpewer.h"
#include "spitterProjectile.h"


// constructor
AlphaSpewer::AlphaSpewer(int x, int y) : Enemy(x, y) {

    health = ALPHASPEWER_HEALTH;
    radius = ALPHASPEWER_RADIUS;
    hitbox.height = ALPHASPEWER_SIZE;
    hitbox.width = ALPHASPEWER_SIZE;
    xSpeed = 0;
    ySpeed = 0;
    damage = ALPHASPEWER_DAMAGE;
    cooldown = ALPHASPEWER_COOLDOWN;
    spitSpeed = SPEWERPROJECTILE_SPEED + 2;
    projectileAmount = 0;
    spitInterval = 20;
}

// updates the object
void AlphaSpewer::Update(float deltaTime) {

    // check if the spewer is still spitting
    if(projectileAmount <= 0){
        hitbox.x = hitbox.x + xSpeed;
        hitbox.y = hitbox.y + ySpeed;
        cooldown = cooldown - 1;
    }
    // time inbetween projectiles
    else if (spitInterval > 0){
        spitInterval = spitInterval - 1;
    }
}

// draws the object
void AlphaSpewer::Render(SDL_Renderer* renderer) {
    RenderCam(renderer, 0, 0);
}

// draws the object based on the camera's position
void AlphaSpewer::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 205, 92, 92, 255);
}

// updates the ai based on the player's position
void AlphaSpewer::UpdateAI(Rectangle phitbox) {

    if(deleteFlag == true){
        spawnBloodStain();
    }

    if(cooldown <= 0){
        projectileAmount = ALPHASPEWER_PROJECTILE_NUMBER;
        cooldown = ALPHASPEWER_COOLDOWN;
    }
    // check if there are any projectiles left to spit, 
    // and if enough time has passed between the last spit
    if((projectileAmount > 0) && (spitInterval <= 0)) {
        spitProjectile(phitbox);
        spitInterval = ALPHASPEWER_SPIT_INTERVAL;

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
    xSpeed = dx * ALPHASPEWER_SPEED;
    ySpeed = dy * ALPHASPEWER_SPEED;

    // if the player is too close, reverse
    if(length <= 300){
        xSpeed = -xSpeed;
        ySpeed = -ySpeed;
    }
    // buffer to stop stuttering when on the boundary of too close/far to player
    else if(length < 450){
        xSpeed = 0;
        ySpeed = 0;
    }
}

// creates a projectile object
void AlphaSpewer::spitProjectile(Rectangle phitbox) {

    
    // get center of hitboxes
    Point playerCenter = getCenter(&phitbox);
    Point enemyCenter = getCenter(&hitbox);

    // spawn explosion centered on the enemy
    int x = enemyCenter.x - (SPITTERPROJECTILE_SIZE / 2);
    int y = enemyCenter.y - (SPITTERPROJECTILE_SIZE / 2);

    // calculate random angle (2 - 10)
    int newDirection = (rand() % 9) + 2;

    // multiply to get more varied numbers
    newDirection = newDirection * 2;

    // negative angles
    if(rand() % 2 == 1){
        newDirection = -newDirection;
    }

    // calculate vector
    float dx = playerCenter.x - enemyCenter.x;
    float dy = playerCenter.y - enemyCenter.y;

    // normalize
    float length = sqrt((dx * dx) + (dy * dy));

    if(length != 0) {
        dx = dx / length;
        dy = dy / length;
    }

    // rotate 
    float angle = newDirection; 
    float radians = angle * (M_PI / 180.0f); 
    float cosAngle = cos(radians);
    float sinAngle = sin(radians);
    
    // Apply the rotation
    float rotatedDx = dx * cosAngle - dy * sinAngle;
    float rotatedDy = dx * sinAngle + dy * cosAngle;
    
    // Set the speed based on spitSpeed
    float projXspeed = rotatedDx * spitSpeed;
    float projYspeed = rotatedDy * spitSpeed;

    // create spit at SPEWER's location w/ calculated speeds
    SpitterProjectile* spit = new SpitterProjectile(x, y, projXspeed, projYspeed);

    childrenList.push_back(spit);
    
    // set the flag for child to true
    children = true;
    // decrement projectiles to shoot
    projectileAmount = projectileAmount - 1;
}



