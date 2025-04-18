#ifndef CHARGER_H
#define CHARGER_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "enemy.h"

class Charger : public Enemy {

    public:

        // constructor
        Charger(int x, int y);

        // updates the object
        void Update(float deltaTime);

        // draws the object
        void Render(SDL_Renderer* renderer);

        // draws the object based on the camera's position
        void RenderCam(SDL_Renderer* renderer, int camX, int camY);

        // updates the ai based on the player's position
        void UpdateAI(Rectangle phitbox);

    protected:

        // boolean for identifying which state the charger is in
        bool charging;

        // how long the charger should charge for
        int chargeDuration;

        // how long the charger should move in one direction before turning
        int moveDuration;
};


#endif