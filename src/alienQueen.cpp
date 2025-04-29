#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#include "enemy.h"
#include "alienQueen.h"
#include "spitterProjectile.h"
#include "exploder.h"
#include "roach.h"
#include "spitter.h"
#include "enemyFactory.h"
#include <constants.h>

// constructor
AlienQueen::AlienQueen(int x, int y) : Enemy(x, y) {

    health = 3000;
    radius = 75;
    hitbox.height = 150;
    hitbox.width = 150;
    xSpeed = 0;
    ySpeed = 0;
    damage = ALPHASPEWER_DAMAGE;
    cooldown = 100;
    cooldown2 = 435;
    spitSpeed = SPEWERPROJECTILE_SPEED + 2;
    projectileAmount = 0;
    spitInterval = 20;
    phase = 1;
    charging = false;
    chargeDuration = 0;
}

// updates the object
void AlienQueen::Update(float deltaTime) {

    // check if the spewer is still spitting
    Entity::Update(deltaTime);
    cooldown = cooldown - 1;
    cooldown2 = cooldown2 - 1;
    if(charging) {
        chargeDuration = chargeDuration - 1;
    }

}

// draws the object
void AlienQueen::Render(SDL_Renderer* renderer) {
    RenderCam(renderer, 0, 0);
}

// draws the object based on the camera's position
void AlienQueen::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);

    static SDL_Surface* proj_surface = SDL_LoadBMP( "../resource/enemies/queen_1.bmp" );
    static SDL_Surface* proj_surface_2 = SDL_LoadBMP( "../resource/enemies/queen_2.bmp" );
    static SDL_Texture* proj_texture = SDL_CreateTextureFromSurface( renderer, proj_surface );
    static SDL_Texture* proj_texture_2 = SDL_CreateTextureFromSurface( renderer, proj_surface_2 );

    if (phase == 1) {
        texture = proj_texture;
    }
    if (phase == 2) {
        texture = proj_texture_2;
    }

    static SDL_RendererFlip flip = SDL_FLIP_NONE;

    if (xSpeed < 0) {
        flip = SDL_FLIP_NONE;
    }
    if (xSpeed > 0) {
        flip = SDL_FLIP_HORIZONTAL;
    }

    SDL_Rect dst = { point.x - camX - 96, point.y - camY - 96, TILE_SIZE * 3, TILE_SIZE * 3 };

    SDL_RenderCopyEx(renderer, texture, NULL, &dst, NULL, NULL, flip);

    // filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 120, 30, 92, 100);
}

// updates the ai based on the player's position
void AlienQueen::UpdateAI(Rectangle phitbox) {

    // code for determining switching phase
    // if health = 70% -> phase 2
    if((health <= 2000) && (phase == 1)) {
        phase = 2;
        cooldown = 200;
        cooldown2 = 435;
    }
    // if health = 35% -> phase 3

    switch (phase) {
        case 1:
            phase1(phitbox);
            break;
        case 2:
            phase2(phitbox);
            break;
        case 3:
            phase3(phitbox);
            break;
    default:
        break;
    }
    
    if(deleteFlag == true){
        spawnBloodStain();
		soundList.push_back(SoundType::BUG_DEATH1);
		sounds = true;
    }
}

void AlienQueen::phase1(Rectangle phitbox){
    // cooldown 1: spit projectiles in circles

    // check if ready to spit
    if (cooldown <= 0) {
        if (projectileAmount <= 0) {
            // done spitting
            projectileAmount = 5;
            cooldown = 200;
        }
        else {
            // spit
            spitProjectileCircle(20 - projectileAmount);
            projectileAmount--;
            cooldown = 10;
        }
    }
    // cooldown 2: spawn exploders in a circle
    if (cooldown2 <= 0) {
        enemyCircle(6, EnemyFactory::EnemyType::EXPLODER);
        cooldown2 = 435;
    }


}

// hover near player and charge multiple times in quick succession
void AlienQueen::phase2(Rectangle phitbox){

    if(chargeDuration > 0){
        return;
    }

    if((chargeDuration < 0) && (charging == true)){
        spitProjectileCircle(20);
        charging = false;
    }

    moveToPlayer(phitbox);

    // cooldown 1 = charge
    if (cooldown <= 0) {
        charge(phitbox);
    }

    // cooldown 2
    // spawn alpha spitters
    if (cooldown2 <= 0){
        enemyCircle(4, EnemyFactory::EnemyType::SPITTER);
        cooldown2 = 435;
    }
}

void AlienQueen::phase3(Rectangle phitbox){
    
}

// charge towards the player
void AlienQueen::charge(Rectangle phitbox) {
    charging = true;
    chargeDuration = 70;
    cooldown = 100;

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
    xSpeed = dx * 13;
    ySpeed = dy * 13;

    soundList.push_back(SoundType::ALIENQUEEN2);
    sounds = true;
}

// moves towards the player
void AlienQueen::moveToPlayer(Rectangle phitbox) {
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
    if(length <= 400){
        xSpeed = -xSpeed;
        ySpeed = -ySpeed;
    }
    // buffer to stop stuttering when on the boundary of too close/far to player
    else if(length < 500){
        xSpeed = 0;
        ySpeed = 0;
    }    
}

// creates n projectile objects in a circle. 
void AlienQueen::spitProjectileCircle(int numProj) {

    Point enemyCenter = getCenter(&hitbox);

    // spawn projectiles centered on the enemy
    int x = enemyCenter.x - (SPITTERPROJECTILE_SIZE / 2);
    int y = enemyCenter.y - (SPITTERPROJECTILE_SIZE / 2);

    SpitterProjectile* spit;

    float angleStep = 360.0f / numProj;

    for (int i = 0; i < numProj; ++i) {
        float angleDeg = i * angleStep;
        float angleRad = angleDeg * (M_PI / 180.0f);

        float dx = cos(angleRad);
        float dy = sin(angleRad);

        float speed = spitSpeed;

        spit = new SpitterProjectile(x, y, dx * speed, dy * speed);
        childrenList.push_back(spit);
    }

    children = true;
    soundList.push_back(SoundType::SPIT_LOW);
    sounds = true;
}

void AlienQueen::enemyCircle(int number, EnemyFactory::EnemyType type) {
        
    Point enemyCenter = getCenter(&hitbox);

    // spawn projectiles centered on the enemy
    int x = enemyCenter.x - (SPITTERPROJECTILE_SIZE / 2);
    int y = enemyCenter.y - (SPITTERPROJECTILE_SIZE / 2);

    float angleStep = 360.0f / number;

    for (int i = 0; i < number; ++i) {
        float angleDeg = i * angleStep;
        float angleRad = angleDeg * (M_PI / 180.0f);

        float spawnX = x + cos(angleRad) * radius * 1.5;
        float spawnY = y + sin(angleRad) * radius * 1.5;

        GameProcess* enemy = EnemyFactory::createEnemy(type);
        enemy->setPosition(spawnX, spawnY);
        enemy->setLastPosition(spawnX, spawnY);
        childrenList.push_back(enemy);
    }

    soundList.push_back(SoundType::ALIENQUEEN1);
    sounds = true;
}

// creates a projectile object
void AlienQueen::spitProjectile(Rectangle phitbox) {

    
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
	
	// add sound for spitting
    soundList.push_back(SoundType::SPIT_LOW);
    sounds = true;
}



