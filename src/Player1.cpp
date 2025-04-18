#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#include "Player1.h"
#include "playerProjectile.h"
#include <iostream>

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
	cooldown = 40;
    tags.insert("player");
}

// updates the object
void Player1::Update(float deltaTime) {
	float dx, dy;
	if (abs(xSpeed) == abs(ySpeed)){
		dx = sqrt(xSpeed*xSpeed/2);
		dy = sqrt(ySpeed*ySpeed/2);
		if (xSpeed<0) dx*=-1;
		if (ySpeed<0) dy*=-1;
	}
	else{
		dx = xSpeed;
		dy = ySpeed;
	}

    Entity::Update(deltaTime);
	cooldown-=1;
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
    filledCircleRGBA(renderer, point.x - camX, point.y - camY, radius, 0, 55, 200, 255);
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
    float projXspeed = dx * 3 + xSpeed;
    float projYspeed = dy * 3 + ySpeed;

    // create spit at spitter's location w/ calculated speeds
    //SpitterProjectile spit(hitbox.x, hitbox.y, projXspeed, projYspeed);
    PlayerProjectile* spit = new PlayerProjectile(hitbox.x, hitbox.y, projXspeed, projYspeed);
    //child = spit;
    // put spit in childrenList
    //childrenList.clear();
    childrenList.push_back(spit);
    
    // set the flag for child to true
    children = true;
	cooldown = 40;
	}
}

void Player1::handleInteraction(std::string tag) {
    if (tag == "wall") {
        revertPosition();
    }
}