#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include "gameProcess.h"
#include "bloodStain.h"


// constructor
BloodStain::BloodStain(int x, int y, int height, int width) : GameProcess() {
    hitbox.x = x;
    hitbox.y = y;
    hitbox.height = height;
    hitbox.width = width;
}

// draw the bloodstain
void BloodStain::Render(SDL_Renderer* renderer) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x, point.y, hitbox.height/1.5, 0, 200, 0, 200);
}

// draws the object based on the camera's position
void BloodStain::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x - camX, point.y - camY, hitbox.height/1.5, 0, 200, 0, 200);
}

// updates the object
void BloodStain::Update(float deltaTime) {
    
}

// handles the interactions with other objects
void BloodStain::handleInteractions(int tag) {

}