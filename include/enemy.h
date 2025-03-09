/*#ifndef ENEMY_H
#define ENEMY_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "entity.h"

class Enemy : public Entity {

    public:

        // constructor
        Enemy(int x, int y);

        // updates the object
        virtual void Update(float deltaTime) = 0;

        // draws the object
        virtual void Render(SDL_Renderer* renderer) = 0;

        // updates the ai based on the player's position
        virtual void UpdateAI(int pX, int pY) = 0;

        int getDamage() const;

    protected:

        int damage;


};


#endif*/