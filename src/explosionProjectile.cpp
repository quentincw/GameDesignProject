#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"
#include "projectile.h"
#include "explosionProjectile.h"
#include "enemyConstants.h"

// constructor
ExplosionProjectile::ExplosionProjectile(int x, int y) : Projectile(x, y, 0, 0) {

    radius = EXPLOSIONPROJECTILE_RADIUS;
    damage = EXPLOSIONPROJECTILE_DAMAGE;
    hitbox.height = EXPLOSIONPROJECTILE_SIZE;
    hitbox.width = EXPLOSIONPROJECTILE_SIZE;
    lifeTime = EXPLOSIONPROJECTILE_LIFETIME;
    tags.push_back("Player");
}

// updates the object
void ExplosionProjectile::Update(float deltaTime) {
    hitbox.x = hitbox.x + xSpeed;
    hitbox.y = hitbox.y + ySpeed;

    // delete explosion if active for enough time
    
    lifeTime--;
    if(lifeTime < 0){
        markForDeletion();
    }
}

// draws the object
void ExplosionProjectile::Render(SDL_Renderer* renderer) {
    RenderCam(renderer, 0, 0);
}

// draws the object based on the camera's position
void ExplosionProjectile::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 255, 69, 0, 255);
}