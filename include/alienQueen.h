#ifndef ALIENQUEEN_H
#define ALIENQUEEN_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#include <vector>
#include "enemy.h"
#include "projectile.h"
#include "enemyFactory.h"

class AlienQueen : public Enemy {

    public:

        // constructor
        AlienQueen(int x, int y);

        // updates the object
        void Update(float deltaTime);

        // draws the object
        void Render(SDL_Renderer* renderer);

        // draws the object based on the camera's position
        void RenderCam(SDL_Renderer* renderer, int camX, int camY);

        // updates the ai based on the player's position
        void UpdateAI(Rectangle phitbox);

    private:
        // the current phase of the queen. Determines attacks + behavior
        int phase;

        // cooldowns for various attacks
        float cooldown;
        float cooldown2;
        float chargeDuration;

        // how many projectiles will spawn in a spit phase
        int projectileAmount;

        // how long inbetween shooting projectiles
        int spitInterval;

        // how fast the projectile will be
        float spitSpeed;

        bool charging;

        SDL_Texture* texture;

        // shoot projectiles and spawn enemies. Stationary in center
        void phase1(Rectangle phitbox);

        void phase2(Rectangle phitbox);

        void phase3(Rectangle phitbox);

        // moves towards the player
        void moveToPlayer(Rectangle phitbox);

        // moves towards the player in straight line
        void charge(Rectangle phitbox);

        // creates a projectile object
        void spitProjectile(Rectangle phitbox);

        // creates n projectile objects in a circle. 
        void spitProjectileCircle(int numProj);

        void exploderCircle(int number);

        void enemyCircle(int number, EnemyFactory::EnemyType type);
};


#endif