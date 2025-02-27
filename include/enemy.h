#ifndef ENEMY_H
#define ENEMY_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameObject.h"

class Enemy : public GameObject {

    public:

        // constructor
        Enemy(int x, int y);

        // updates the object
        virtual void Update(float deltaTime) = 0;

        // draws the object
        virtual void Render(SDL_Renderer* renderer) = 0;

        // updates the ai based on the player's position
        virtual void UpdateAI(int pX, int pY) = 0;

        // checks if the enemy is dead or alive
        bool isAlive() const;
        
        // damage the enemy and update alive status
        void takeDamage(int damage_taken);

        // get the x position of the enemy
        int getXpos() const;

        // get the y position of the enemy
        int getYpos() const;

        // get the radius of the enemy (for collision detection)
        int getRadius() const;

        // get the damage the enemy causes to the player on contact
        int getDamage() const;

    protected:
        // the position of the enemy (center point)
        int xPos, yPos;

        // radius of the collision detection 
        int radius;
        
        // the speed of the enemy
        float xSpeed, ySpeed;

        // health of the enemy
        int health;

        // the status of the enemy (alive/dead)
        bool alive;

        // the damage the enemy causes to the player
        int damage;


};


#endif