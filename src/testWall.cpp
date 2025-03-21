#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include <bits/stdc++.h>
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