#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include "gameProcess.h"
#include "deadSoldier.h"
#include <constants.h>
#include <iostream>


// constructor
DeadSoldier::DeadSoldier(int x, int y)  {
    hitbox.x = x;
    hitbox.y = y;
    hitbox.height = 10;
    hitbox.width = 10;
    damage = 0;
    soundPlayed = false;
    spriteNum = rand()%2 + 1;

    // randomize direction of sprite
    int flipDir = rand()%2 + 1;
    switch (flipDir) {
        case 1:
            flip = SDL_FLIP_NONE;
            break;
        case 2:
            flip = SDL_FLIP_HORIZONTAL;
            break;
        default:
            flip = SDL_FLIP_NONE;
            break;
    }

}
// draw the wall
void DeadSoldier::Render(SDL_Renderer* renderer) {
    //rectangleRGBA(renderer, hitbox.x, hitbox.y, hitbox.x + hitbox.width, hitbox.y + hitbox.height, 0, 100, 255, 255);
    RenderCam(renderer, 0, 0);
}

// updates the object
void DeadSoldier::Update(float deltaTime) {
}

// updates the ai based on the player's position
void DeadSoldier::UpdateAI(Rectangle phitbox) {
    // get center of hitboxes
    Point playerCenter = getCenter(&phitbox);
    Point enemyCenter = getCenter(&hitbox);

    // calculate vector
    float dx = playerCenter.x - enemyCenter.x;
    float dy = playerCenter.y - enemyCenter.y;

    // normalize
    float length = sqrt((dx * dx) + (dy * dy));

    if(length != 0) {
        dx = dx / length;
        dy = dy / length;
    }

    // if the player is close, play voice line
    if((length <= 300) && (soundPlayed == false)) {
        int val = rand()%6+1;
        switch (val) {
            case 1:
                soundList.push_back(SoundType::PLAYER_SAD1);
                break;
            case 2:
                soundList.push_back(SoundType::PLAYER_SAD2);
                break;
            case 3:
                soundList.push_back(SoundType::PLAYER_SAD3);
                break;
            case 4:
                soundList.push_back(SoundType::PLAYER_SAD4);
                break;
            case 5:
                soundList.push_back(SoundType::PLAYER_SAD5);
                break;
            case 6:
                soundList.push_back(SoundType::PLAYER_SAD6);	
        }
        sounds = true;
        soundPlayed = true;
        std::cout << "sound added" << std::endl;
    }
}

// draws the object based on the camera's position
void DeadSoldier::RenderCam(SDL_Renderer* renderer, int camX, int camY) {

    Point point = getCenter(&hitbox);

    switch (spriteNum) {
        case 1: {
            static SDL_Surface* body_surface = SDL_LoadBMP( "../resource/dead_soldier1.bmp" );
            static SDL_Texture* body_texture = SDL_CreateTextureFromSurface( renderer, body_surface );
            SDL_Rect dst = { point.x - camX - 32, point.y - camY - 32, TILE_SIZE, TILE_SIZE };
            SDL_RenderCopyEx(renderer, body_texture, NULL, &dst, NULL, NULL, flip);
            break;
        }
        case 2: {
            static SDL_Surface* body_surface = SDL_LoadBMP( "../resource/dead_soldier2.bmp" );
            static SDL_Texture* body_texture = SDL_CreateTextureFromSurface( renderer, body_surface );
            SDL_Rect dst = { point.x - camX - 32, point.y - camY - 32, TILE_SIZE * 2, TILE_SIZE * 2};
            SDL_RenderCopyEx(renderer, body_texture, NULL, &dst, NULL, NULL, flip);
            break;
        }
        default:
            return;
    }
}

// handles the interactions with other objects
void DeadSoldier::handleInteraction(std::string tag) {
}