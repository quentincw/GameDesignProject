#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <string>
#include <vector>
#include "enemy.h"
#include "alphaCharger.h"
#include <constants.h>

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
    Entity::Update(deltaTime);
    if(charging) {
        chargeDuration = chargeDuration - 1;
    }
    red -= 1;
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

    static SDL_Surface* proj_surface = SDL_LoadBMP( "../resource/enemies/a_charger.bmp" );
    static SDL_Texture* proj_texture = SDL_CreateTextureFromSurface( renderer, proj_surface );

    SDL_SetTextureColorMod(proj_texture, 255, 255, 255);
    if(red > 0) {
        SDL_SetTextureColorMod(proj_texture, 255, 0, 0);
    }

    static SDL_Rect spriteTextures[4] = {
        {0, 0, 32, 32},
        {32, 0, 32, 32},
        {64, 0, 32, 32},
        {96, 0, 32, 32}
    };

    static const int total_frames = 4;
    static const int fps = 12;
    static int frame = 0;

    static Uint64 startTicks = SDL_GetTicks();

    Uint64 curTicks = SDL_GetTicks();
    float deltaTime = curTicks - startTicks;
    if (deltaTime > 1000 / fps) {
        if (xSpeed != 0 || ySpeed != 0) {
            frame = (frame + 1) % total_frames;
        }
        // use idle sprite
        else {
            frame = 0;
        }
        startTicks = curTicks;
    }

    static SDL_RendererFlip flip = SDL_FLIP_NONE;

    if (xSpeed < 0) {
        flip = SDL_FLIP_NONE;
    }
    if (xSpeed > 0) {
        flip = SDL_FLIP_HORIZONTAL;
    }

    SDL_Rect dst = { point.x - camX - 64, point.y - camY - 76, TILE_SIZE * 2, TILE_SIZE * 2 };

    SDL_RenderCopyEx(renderer, proj_texture, &spriteTextures[frame], &dst, NULL, NULL, flip);

    // filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 255, 0, 0, 100);
}

// updates the ai based on the player's position
void AlphaCharger::UpdateAI(Rectangle phitbox) {

    if(deleteFlag == true){
        spawnBloodStain();
		deathSound(1);
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
        soundList.push_back(SoundType::CHARGER_CHARGE);
        sounds = true;
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
        soundList.push_back(SoundType::CHARGER_CHARGE);
        sounds = true;
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
