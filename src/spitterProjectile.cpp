#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"
#include "projectile.h"
#include "spitterProjectile.h"
#include <constants.h>

// constructor
SpitterProjectile::SpitterProjectile(int x, int y, float startXSpeed, float startYSpeed) : Projectile(x, y, startXSpeed, startYSpeed) {

    radius = 10;
    damage = 10;
    hitbox.height = 10;
    hitbox.width = 10;
    interactions.insert("player");
}

// updates the object
void SpitterProjectile::Update(float deltaTime) {
    Projectile::Update(deltaTime);
}

// draws the object
void SpitterProjectile::Render(SDL_Renderer* renderer) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x, point.y, radius, 0, 255, 0, 255);
}

// draws the object based on the camera's position
void SpitterProjectile::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);

    static SDL_Surface* proj_surface = SDL_LoadBMP( "../resource/enemy_projectile.bmp" );
    static SDL_Texture* proj_texture = SDL_CreateTextureFromSurface( renderer, proj_surface );

    SDL_Rect dst = { point.x - camX - 8, point.y - camY - 8, TILE_SIZE / 4, TILE_SIZE / 4 };

    SDL_RenderCopy(renderer, proj_texture, NULL, &dst);

    // filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 0, 255, 0, 100);
}