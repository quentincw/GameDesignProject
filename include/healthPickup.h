#ifndef HEALTHPICKUP_H
#define HEALTHPICKUP_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "pickup.h"


class HealthPickup : public Pickup {

    public:

        // constructor
        HealthPickup(int x, int y);
        
        // constructor with stats
        HealthPickup(int x, int y, int health, int armor, int damage);

        // draws the object
        void Render(SDL_Renderer* renderer);

        // draws the object based on the camera's position
        void RenderCam(SDL_Renderer* renderer, int camX, int camY);

        // handles the interactions with other objects
        void handleInteraction(std::string tag) override;
};


#endif