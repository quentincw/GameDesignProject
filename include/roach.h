#ifndef ROACH_H
#define ROACH_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "enemy.h"

class Roach : public Enemy {

    public:

        // constructor
        Roach(int x, int y);

        // updates the object
        void Update(float deltaTime);

        // draws the object
        void Render(SDL_Renderer* renderer);

        // updates the ai based on the player's position
        void UpdateAI(Rectangle phitbox);

        // handles the interactions with other objects
        void handleInteractions(int tag);


};


#endif