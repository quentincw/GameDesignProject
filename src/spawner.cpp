#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#include "enemy.h"
#include "spawner.h"
#include "roach.h"
#include <constants.h>


// constructor
Spawner::Spawner(int x, int y) : Enemy(x, y) {

    health = SPAWNER_HEALTH;
    radius = SPAWNER_RADIUS;
    hitbox.height = SPAWNER_SIZE;
    hitbox.width = SPAWNER_SIZE;
    xSpeed = 0;
    ySpeed = 0;
    damage = SPAWNER_DAMAGE;
    cooldown = SPAWNER_COOLDOWN;
}

// updates the object
void Spawner::Update(float deltaTime) {
    Entity::Update(deltaTime);
    cooldown = cooldown - 1;
    red -= 1;
}

// draws the object
void Spawner::Render(SDL_Renderer* renderer) {
    RenderCam(renderer, 0, 0);
}

// draws the object based on the camera's position
void Spawner::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);

    static SDL_Surface* proj_surface = SDL_LoadBMP( "../resource/enemies/spawner.bmp" );
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

    SDL_Rect dst = { point.x - camX - 32, point.y - camY - 40, TILE_SIZE, TILE_SIZE };

    SDL_RenderCopyEx(renderer, proj_texture, &spriteTextures[frame], &dst, NULL, NULL, flip);

    // filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 128, 128, 0, 100);
}

// updates the ai based on the player's position
void Spawner::UpdateAI(Rectangle phitbox) {

    if(deleteFlag == true){
        spawnBloodStain();
		soundList.push_back(SoundType::BUG_DEATH1);
		sounds = true;
    }

    if(cooldown <= 0){
        spawnEnemy();
        cooldown = SPAWNER_COOLDOWN;
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
    xSpeed = dx * SPAWNER_SPEED;
    ySpeed = dy * SPAWNER_SPEED;

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

    // get the center of the enemy
    Point center = getCenter(&hitbox);

    // spawn raoch centered on the enemy
    int x = center.x - (ROACH_SIZE / 2);
    int y = center.y - (ROACH_SIZE / 2);
   
    Roach* roach = new Roach(x, y);
    // put roach in childrenList
    childrenList.push_back(roach);

    
    // set the flag for child to true
    children = true;
}
