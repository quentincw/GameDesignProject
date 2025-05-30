#ifndef PLAYER_PROJECTILE_H
#define PLAYER_PROJECTILE_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "projectile.h"


class PlayerProjectile : public Projectile {

    public:

        // constructor
        PlayerProjectile(int x, int y, float startXSpeed, float startYSpeed);

        // updates the object
        void Update(float deltaTime);

        // draws the object
        void Render(SDL_Renderer* renderer);

        // draws the object based on the camera's position
        void RenderCam(SDL_Renderer* renderer, int camX, int camY);

        void bounceX(int newX);

        void bounceY(int newY);
};


#endif