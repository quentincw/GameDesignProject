#ifndef SPAWNER_H
#define SPAWNER_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#include <vector>
#include "enemy.h"

class Spawner : public Enemy {

    public:

        // constructor
        Spawner(int x, int y);

        // updates the object
        void Update(float deltaTime);

        // draws the object
        void Render(SDL_Renderer* renderer);

        // draws the object based on the camera's position
        void RenderCam(SDL_Renderer* renderer, int camX, int camY);

        // updates the ai based on the player's position
        void UpdateAI(Rectangle phitbox);

    private:

        // time inbetween spawning
        float cooldown;

        // creates a projectile object
        virtual void spawnEnemy();





};


#endif