#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"
#include "pickup.h"
#include "healthPickup.h"
#include <constants.h>

// default constructor
HealthPickup::HealthPickup(int x, int y) : Pickup(x, y) {
    hitbox.height = 30;
    hitbox.width = 30;
    damage = -20;
    interactions.insert("player");
}

// constructor
HealthPickup::HealthPickup(int x, int y, int health, int armor, int damage) : Pickup(x, y, health, armor, damage) {
    hitbox.height = 30;
    hitbox.width = 30;
    this->damage = damage;
    interactions.insert("player");
}

// draws the object
void HealthPickup::Render(SDL_Renderer* renderer) {
    int shortSide = hitbox.height/3;
    int longSide = hitbox.height;
    SDL_Rect rect;

    // vertical rectangle
    rect.x = hitbox.x + shortSide;
    rect.y = hitbox.y;
    rect.w = shortSide;
    rect.h = longSide;

    SDL_SetRenderDrawColor( renderer, 0, 255, 100, 255 );
    SDL_RenderFillRect( renderer, &rect );

    // horizontal rectangle
    rect.x = hitbox.x;
    rect.y = hitbox.y + shortSide;
    rect.w = longSide;
    rect.h = shortSide;

    SDL_SetRenderDrawColor( renderer, 0, 255, 100, 255 );
    SDL_RenderFillRect( renderer, &rect );

}

// draws the object based on the camera's position
void HealthPickup::RenderCam(SDL_Renderer* renderer, int camX, int camY) {

    int shortSide = hitbox.height/3;
    int longSide = hitbox.height;
    SDL_Rect rect;

    // vertical rectangle
    rect.x = hitbox.x + shortSide - camX;
    rect.y = hitbox.y - camY;
    rect.w = shortSide;
    rect.h = longSide;

    SDL_SetRenderDrawColor( renderer, 0, 255, 100, 255 );
    SDL_RenderFillRect( renderer, &rect );

    // horizontal rectangle
    rect.x = hitbox.x - camX;
    rect.y = hitbox.y + shortSide - camY;
    rect.w = longSide;
    rect.h = shortSide;

    SDL_SetRenderDrawColor( renderer, 0, 255, 100, 255 );
    SDL_RenderFillRect( renderer, &rect );

    static SDL_Surface* proj_surface = SDL_LoadBMP( "../resource/health.bmp" );
    static SDL_Texture* proj_texture = SDL_CreateTextureFromSurface( renderer, proj_surface );

    SDL_Rect dst = { static_cast<int>(hitbox.x - camX - 32), static_cast<int>(hitbox.y - camY - 32), TILE_SIZE, TILE_SIZE };

    SDL_RenderCopy(renderer, proj_texture, NULL, &dst);

}

// handles the interactions with other objects
void HealthPickup::handleInteraction(std::string tag) {
    if (tag == "player") {
        markForDeletion();
    }
}
