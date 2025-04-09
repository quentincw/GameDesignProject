#ifndef ENEMY_H
#define ENEMY_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "entity.h"

class Enemy : public Entity {

    public:

        // constructor
        Enemy(int x, int y);

        // updates the object
        virtual void Update(float deltaTime) = 0;

        // draws the object
        virtual void Render(SDL_Renderer* renderer) = 0;

        // draws the object based on the camera's position
        virtual void RenderCam(SDL_Renderer* renderer, int camX, int camY) = 0;

        // updates the ai based on the player's position
        virtual void UpdateAI(Rectangle phitbox) = 0;

        // handles the interactions with other objects
        virtual void handleInteractions(std::string tag) = 0;
};


#endif