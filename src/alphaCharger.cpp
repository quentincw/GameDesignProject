#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <string>
#include <vector>
#include "enemy.h"
#include "alphaCharger.h"

// constructor
AlphaCharger::AlphaCharger(int x, int y) : Enemy(x, y) {

    health = ALPHACHARGER_HEALTH;
    hitbox.height = ALPHACHARGER_SIZE;
    hitbox.width = ALPHACHARGER_SIZE;
    radius = ALPHACHARGER_RADIUS;
    xSpeed = 0;
    ySpeed = 0;
    damage = ALPHACHARGER_DAMAGE;
    charging = false;
    chargeDuration = 0;
    moveDuration = 0;
}

// updates the object
void AlphaCharger::Update(float deltaTime) {
    hitbox.x = hitbox.x + xSpeed;
    hitbox.y = hitbox.y + ySpeed;
    if(charging) {
        chargeDuration = chargeDuration - 1;
    }

    moveDuration = moveDuration - 1;

}

// draws the object
void AlphaCharger::Render(SDL_Renderer* renderer) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x, point.y, radius, 255, 0, 0, 255);
}

// draws the object based on the camera's position
void AlphaCharger::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 255, 0, 0, 255);
}

// updates the ai based on the player's position
void AlphaCharger::UpdateAI(Rectangle phitbox) {

    if(deleteFlag == true){
        spawnBloodStain();
    }

    // if the charger is charging, don't change direction
    if(chargeDuration > 0){
        return;
    }

    // charger is done charging
    charging = false;

    Point playerCenter = getCenter(&phitbox);
    Point enemyCenter = getCenter(&hitbox);

    // check if the player is on the same x as the charger
    if((enemyCenter.x + ALPHACHARGER_SIZE/2 > playerCenter.x) && (enemyCenter.x - ALPHACHARGER_SIZE/2 < playerCenter.x)) {
        charging = true;
        chargeDuration = ALPHACHARGER_CHARGEDURATION;
        moveDuration = 0;
        // charge direction
        if(enemyCenter.y < playerCenter.y){
            ySpeed = ALPHACHARGER_CHARGE_SPEED;
        }
        else {
            ySpeed = -ALPHACHARGER_CHARGE_SPEED;
        }
        xSpeed = 0;
        return;
    } 
    // check if the player is on the same y as the charger
    else if((enemyCenter.y + ALPHACHARGER_SIZE/2 > playerCenter.y) && (enemyCenter.y - ALPHACHARGER_SIZE/2 < playerCenter.y)) {
        charging = true;
        chargeDuration = ALPHACHARGER_CHARGEDURATION;
        moveDuration = 0;
        // charge direction
        if(enemyCenter.x < playerCenter.x){
            xSpeed = ALPHACHARGER_CHARGE_SPEED;
        }
        else {
            xSpeed = -ALPHACHARGER_CHARGE_SPEED;
        }
        ySpeed = 0;
        return;
    }

    // charger is not charging and player is not on same x or y
    // pick random direction and move in that direction for a duration

    // if the charger is moving, don't change direction
    if(moveDuration > 0){
        return;
    }

    moveDuration = 50;

    int newDirection = rand() % 4;
    switch (newDirection) {
        // move right
        case 0:
            xSpeed = ALPHACHARGER_SPEED;
            ySpeed = 0;
            break;
        // move left
        case 1:
            xSpeed = -ALPHACHARGER_SPEED;
            ySpeed = 0;
            break;
        // move down
        case 2:
            xSpeed = 0;
            ySpeed = ALPHACHARGER_SPEED;
            break;
        // move up
        case 3:
            xSpeed = 0;
            ySpeed = -ALPHACHARGER_SPEED;
            break;
        default:
            break;
    }
}
