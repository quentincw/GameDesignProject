/*#ifndef ENTITY_H
#define ENTITY_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include "process.h"

using namespace std;

struct Circle {
    int x;
    int y;
    int radius;
};


class Entity : public Process {

    public:

        // constructor
        Entity();
        
        // updates the object
        virtual void Update(float deltaTime) = 0;

        // draws the object
        virtual void Render(SDL_Renderer* renderer) = 0;

        // gets the current health
        int getHealth() const;

        // subtracts the health damage from the current health
        void adjustHealth(int healthDamage);

        // gets the circle of the entity
        Circle getHitbox() const;



    protected:

        // current health
        int health;

        // maximum health
        int maxHealth;

        // flag for whether the entity is alive or dead
        bool isAlive;

        // maximum speed
        float speed;

        // the speed of the entity
        float xSpeed, ySpeed;

        // the circle hitbox of the entity
        Circle hitbox;


};


#endif*/