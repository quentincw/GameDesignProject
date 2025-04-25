#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <string>
#include <vector>
#include "enemy.h"
#include "roach.h"
#include <constants.h>

// constructor
Roach::Roach(int x, int y) : Enemy(x, y) {

    health = ROACH_HEALTH;
    hitbox.height = ROACH_SIZE;
    hitbox.width = ROACH_SIZE;
    radius = ROACH_RADIUS;
    xSpeed = 0;
    ySpeed = 0;
    damage = ROACH_DAMAGE;
}

// updates the object
void Roach::Update(float deltaTime) {
    Entity::Update(deltaTime);
}

// draws the object
void Roach::Render(SDL_Renderer* renderer) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x, point.y, radius, 255, 0, 0, 255);
}

// draws the object based on the camera's position
void Roach::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);

    static SDL_Surface* proj_surface = SDL_LoadBMP( "../resource/enemies/roach.bmp" );
    static SDL_Texture* proj_texture = SDL_CreateTextureFromSurface( renderer, proj_surface );

    SDL_Rect dst = { point.x - camX - 32, point.y - camY - 50, TILE_SIZE, TILE_SIZE };

    SDL_RenderCopy(renderer, proj_texture, NULL, &dst);

    // filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 255, 0, 0, 100);
}

// updates the ai based on the player's position
void Roach::UpdateAI(Rectangle phitbox) {

    if(deleteFlag == true){
        spawnBloodStain();
		soundList.push_back(SoundType::BUG_DEATH1);
		sounds = true;
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
    xSpeed = dx * ROACH_SPEED;
    ySpeed = dy * ROACH_SPEED;
}
