#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#include "enemy.h"
#include "alphaSpewer.h"
#include "spitterProjectile.h"
#include <constants.h>


// constructor
AlphaSpewer::AlphaSpewer(int x, int y) : Enemy(x, y) {

    health = ALPHASPEWER_HEALTH;
    radius = ALPHASPEWER_RADIUS;
    hitbox.height = ALPHASPEWER_SIZE;
    hitbox.width = ALPHASPEWER_SIZE;
    xSpeed = 0;
    ySpeed = 0;
    damage = ALPHASPEWER_DAMAGE;
    cooldown = ALPHASPEWER_COOLDOWN;
    spitSpeed = SPEWERPROJECTILE_SPEED + 2;
    projectileAmount = 0;
    spitInterval = 20;
}

// updates the object
void AlphaSpewer::Update(float deltaTime) {

    // check if the spewer is still spitting
    if(projectileAmount <= 0){
        Entity::Update(deltaTime);
        cooldown = cooldown - 1;
    }
    // time inbetween projectiles
    else if (spitInterval > 0){
        spitInterval = spitInterval - 1;
    }
    red -= 1;
}

// draws the object
void AlphaSpewer::Render(SDL_Renderer* renderer) {
    RenderCam(renderer, 0, 0);
}

// draws the object based on the camera's position
void AlphaSpewer::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);

    static SDL_Surface* proj_surface = SDL_LoadBMP( "../resource/enemies/a_spewer.bmp" );
    static SDL_Texture* proj_texture = SDL_CreateTextureFromSurface( renderer, proj_surface );

    SDL_SetTextureColorMod(proj_texture, 255, 255, 255);
    if(red > 0) {
        SDL_SetTextureColorMod(proj_texture, 255, 0, 0);
    }

    static SDL_Rect spriteTextures[4] = {
        {0, 0, 32, 32},
        {32, 0, 32, 32},
        {64, 0, 32, 32},
        {96, 0, 32, 32}
    };

    static const int total_frames = 4;
    static const int fps = 12;
    static int frame = 0;

    static Uint64 startTicks = SDL_GetTicks();

    Uint64 curTicks = SDL_GetTicks();
    float deltaTime = curTicks - startTicks;
    if (deltaTime > 1000 / fps) {
        if (xSpeed != 0 || ySpeed != 0) {
            frame = (frame + 1) % total_frames;
        }
        // use idle sprite
        else {
            frame = 0;
        }
        startTicks = curTicks;
    }

    static SDL_RendererFlip flip = SDL_FLIP_NONE;

    if (xSpeed < 0) {
        flip = SDL_FLIP_NONE;
    }
    if (xSpeed > 0) {
        flip = SDL_FLIP_HORIZONTAL;
    }

    SDL_Rect dst = { point.x - camX - 64, point.y - camY - 86, TILE_SIZE * 2, TILE_SIZE * 2 };

    SDL_RenderCopyEx(renderer, proj_texture, &spriteTextures[frame], &dst, NULL, NULL, flip);

    // filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 205, 92, 92, 100);
}

// updates the ai based on the player's position
void AlphaSpewer::UpdateAI(Rectangle phitbox) {

    if(deleteFlag == true){
        spawnBloodStain();
		deathSound(1);
    }

    if(cooldown <= 0){
        projectileAmount = ALPHASPEWER_PROJECTILE_NUMBER;
        cooldown = ALPHASPEWER_COOLDOWN;
    }
    // check if there are any projectiles left to spit, 
    // and if enough time has passed between the last spit
    if((projectileAmount > 0) && (spitInterval <= 0)) {
        spitProjectile(phitbox);
        spitInterval = ALPHASPEWER_SPIT_INTERVAL;

    }

    // get center of hitboxes
    Point playerCenter = getCenter(&phitbox);
    Point enemyCenter = getCenter(&hitbox);

    // calculate vector
    float dx = playerCenter.x - enemyCenter.x;
    float dy = playerCenter.y - enemyCenter.y;

    // normalize
    float length = sqrt((dx * dx) + (dy * dy));

    if(length != 0) {
        dx = dx / length;
        dy = dy / length;
    }

    // set the speed based on speed
    xSpeed = dx * ALPHASPEWER_SPEED;
    ySpeed = dy * ALPHASPEWER_SPEED;

    // if the player is too close, reverse
    if(length <= 300){
        xSpeed = -xSpeed;
        ySpeed = -ySpeed;
    }
    // buffer to stop stuttering when on the boundary of too close/far to player
    else if(length < 450){
        xSpeed = 0;
        ySpeed = 0;
    }
}

