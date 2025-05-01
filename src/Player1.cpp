#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#include "Player1.h"
#include "playerProjectile.h"
#include <constants.h>
#include <random>

// constructor
Player1::Player1(int x, int y) : Entity() {

    health = 100;
    hitbox.height = 20;
    hitbox.width = 20;
	hitbox.x = x;
	hitbox.y = y;
    radius = 10;
    xSpeed = 0;
    ySpeed = 0;
	cooldown = 25;
	stepCooldown = 0;
    dodging = false;
    invulnerability = 0;
    dodgeCooldown = 0;
    damage = 0;
    maxHealth = 100;
    tags.insert("player");
}

// subtracts the health damage from the current heaSlth
void Player1::adjustHealth(int healthDamage) {
    if(healthDamage == -1) {
        invulnerability = 90;
        return;
    }
    // player is invulnerable
    if (invulnerability > 0) {
        return;
    }
    health = health - healthDamage;
    if (health <= 0) {
        health = 0;
        isAlive = false;
    }
    
    if (health > maxHealth) {
        health = maxHealth;
    }
    
    if (healthDamage > 0) {
        invulnerability = 90;
        red = 90;
        // spawn blood stain on damage
        spawnBloodStain(1);
        int val = rand()%6+1;
        switch (val) {
            case 1:
                soundList.push_back(SoundType::PLAYER_DAMAGE1);
                break;
            case 2:
                soundList.push_back(SoundType::PLAYER_DAMAGE2);
                break;
            case 3:
                soundList.push_back(SoundType::PLAYER_DAMAGE3);
                break;
            case 4:
                soundList.push_back(SoundType::PLAYER_DAMAGE4);
                break;
            case 5:
                soundList.push_back(SoundType::PLAYER_DAMAGE5);
                break;
            case 6:
                soundList.push_back(SoundType::PLAYER_DAMAGE6);	
        }
        sounds = true;
    }
}

// updates the object
void Player1::Update(float deltaTime) {
    /*
	float dx, dy;
	if (abs(xSpeed) == abs(ySpeed)){
		dx = sqrt(xSpeed*xSpeed/2);
		dy = sqrt(ySpeed*ySpeed/2);
		if (xSpeed<0) dx*=-1;
		if (ySpeed<0) dy*=-1;
	}
	else {
		dx = xSpeed;
		dy = ySpeed;
	}*/
	
	if ((xSpeed!=0 || ySpeed!=0) && stepCooldown<=0){
		soundList.push_back(SoundType::FOOTSTEPS);
		sounds = true;
		stepCooldown = 20;
	}
	stepCooldown-=1;

    // use dodge speed if dodging
    if (dodging) {
        hitbox.x += dodgeX;
        hitbox.y += dodgeY;
    }
    // use normal speed
    else {
        Entity::Update(deltaTime);
    }

	cooldown-=1;
    invulnerability-=1;
    red-=1;
    if (dodgeCooldown > 0){
        dodgeCooldown-=1;
    }
    if (invulnerability <= 0){
        if(dodging){
            dodging = false;
            tags.insert("player");
            dodgeCooldown = 30;
        }
    }
}

// adjust move speed
void Player1::setSpeedX(float x) {
	xSpeed = x;
}

void Player1::setSpeedY(float y) {
	ySpeed = y;
}

// draws the object
void Player1::Render(SDL_Renderer* renderer) {
    Point point = getCenter(&hitbox);
    filledCircleRGBA(renderer, point.x, point.y, radius, 0, 55, 200, 255);
	filledCircleRGBA(renderer, point.x+(20*mouseX), point.y+(20*mouseY), 5, 255, 255, 255, 255);
}

