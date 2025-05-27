#ifndef ENTITY_H
#define ENTITY_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include "gameProcess.h"

using namespace std;


class Entity : public GameProcess {

    public:

        // constructor
        Entity();
        
        // updates the object
        virtual void Update(float deltaTime) = 0;

        // draws the object
        virtual void Render(SDL_Renderer* renderer) = 0;

        // draws the object based on the camera's position
        virtual void RenderCam(SDL_Renderer* renderer, int camX, int camY) = 0;

        // gets the current health
        int getHealth() const;

        // subtracts the health damage from the current health
        virtual void adjustHealth(int healthDamage);

        // handles the interactions with other objects
        void handleInteraction(std::string tag) override;

        // spawns a bloodstain child process
        void spawnBloodStain();

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

        // spawns a bloodstain child process
        void spawnBloodStain(int color = 0);

        // how long the entity should be red for
        int red;

};


#endif