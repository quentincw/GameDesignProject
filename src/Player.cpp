#include "Player.h"
#include <iostream>

Player::Player(){}

Player::Player(float x, float y){
	xPos = x;
	yPos = y;
	weaponX = 1;
	weaponY = 0;
}

void Player::setX(float x){
	xMove = x;
}

void Player::setY(float y){
	yMove = y;
}

float Player::getX(){
	return xPos;
}

float Player::getY(){
	return yPos;
}

void Player::setMouse(float x, float y){
	float Vx = x - xPos;
	float Vy = y - yPos;
	float mag = sqrt(pow(Vx,2) + pow(Vy,2));
	weaponX = Vx / mag;
	weaponY = Vy / mag;
}

void Player::Update(float deltaTime) {
    xPos += xMove;
    yPos += yMove;
}

void Player::Render(SDL_Renderer* renderer) {
    boxRGBA(renderer, xPos-10, yPos-10, xPos+10, yPos+10, 0, 255, 0, 255);
	filledCircleRGBA(renderer, xPos+(20*weaponX), yPos+(20*weaponY), 5, 255, 255, 255, 255);
}