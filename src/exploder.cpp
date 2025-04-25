#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#include "enemy.h"
#include "exploder.h"
#include "explosionProjectile.h"
#include <constants.h>


// constructor
Exploder::Exploder(int x, int y) : Enemy(x, y) {

    health = EXPLODER_HEALTH;
    radius = EXPLODER_RADIUS;
    hitbox.height = EXPLODER_SIZE;
    hitbox.width = EXPLODER_SIZE;
    xSpeed = 0;
    ySpeed = 0;
    damage = EXPLODER_DAMAGE;
}

// updates the object
void Exploder::Update(float deltaTime) {
    Entity::Update(deltaTime);
}

// draws the object
void Exploder::Render(SDL_Renderer* renderer) {
    RenderCam(renderer, 0,0);
}

// draws the object based on the camera's position
void Exploder::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);

    static SDL_Surface* proj_surface = SDL_LoadBMP( "../resource/enemies/exploder.bmp" );
    static SDL_Texture* proj_texture = SDL_CreateTextureFromSurface( renderer, proj_surface );

    SDL_Rect dst = { point.x - camX - 32, point.y - camY - 44, TILE_SIZE, TILE_SIZE };

    SDL_RenderCopy(renderer, proj_texture, NULL, &dst);

    // filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 139, 0, 0, 100);
}

// updates the ai based on the player's position
void Exploder::UpdateAI(Rectangle phitbox) {

    if(deleteFlag == true){
        spawnBloodStain();
        //explode();
    }

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
    xSpeed = dx * EXPLODER_SPEED;
    ySpeed = dy * EXPLODER_SPEED;

    // if the player is close, then blow up
    if(length <= 50){
        spawnBloodStain();
        explode();
        markForDeletion();
    }
}

// creates a projectile object
void Exploder::explode() {

    // create explosion at exploder's location

    // get the center of the enemy
    Point center = getCenter(&hitbox);

    // spawn explosion centered on the enemy
    int x = center.x - (EXPLOSIONPROJECTILE_SIZE / 2);
    int y = center.y - (EXPLOSIONPROJECTILE_SIZE / 2);

    ExplosionProjectile* boom = new ExplosionProjectile(x, y);

    childrenList.push_back(boom);
    
    // set the flag for child to true
    children = true;
}
