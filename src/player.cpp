#include <iostream>
#include <stdio.h>
#include "constants.h"
#include "player.h"

Player::Player() {
    velX = 0;
    velY = 0;
}

void Player::move(vector<vector<vector<SDL_Rect>>> tilemap_collision)
{
    posX += velX;
    posY += velY;

    // check collisions with x tiles
    int tileRange = 2;

    // tile coordinates of the player's position
    int tileX = posX / TILE_SIZE;
    int tileY = posY / TILE_SIZE;

    // limit tileRange such that it does not reach out of bounds
    for (int x = max(0, tileX - tileRange); x < min(int(tilemap_collision.size()), tileX + tileRange); x++) {
        for (int y = max(0, tileY - tileRange); y < min(int(tilemap_collision[x].size()), tileY + tileRange); y++) {
            for (SDL_Rect wall: tilemap_collision[x][y]) {
                if (checkCollision(wall)) {
                    posX -= velX;
                    posY -= velY;
                }
            }
        }
    }
}

void Player::setPos(int x, int y)
{
    posX = x;
    posY = y;
}

void Player::setMouse(float x, float y)
{
 	float Vx = x - xPos;
 	float Vy = y - yPos;
 	float mag = sqrt(pow(Vx,2) + pow(Vy,2));
 	weaponX = Vx / mag;
 	weaponY = Vy / mag;
}

vector<int> Player::getPos()
{
    return vector<int>{posX, posY};
}

void Player::setVelX(int x)
{
    if (x < 0) {
        velX = -5;
    }
    if (x > 0) {
        velX = 5;
    }
    if (x == 0) {
        velX = 0;
    }
}

void Player::setVelY(int y)
{
    if (y < 0) {
        velY = -5;
    }
    if (y > 0) {
        velY = 5;
    }
    if (y == 0) {
        velY = 0;
    }
}

bool Player::checkCollision(SDL_Rect rect)
{
    // for circle/rect
    int cX, cY;
    if (posX < rect.x) {
        cX = rect.x;
    }
    else if (posX > rect.x + rect.w) {
        cX = rect.x + rect.w;
    }
    else {
        cX = posX;
    }
    if (posY < rect.y) {
        cY = rect.y;
    }
    else if (posY > rect.y + rect.h) {
        cY = rect.y + rect.h;
    }
    else {
        cY = posY;
    }

    int deltaX = cX - posX;
    int deltaY = cY - posY;
    if (deltaX * deltaX + deltaY * deltaY < rad * rad) {
        return true;
    }
    return false;
}

void Player::update(float deltaMS)
{
     xPos += xMove;
     yPos += yMove;
}
