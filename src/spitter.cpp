#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#include "enemy.h"
#include "spitter.h"
#include "spitterProjectile.h"
#include <constants.h>

// constructor
Spitter::Spitter(int x, int y) : Enemy(x, y) {

    health = SPITTER_HEALTH;
    radius = SPITTER_RADIUS;
    hitbox.height = SPITTER_SIZE;
    hitbox.width = SPITTER_SIZE;
    xSpeed = 0;
    ySpeed = 0;
    damage = SPITTER_DAMAGE;
    cooldown = SPITTER_COOLDOWN;
    spitSpeed = SPITTERPROJECTILE_SPEED;
}

// updates the object
void Spitter::Update(float deltaTime) {
    Entity::Update(deltaTime);
    cooldown = cooldown - 1;
}

// draws the object
void Spitter::Render(SDL_Renderer* renderer) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x, point.y, radius, 255, 255, 0, 255);
}

// draws the object based on the camera's position
void Spitter::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);

    static SDL_Surface* proj_surface = SDL_LoadBMP( "../resource/enemies/spitter.bmp" );
    static SDL_Texture* proj_texture = SDL_CreateTextureFromSurface( renderer, proj_surface );

    SDL_Rect dst = { point.x - camX - 32, point.y - camY - 46, TILE_SIZE, TILE_SIZE };

    SDL_RenderCopy(renderer, proj_texture, NULL, &dst);

    // filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 255, 255, 0, 100);
}

// updates the ai based on the player's position
void Spitter::UpdateAI(Rectangle phitbox) {

    if(deleteFlag == true){
        spawnBloodStain();
		soundList.push_back(SoundType::BUG_DEATH1);
		sounds = true;
    }

    if(cooldown <= 0){
        spitProjectile(phitbox);
        cooldown = SPITTER_COOLDOWN;
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
    xSpeed = dx * SPITTER_SPEED;
    ySpeed = dy * SPITTER_SPEED;

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
void Spitter::spitProjectile(Rectangle phitbox) {


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

    // spawn explosion centered on the enemy
    int x = enemyCenter.x - (SPITTERPROJECTILE_SIZE / 2);
    int y = enemyCenter.y - (SPITTERPROJECTILE_SIZE / 2);

    // create spit at spitter's location w/ calculated speeds
    //SpitterProjectile spit(hitbox.x, hitbox.y, projXspeed, projYspeed);
    SpitterProjectile* spit = new SpitterProjectile(x, y, projXspeed, projYspeed);
    //child = spit;
    // put spit in childrenList
    //childrenList.clear();
    childrenList.push_back(spit);

    
    // set the flag for child to true
    children = true;

    // add sound for spitting
    soundList.push_back(SoundType::SPIT_HIGH);
    sounds = true;
}
