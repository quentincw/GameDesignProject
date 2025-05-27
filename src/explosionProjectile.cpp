#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"
#include "projectile.h"
#include "explosionProjectile.h"
#include "enemyConstants.h"
#include <constants.h>

// constructor
ExplosionProjectile::ExplosionProjectile(int x, int y) : Projectile(x, y, 0, 0) {

    radius = EXPLOSIONPROJECTILE_RADIUS;
    damage = EXPLOSIONPROJECTILE_DAMAGE;
    hitbox.height = EXPLOSIONPROJECTILE_SIZE;
    hitbox.width = EXPLOSIONPROJECTILE_SIZE;
    lifeTime = EXPLOSIONPROJECTILE_LIFETIME;
    interactions.insert("player");
    interactions.insert("enemy");
}

// updates the object
void ExplosionProjectile::Update(float deltaTime) {
    Projectile::Update(deltaTime);

    // delete explosion if active for enough time
    
    lifeTime--;
    if(lifeTime < 0){
        markForDeletion();
    }
    // only damage enemies/ player for 3 frames
    if(lifeTime < EXPLOSIONPROJECTILE_LIFETIME - 2) {
        interactions.clear();
    }
}

// draws the object
void ExplosionProjectile::Render(SDL_Renderer* renderer) {
    RenderCam(renderer, 0, 0);
}

// draws the object based on the camera's position
void ExplosionProjectile::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);

    static SDL_Surface* proj_surface = SDL_LoadBMP( "../resource/explosion.bmp" );
    static SDL_Texture* proj_texture = SDL_CreateTextureFromSurface( renderer, proj_surface );

    SDL_Rect dst = { point.x - camX - 32, point.y - camY - 32, TILE_SIZE, TILE_SIZE };

    SDL_RenderCopy(renderer, proj_texture, NULL, &dst);

    // filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 255, 69, 0, 100);
}
void ExplosionProjectile::handleInteraction(std::string tag) {}