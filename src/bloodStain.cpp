#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include "gameProcess.h"
#include "bloodStain.h"
#include <constants.h>
#include <random>
using namespace std;


// constructor
BloodStain::BloodStain(int x, int y, int height, int width, int type) : GameProcess() {
    hitbox.x = x;
    hitbox.y = y;
    hitbox.height = height;
    hitbox.width = width;

    color = type;

    lastX = x;
    lastY = y;

    random_device rd;  // get random number
    mt19937 eng(rd()); // seed
    uniform_int_distribution<> distr(0, 6); // Define the range
    currentSpriteIndex = distr(eng);
}

// draw the bloodstain
void BloodStain::Render(SDL_Renderer* renderer) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x, point.y, hitbox.height/1.5, 0, 200, 0, 200);
}

// draws the object based on the camera's position
void BloodStain::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);

    static SDL_Surface* blood_surface = SDL_LoadBMP( "../resource/blood.bmp" );
    static SDL_Texture* blood_texture = SDL_CreateTextureFromSurface( renderer, blood_surface );

    // change to green if alien blood
    if(color == 0){
        SDL_SetTextureColorMod(blood_texture, 0, 255, 0);
    }
    else {
        SDL_SetTextureColorMod(blood_texture, 255, 255, 255);
    }

    SDL_Rect dst = { point.x - camX - (TILE_SIZE / 2), point.y - camY - (TILE_SIZE / 2), TILE_SIZE, TILE_SIZE };

    static SDL_Rect redTextures[7] = {
        {0, 0, 16, 16},
        {16, 0, 16, 16},
        {32, 0, 16, 16},
        {48, 0, 16, 16},
        {64, 0, 16, 16},
        {80, 0, 16, 16},
        {96, 0, 16, 16}
    };

    static SDL_Rect greenTextures[7] = {
        {0, 16, 16, 16},
        {16, 16, 16, 16},
        {32, 16, 16, 16},
        {48, 16, 16, 16},
        {64, 16, 16, 16},
        {80, 16, 16, 16},
        {96, 16, 16, 16}
    };

    if (color == 1) {
    SDL_RenderCopy(renderer, blood_texture, &redTextures[currentSpriteIndex], &dst);
    }
    else {
        SDL_RenderCopy(renderer, blood_texture, &greenTextures[currentSpriteIndex], &dst);
    }
}

// updates the object
void BloodStain::Update(float deltaTime) {
    
}

// handles the interactions with other objects
void BloodStain::handleInteractions(int tag) {

}