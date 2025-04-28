#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"
#include "projectile.h"
#include "playerProjectile.h"
#include <constants.h>

// constructor
PlayerProjectile::PlayerProjectile(int x, int y, float startXSpeed, float startYSpeed) : Projectile(x, y, startXSpeed, startYSpeed) {

    radius = 8;
    hitbox.height = 16;
    hitbox.width = 16;
    damage = 50;
    interactions.insert("enemy");
}

// updates the object
void PlayerProjectile::Update(float deltaTime) {
    Projectile::Update(deltaTime);
}

// draws the object
void PlayerProjectile::Render(SDL_Renderer* renderer) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x, point.y, radius, 0, 0, 255, 255);
}

// draws the object based on the camera's position
void PlayerProjectile::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);

    static SDL_Surface* proj_surface = SDL_LoadBMP( "../resource/projectile.bmp" );
    static SDL_Texture* proj_texture = SDL_CreateTextureFromSurface( renderer, proj_surface );

    SDL_Rect dst = { point.x - camX - 8, point.y - camY - 8, TILE_SIZE / 4, TILE_SIZE / 4 };

    SDL_RenderCopy(renderer, proj_texture, NULL, &dst);

    // filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 0, 0, 255, 100);
}

// projectile collided with top/bottom of obstacle
void PlayerProjectile::bounceX(int newX){
    xSpeed = -xSpeed;
    hitbox.x = newX;
}

// projectile collided with right/left of obstacle
void PlayerProjectile::bounceY(int newY){
    ySpeed = -ySpeed;
    hitbox.y = newY;
}