#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "enemy.h"
#include <iostream>
#include <random>

// constructor
Enemy::Enemy(int x, int y) : Entity() {
    interactions.insert("player");
    tags.insert("enemy");
    hitbox.x = x;
    hitbox.y = y;
    damage = 0;
}

// destructor
Enemy::~Enemy() {} 

void Enemy::handleInteraction(const std::string tag) {
    Entity::handleInteraction(tag);
}

void Enemy::deathSound(int odds) {
	soundList.push_back(SoundType::BUG_DEATH1);
	float per = 100.0/odds;
	int val = rand()%100;
	if (per>=val){
		val = rand()%9+1;
		switch (val) {
			case 1:
				soundList.push_back(SoundType::PLAYER_KILLS1);
				break;
			case 2:
				soundList.push_back(SoundType::PLAYER_KILLS2);
				break;
			case 3:
				soundList.push_back(SoundType::PLAYER_KILLS3);
				break;
			case 4:
				soundList.push_back(SoundType::PLAYER_KILLS4);
				break;
			case 5:
				soundList.push_back(SoundType::PLAYER_KILLS5);
				break;
			case 6:
				soundList.push_back(SoundType::PLAYER_KILLS6);	
				
			case 7:
				soundList.push_back(SoundType::PLAYER_KILLS1);
				break;
			case 8:
				soundList.push_back(SoundType::PLAYER_KILLS2);
				break;
			case 9:
				soundList.push_back(SoundType::PLAYER_KILLS3);
				break;
		}
	}
	sounds = true;
}