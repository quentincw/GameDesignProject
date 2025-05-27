#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"


class Projectile : public GameProcess {

    public:

        // constructor
        Projectile(int x, int y, float startXSpeed, float startYSpeed);

        // updates the object
        virtual void Update(float deltaTime) = 0;

        // draws the object
        virtual void Render(SDL_Renderer* renderer) = 0;

        // draws the object based on the camera's position
        virtual void RenderCam(SDL_Renderer* renderer, int camX, int camY) = 0;

        // handles the interactions with other objects
        void handleInteraction(std::string tag) override;

    protected:
        
        // the current speed of the projectile
        float xSpeed, ySpeed;
};


#endif