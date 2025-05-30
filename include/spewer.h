#ifndef SPEWER_H
#define SPEWER_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#include <vector>
#include "enemy.h"
#include "projectile.h"

class Spewer : public Enemy {

    public:

        // constructor
        Spewer(int x, int y);

        // updates the object
        void Update(float deltaTime);

        // draws the object
        void Render(SDL_Renderer* renderer);

        // draws the object based on the camera's position
        void RenderCam(SDL_Renderer* renderer, int camX, int camY);

        // updates the ai based on the player's position
        void UpdateAI(Rectangle phitbox);

    private:

        // time inbetween spitting, time the Spewer is stationary while spitting
        float cooldown, windup;

        // how fast the projectile will be
        float spitSpeed;

        // creates a projectile object
        void spitProjectile(Rectangle phitbox);





};


#endif