// draws the object based on the camera's position
void Player1::RenderCam(SDL_Renderer* renderer, int camX, int camY) {
    Point point = getCenter(&hitbox);

    static SDL_Surface* player_surface = SDL_LoadBMP( "../resource/player.bmp" );
    static SDL_Texture* player_texture = SDL_CreateTextureFromSurface( renderer, player_surface );

    SDL_SetTextureColorMod(player_texture, 255, 255, 255);
    if(red > 0) {
        SDL_SetTextureColorMod(player_texture, 255, 0, 0);
    }

    static SDL_Rect idle = {0, 0, 16, 16};

    static SDL_Rect spriteTextures[6] = {
        {0, 16, 16, 16},
        {16, 16, 16, 16},
        {32, 16, 16, 16},
        {48, 16, 16, 16},
        {64, 16, 16, 16},
        {80, 16, 16, 16}
    };

    SDL_Rect dst_player = { point.x - camX - (TILE_SIZE / 2), point.y - camY - (TILE_SIZE / 2), TILE_SIZE, TILE_SIZE };

    static const int total_frames = 6;
    static const int fps = 12;
    static int frame = 0;

    static SDL_RendererFlip flip = SDL_FLIP_NONE;

    static Uint64 startTicks = SDL_GetTicks();

    Uint64 curTicks = SDL_GetTicks();
    float deltaTime = curTicks - startTicks;
    if (deltaTime > 1000 / fps) {
        // play dodge
        if (dodging) {
            frame = 0;
        }
        // play walk anim
        else if (xSpeed != 0 || ySpeed != 0) {
            frame = (frame + 1) % total_frames;
        }
        // use idle sprite
        else {
            frame = 0;
        }
        startTicks = curTicks;
    }

    static SDL_Point flip_offset = {0, 0};

    if (xSpeed != 0 || ySpeed != 0) {
        if (xSpeed > 0) {
            flip = SDL_FLIP_NONE;
            flip_offset = {0, 0};
        }
        if (xSpeed < 0) {
            flip = SDL_FLIP_HORIZONTAL;
            flip_offset = {24, 0};
        }
        SDL_RenderCopyEx(renderer, player_texture, &spriteTextures[frame], &dst_player, NULL, NULL, flip);
    }
    else {
        SDL_RenderCopyEx(renderer, player_texture, &idle, &dst_player, NULL, NULL, flip);
    }

    static SDL_Surface* weapon_surface = SDL_LoadBMP( "../resource/weapon.bmp" );
    static SDL_Texture* weapon_texture = SDL_CreateTextureFromSurface( renderer, weapon_surface );
    SDL_SetTextureColorMod(weapon_texture, 255, 255, 255);
    if(red > 0) {
        SDL_SetTextureColorMod(weapon_texture, 255, 0, 0);
    }

    static const SDL_Point pivot = {8, 28};
    static const SDL_Point pivot_2 = {56, 28};

    int mX = 0;
    int mY = 0;
    Uint32 mouse = SDL_GetMouseState(&mX, &mY);
    float deltaX = point.x - camX - mX;
    float deltaY = point.y - camY - mY;

    float angle = 0.0f;

    if (deltaX != 0) angle = atanf(deltaY / deltaX) * (180 / M_PI);

    if (deltaX > 0) {
        dst_weapon = { point.x - camX - 68 + flip_offset.x, point.y - camY - 12 + flip_offset.y, TILE_SIZE, TILE_SIZE };
        SDL_RenderCopyEx(renderer, weapon_texture, NULL, &dst_weapon, angle, &pivot_2, SDL_FLIP_HORIZONTAL);
    }
    else {
        dst_weapon = { point.x - camX - 20 + flip_offset.x, point.y - camY - 12 + flip_offset.y, TILE_SIZE, TILE_SIZE };
        SDL_RenderCopyEx(renderer, weapon_texture, NULL, &dst_weapon, angle, &pivot, SDL_FLIP_NONE);
    }
}

void Player1::updateMouse(float x, float y){
	mouseX = x;
	mouseY = y;
}

// creates a projectile object
void Player1::shootProj(int camX, int camY) {
	if (cooldown<=0){

    // get center of hitboxes
    Point playerCenter = getCenter(&hitbox);

    // calculate vector
    float dx = mouseX - playerCenter.x + camX;
    float dy = mouseY - playerCenter.y + camY;

    // normalize
    float length = sqrt((dx * dx) + (dy * dy));

    if(length != 0) {
        dx = dx / length;
        dy = dy / length;
    }

    // set the speed based on spitSpeed
    float projXspeed = dx * 6;
    float projYspeed = dy * 6;

    // create spit at spitter's location w/ calculated speeds
    //SpitterProjectile spit(hitbox.x, hitbox.y, projXspeed, projYspeed);
    PlayerProjectile* spit = new PlayerProjectile(hitbox.x, hitbox.y, projXspeed, projYspeed);
    //child = spit;
    // put spit in childrenList
    //childrenList.clear();
    childrenList.push_back(spit);
    
    // set the flag for child to true
    children = true;
	cooldown = 25;

    // add sound to list
    soundList.push_back(SoundType::PLAYER_SHOOT);
    sounds = true;
	}
}

void Player1::handleInteraction(std::string tag) {
    Entity::handleInteraction(tag);
}

// causes the player to roll, dodging all attacks and moving quickly in one direction
void Player1::dodgeRoll(){
    // don't dodge roll unless moving
    if((xSpeed == 0) && (ySpeed == 0)){
        return;
    }
    // don't dodge if already dodging
    if(dodging == true){
        return;
    }
    // don't dodge if dodge is on cooldown
    if(dodgeCooldown > 0){
        return;
    }
    dodging = true;
    tags.erase("player");
    invulnerability = 30;
    // set speed for dodge
    float length = sqrt(xSpeed * xSpeed + ySpeed * ySpeed);
    float normX = xSpeed / length;
    float normY = ySpeed / length;

    float dodgeSpeed = 7.0f;
    dodgeX = normX * dodgeSpeed;
    dodgeY = normY * dodgeSpeed;
	
	soundList.push_back(SoundType::ROLL);
	sounds = true;

}