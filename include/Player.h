#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GameObject.h"

class Player : public GameObject{
	public:
		Player();
		Player(float, float);
	
		void Update(float deltaTime);
		void Render(SDL_Renderer* renderer);
		
		void setX(float x);
		void setY(float y);
		
		float getX();
		float getY();
	
	protected:
		float xPos;
		float yPos;
		float xMove;
		float yMove;
};


#endif /* _PLAYER_H_ */