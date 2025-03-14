#ifndef SPITTER_H
#define SPITTER_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#include <vector>
#include "enemy.h"
#include "projectile.h"

class Spitter : public Enemy {

    public:

        // constructor
        Spitter(int x, int y);

        // updates the object
        void Update(float deltaTime);

        // draws the object
        void Render(SDL_Renderer* renderer);

        // updates the ai based on the player's position
        void UpdateAI(Circle phitbox);



    private:

        // time inbetween spitting, time the spitter is stationary while spitting
        float cooldown, windup;

        // how fast the projectile will be
        float spitSpeed;

        // creates a projectile object
        void spitProjectile(Circle phitbox);





};


#endif