// creates a projectile object
void AlphaSpewer::spitProjectile(Rectangle phitbox) {

    
    // get center of hitboxes
    Point playerCenter = getCenter(&phitbox);
    Point enemyCenter = getCenter(&hitbox);

    // spawn explosion centered on the enemy
    int x = enemyCenter.x - (SPITTERPROJECTILE_SIZE / 2);
    int y = enemyCenter.y - (SPITTERPROJECTILE_SIZE / 2);

    // calculate random angle (2 - 10)
    int newDirection = (rand() % 9) + 2;

    // multiply to get more varied numbers
    newDirection = newDirection * 2;

    // negative angles
    if(rand() % 2 == 1){
        newDirection = -newDirection;
    }

    // calculate vector
    float dx = playerCenter.x - enemyCenter.x;
    float dy = playerCenter.y - enemyCenter.y;

    // normalize
    float length = sqrt((dx * dx) + (dy * dy));

    if(length != 0) {
        dx = dx / length;
        dy = dy / length;
    }

    // rotate 
    float angle = newDirection; 
    float radians = angle * (M_PI / 180.0f); 
    float cosAngle = cos(radians);
    float sinAngle = sin(radians);
    
    // Apply the rotation
    float rotatedDx = dx * cosAngle - dy * sinAngle;
    float rotatedDy = dx * sinAngle + dy * cosAngle;
    
    // Set the speed based on spitSpeed
    float projXspeed = rotatedDx * spitSpeed;
    float projYspeed = rotatedDy * spitSpeed;

    // create spit at SPEWER's location w/ calculated speeds
    SpitterProjectile* spit = new SpitterProjectile(x, y, projXspeed, projYspeed);

    childrenList.push_back(spit);
    
    // set the flag for child to true
    children = true;
    // decrement projectiles to shoot
    projectileAmount = projectileAmount - 1;

    // 8 way spit to catch player off guard
    if(projectileAmount == 1){
        /*
        spit = new SpitterProjectile(x, y, spitSpeed, spitSpeed);
        childrenList.push_back(spit);

        spit = new SpitterProjectile(x, y, -spitSpeed, spitSpeed);
        childrenList.push_back(spit);

        spit = new SpitterProjectile(x, y, -spitSpeed, -spitSpeed);
        childrenList.push_back(spit);

        spit = new SpitterProjectile(x, y, spitSpeed, -spitSpeed);
        childrenList.push_back(spit);

        // up, down, left, right

        spit = new SpitterProjectile(x, y, -spitSpeed, 0);
        childrenList.push_back(spit);

        spit = new SpitterProjectile(x, y, 0, -spitSpeed);
        childrenList.push_back(spit);

        spit = new SpitterProjectile(x, y, spitSpeed, 0);
        childrenList.push_back(spit);

        spit = new SpitterProjectile(x, y, 0, spitSpeed);
        childrenList.push_back(spit);*/

        int numProjectiles = 20; // Number of projectiles to fire in a circle
        float angleStep = 360.0f / numProjectiles;

        for (int i = 0; i < numProjectiles; ++i) {
            float angleDeg = i * angleStep;
            float angleRad = angleDeg * (M_PI / 180.0f); // Convert to radians

            float dx = cos(angleRad);
            float dy = sin(angleRad);

            float speed = spitSpeed;

            spit = new SpitterProjectile(x, y, dx * speed, dy * speed);
            childrenList.push_back(spit);
        }
    }
	
	// add sound for spitting
    soundList.push_back(SoundType::SPIT_LOW);
    sounds = true;
}



