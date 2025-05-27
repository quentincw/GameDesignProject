#ifndef EXPLOSION_PROJECTILE_H
#define EXPLOSION_PROJECTILE_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "projectile.h"


class ExplosionProjectile : public Projectile {

    public:

        // constructor
        ExplosionProjectile(int x, int y);

        // updates the object
        void Update(float deltaTime);

        // draws the object
        void Render(SDL_Renderer* renderer);

        // draws the object based on the camera's position
        void RenderCam(SDL_Renderer* renderer, int camX, int camY);

        // handles the interactions with other objects
        void handleInteraction(std::string tag) override;
    
    protected:

        // how long the explosion should last before disappearing
        int lifeTime;

};


#endif