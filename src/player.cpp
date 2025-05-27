#include <iostream>
#include <stdio.h>
#include "constants.h"
#include "player.h"

Player::Player() {
    velX = 0;
    velY = 0;
}

void Player::move(vector<vector<int>> tilemap_collision)
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
            if (tilemap_collision[x][y]) {
                if (checkCollision(x, y)) {
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

bool Player::checkCollision(int xs, int ys)
{
    int x = xs * TILE_SIZE;
    int y = ys * TILE_SIZE;
    
    // for circle/rect
    int cX, cY;
    if (posX < x - (TILE_SIZE / 2)) {
        cX = x - (TILE_SIZE / 2);
    }
    else if (posX > x + (TILE_SIZE / 2)) {
        cX = x + (TILE_SIZE / 2);
    }
    else {
        cX = posX;
    }
    if (posY < y - (TILE_SIZE / 2)) {
        cY = y - (TILE_SIZE / 2);
    }
    else if (posY > y + (TILE_SIZE / 2)) {
        cY = y + (TILE_SIZE / 2);
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
