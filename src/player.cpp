#include <iostream>
#include <stdio.h>
#include "constants.h"
#include "player.h"

Player::Player() {
    posX = SCREEN_WIDTH / 2;
    posY = SCREEN_HEIGHT / 2;
    velX = 0;
    velY = 0;
}

void Player::move(vector<vector<vector<SDL_Rect>>> tilemap_collision)
{
    posX += velX;
    posY += velY;
    for (int x = 0; x < tilemap_collision.size(); x++) {
        for (int y = 0; y < tilemap_collision[x].size(); y++) {
            for (SDL_Rect wall: tilemap_collision[x][y]) {
                if (checkCollision(wall)) {
                    posX -= velX;
                    posY -= velY;
                }
            }
        }
    }
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

    // bottom a <= top b
    // if (a.y + a.h <= b.y) {
    //     return false;
    // }
    // // top a >= bottom b
    // if (a.y >= b.y + b.h) {
    //     return false;
    // }
    // // right a <= left b
    // if (a.x + a.w <= b.x) {
    //     return false;
    // }
    // // left a >= right b
    // if (a.x >= b.x + b.w) {
    //     return false;
    // }
    // return true;
}
