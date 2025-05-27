#ifndef BURROWER_H
#define BURROWER_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "enemy.h"

class Burrower : public Enemy {

    public:

        // constructor
        Burrower(int x, int y);

        // updates the object
        void Update(float deltaTime);

        // draws the object
        void Render(SDL_Renderer* renderer);

        // draws the object based on the camera's position
        void RenderCam(SDL_Renderer* renderer, int camX, int camY);

        // updates the ai based on the player's position
        void UpdateAI(Rectangle phitbox);

    protected:

        // boolean for identifying which state the burrower is in
        bool burrowing;

        // how long the burrower should be immune for
        int burrowDuration;

        // how long the burrower should move in one direction before turning
        int moveDuration;

        // time between shooting projectiles
        int cooldown;

        // how many projectiles to shoot before burrowing again
        int spitAmount;

        // how fast the projectiles will be
        float spitSpeed;
        
        // creates a projectile object
        void spitProjectile(Rectangle phitbox);
};


#endif