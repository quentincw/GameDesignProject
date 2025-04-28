#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"
#include "projectile.h"
#include "spitterProjectile.h"

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
    filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 0, 255, 0, 255);
}