#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <string>
#include <vector>
#include "enemy.h"
#include "charger.h"
#include <constants.h>

// constructor
Charger::Charger(int x, int y) : Enemy(x, y) {

    health = CHARGER_HEALTH;
    hitbox.height = CHARGER_SIZE;
    hitbox.width = CHARGER_SIZE;
    radius = CHARGER_RADIUS;
    xSpeed = 0;
    ySpeed = 0;
    damage = CHARGER_DAMAGE;
    charging = false;
    chargeDuration = 0;
    moveDuration = 0;
}

// updates the object
void Charger::Update(float deltaTime) {
    Entity::Update(deltaTime);
    if(charging) {
        chargeDuration = chargeDuration - 1;
    }
    red -= 1;
    moveDuration = moveDuration - 1;

}

// draws the object
void Charger::Render(SDL_Renderer* renderer) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x, point.y, radius, 255, 0, 0, 255);
}

// draws the object based on the camera's position
void Charger::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);

    static SDL_Surface* proj_surface = SDL_LoadBMP( "../resource/enemies/charger.bmp" );
    static SDL_Texture* proj_texture = SDL_CreateTextureFromSurface( renderer, proj_surface );

    SDL_SetTextureColorMod(proj_texture, 255, 255, 255);
    if(red > 0) {
        SDL_SetTextureColorMod(proj_texture, 255, 0, 0);
    }

    static SDL_Rect spriteTextures[4] = {
        {0, 0, 16, 16},
        {16, 0, 16, 16},
        {32, 0, 16, 16},
        {48, 0, 16, 16}
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

    SDL_Rect dst = { point.x - camX - 36, point.y - camY - 36, TILE_SIZE, TILE_SIZE };

    SDL_RenderCopyEx(renderer, proj_texture, &spriteTextures[frame], &dst, NULL, NULL, flip);

    // filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 255, 0, 0, 100);
}

// updates the ai based on the player's position
void Charger::UpdateAI(Rectangle phitbox) {

    if(deleteFlag == true){
        spawnBloodStain();
		deathSound(2);
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
    if((enemyCenter.x + CHARGER_SIZE/2 > playerCenter.x) && (enemyCenter.x - CHARGER_SIZE/2 < playerCenter.x)) {
        charging = true;
        soundList.push_back(SoundType::CHARGER_CHARGE);
        sounds = true;
        chargeDuration = CHARGER_CHARGEDURATION;
        moveDuration = 0;
        // charge direction
        if(enemyCenter.y < playerCenter.y){
            ySpeed = CHARGER_CHARGE_SPEED;
        }
        else {
            ySpeed = -CHARGER_CHARGE_SPEED;
        }
        xSpeed = 0;
        return;
    } 
    // check if the player is on the same y as the charger
    else if((enemyCenter.y + CHARGER_SIZE/2 > playerCenter.y) && (enemyCenter.y - CHARGER_SIZE/2 < playerCenter.y)) {
        charging = true;
        soundList.push_back(SoundType::CHARGER_CHARGE);
        sounds = true;
        chargeDuration = CHARGER_CHARGEDURATION;
        moveDuration = 0;
        // charge direction
        if(enemyCenter.x < playerCenter.x){
            xSpeed = CHARGER_CHARGE_SPEED;
        }
        else {
            xSpeed = -CHARGER_CHARGE_SPEED;
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
            xSpeed = CHARGER_SPEED;
            ySpeed = 0;
            break;
        // move left
        case 1:
            xSpeed = -CHARGER_SPEED;
            ySpeed = 0;
            break;
        // move down
        case 2:
            xSpeed = 0;
            ySpeed = CHARGER_SPEED;
            break;
        // move up
        case 3:
            xSpeed = 0;
            ySpeed = -CHARGER_SPEED;
            break;
        default:
            break;
    }
}
