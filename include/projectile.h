/*#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameObject.h"


class Projectile : public GameObject {

    public:

        // constructor
        Projectile(int x, int y, float startXSpeed, float startYSpeed);

        // updates the object
        void Update(float deltaTime);

        // draws the object
        void Render(SDL_Renderer* renderer);

        // get the x position of the projectile
        int getXpos() const;

        // get the y position of the projectile
        int getYpos() const;

        // get the radius of the projectile (for collision detection)
        int getRadius() const;

        // get the damage the projectile causes to the player on contact
        int getDamage() const;

        // projectile collided with top/bottom of obstacle
        void bounceX(int newX);

        // projectile collided with right/left of obstacle
        void bounceY(int newY);

    protected:
        // the position of the projectile (center point)
        int xPos, yPos;

        // radius of the collision detection 
        int radius;
        
        // the speed of the projectile
        float xSpeed, ySpeed;

        // the damage the projectile causes to the player
        int damage;


};


#endif*/