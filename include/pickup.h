#ifndef PICKUP_H
#define PICKUP_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"

struct Stats {
    int health;
    int armor;
    int damage;
};


class Pickup : public GameProcess {

    public:

        // default constructor
        Pickup(int x, int y);

        // constructor with stats
        Pickup(int x, int y, int health, int armor, int damage);

        // updates the object
        void Update(float deltaTime);

        // draws the object
        virtual void Render(SDL_Renderer* renderer) = 0;

        // draws the object based on the camera's position
        virtual void RenderCam(SDL_Renderer* renderer, int camX, int camY) = 0;

        // get the stats associated with the pickup
        Stats getStats() const;

        // handles the interactions with other objects
        virtual void handleInteractions(int tag) = 0;

    protected:
        
        // the stats of the pickup
        Stats pickupStats;



};


#endif