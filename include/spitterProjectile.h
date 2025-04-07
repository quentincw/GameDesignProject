#ifndef SPITTER_PROJECTILE_H
#define SPITTER_PROJECTILE_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "projectile.h"


class SpitterProjectile : public Projectile {

    public:

        // constructor
        SpitterProjectile(int x, int y, float startXSpeed, float startYSpeed);

        // updates the object
        void Update(float deltaTime);

        // draws the object
        void Render(SDL_Renderer* renderer);

        // draws the object based on the camera's position
        void RenderCam(SDL_Renderer* renderer, int camX, int camY);

        // handles the interactions with other objects
        void handleInteractions(int tag);

};


#endif