#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <string>
#include <vector>
#include "enemy.h"
#include "burrower.h"
#include "spitterProjectile.h"
#include <constants.h>


// constructor
Burrower::Burrower(int x, int y) : Enemy(x, y) {

    health = BURROWER_HEALTH;
    hitbox.height = BURROWER_SIZE;
    hitbox.width = BURROWER_SIZE;
    radius = BURROWER_RADIUS;
    xSpeed = 0;
    ySpeed = 0;
    damage = BURROWER_DAMAGE;
    burrowing = false;
    burrowDuration = 0;
    moveDuration = 0;
    spitAmount = 4;
    cooldown = 100;
    spitSpeed = 4;
}

// updates the object
void Burrower::Update(float deltaTime) {
    Entity::Update(deltaTime);
    if(burrowing) {
        burrowDuration = burrowDuration - 1;
        interactions.erase("player");
        tags.erase("enemy");
    }
    else {
        cooldown = cooldown - 1;
        interactions.insert("player");
        tags.insert("enemy");
    }

    moveDuration = moveDuration - 1;
}

// draws the object
void Burrower::Render(SDL_Renderer* renderer) {
    RenderCam(renderer, 0, 0);
}

// draws the object based on the camera's position
void Burrower::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    // don't render if underground
    if(burrowing){
        return;
    }
    Point point = getCenter(&hitbox);

    static SDL_Surface* proj_surface = SDL_LoadBMP( "../resource/enemies/burrower.bmp" );
    static SDL_Texture* proj_texture = SDL_CreateTextureFromSurface( renderer, proj_surface );

    SDL_Rect dst = { point.x - camX - 32, point.y - camY - 50, TILE_SIZE, TILE_SIZE };

    SDL_RenderCopy(renderer, proj_texture, NULL, &dst);
    
    // filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 139, 69, 19, 100);
}

// updates the ai based on the player's position
void Burrower::UpdateAI(Rectangle phitbox) {

    if(deleteFlag == true){
        spawnBloodStain();
		deathSound(3);
    }

    // stop burrowing if enough time has passed
    if((burrowing == true) && (burrowDuration <= 0)){
        burrowing = false;
		soundList.push_back(SoundType::BURROWER_DIG);
		sounds = true;
        // pause to give player time to react
        cooldown = 30;
        spitAmount = 3;
    }

    // if the BURROWER is not burrowing, don't move
    if(burrowing == false){
        xSpeed = 0;
        ySpeed = 0;
        // shoot projectile if cooldown available
        if(cooldown <= 0){
            // burrow if all projectiles have been fired and cooldown ready
            if(spitAmount <= 0) {
                burrowing = true;
				soundList.push_back(SoundType::BURROWER_DIG);
				sounds = true;
                burrowDuration = 170;
            }
            // if the burrower has fired less than 3 projectiles
            else if(spitAmount > 0) {
                spitProjectile(phitbox);
                cooldown = 8;
                spitAmount = spitAmount - 1;
                // the burrower should remain exposed for a time
                if (spitAmount == 0) {
                    cooldown = 100;
                }
            }
        }
        return;
    }

    // BURROWER is underground
    // pick random direction and move in that direction for a duration

    // if the BURROWER is moving, don't change direction
    if(moveDuration > 0){
        return;
    }

    moveDuration = 50;

    int newDirection = rand() % 4;
    switch (newDirection) {
        // move right
        case 0:
            xSpeed = BURROWER_SPEED;
            ySpeed = 0;
            break;
        // move left
        case 1:
            xSpeed = -BURROWER_SPEED;
            ySpeed = 0;
            break;
        // move down
        case 2:
            xSpeed = 0;
            ySpeed = BURROWER_SPEED;
            break;
        // move up
        case 3:
            xSpeed = 0;
            ySpeed = -BURROWER_SPEED;
            break;
        default:
            break;
    }
}

// creates a projectile object
void Burrower::spitProjectile(Rectangle phitbox) {


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

    // set the speed based on spitSpeed
    float projXspeed = dx * spitSpeed;
    float projYspeed = dy * spitSpeed;

    // spawn explosion centered on the enemy
    int x = enemyCenter.x - (SPITTERPROJECTILE_SIZE / 2);
    int y = enemyCenter.y - (SPITTERPROJECTILE_SIZE / 2);

    // create spit at burrower's location w/ calculated speeds
    SpitterProjectile* spit = new SpitterProjectile(x, y, projXspeed, projYspeed);

    // put spit in childrenList
    childrenList.push_back(spit);

    
    // set the flag for child to true
    children = true;
	
    // add sound for spitting
    soundList.push_back(SoundType::SPIT_HIGH);
    sounds = true;
}
