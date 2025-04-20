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
    int tileX = posX / (TILE_SIZE / 2);
    int tileY = posY / (TILE_SIZE / 2);

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
    int x = xs * (TILE_SIZE / 2);
    int y = ys * (TILE_SIZE / 2);
    
    if (posX + rad < x) {
        return false;
    }
    if (posX - rad > x + (TILE_SIZE / 2)) {
        return false;
    }
    if (posY + rad < y) {
        return false;
    }
    if (posY - rad > y + (TILE_SIZE / 2)) {
        return false;
    }
    
    return true;
}
