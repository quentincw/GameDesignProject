#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include "gameObject.h"
#include "testWall.h"


// constructor
TestWall::TestWall(int x, int y, int height, int width)  {
    hitbox.x = x;
    hitbox.y = y;
    hitbox.height = height;
    hitbox.width = width;
}
// draw the wall
void TestWall::Render(SDL_Renderer* renderer) {
    rectangleRGBA(renderer, hitbox.x, hitbox.y, hitbox.x + hitbox.width, hitbox.y + hitbox.height, 0, 100, 255, 255);
}

// draws the object based on the camera's position
void TestWall::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    rectangleRGBA(renderer, hitbox.x - camX, hitbox.y - camY, hitbox.x - camX + hitbox.width, hitbox.y - camY + hitbox.height, 0, 100, 255, 255);
}