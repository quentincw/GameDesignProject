#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"
#include "projectile.h"
#include "playerProjectile.h"
#include <constants.h>

// constructor
PlayerProjectile::PlayerProjectile(int x, int y, float startXSpeed, float startYSpeed) : Projectile(x, y, startXSpeed, startYSpeed) {

    radius = 15;
    hitbox.height = 30;
    hitbox.width = 30;
    damage = 10;
    interactions.insert("enemy");
}

// updates the object
void PlayerProjectile::Update(float deltaTime) {
    hitbox.x = hitbox.x + xSpeed;
    hitbox.y = hitbox.y + ySpeed;
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

    SDL_Rect dst = { point.x - camX - (TILE_SIZE / 4), point.y - camY - (TILE_SIZE / 4), TILE_SIZE / 2, TILE_SIZE / 2 };

    SDL_RenderCopy(renderer, proj_texture, NULL, &dst);
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