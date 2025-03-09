#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"


class Projectile : public GameProcess {

    public:

        // constructor
        Projectile(int x, int y, float startXSpeed, float startYSpeed);

        // updates the object
        void Update(float deltaTime);

        // draws the object
        void Render(SDL_Renderer* renderer);

        // get the circle representing the hitbox of the projectile
        Circle getHitbox() const;

        // get the damage the projectile causes to the player on contact
        int getDamage() const;

    protected:
        // the x,y, and radius of the projectile
        Circle hitbox;
        
        // the current speed of the projectile
        float xSpeed, ySpeed;

        // the damage the projectile causes to the player
        int damage;


};


#endif