#include "Player.h"
#include <iostream>

Player::Player(){}

Player::Player(float, float){
	xPos = 0;
	yPos = 0;
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

void Player::Update(float deltaTime) {
    xPos += xMove;
    yPos += yMove;
}

void Player::Render(SDL_Renderer* renderer) {
    boxRGBA(renderer, xPos, yPos, xPos+20, yPos+20, 0, 255, 0, 255);
}