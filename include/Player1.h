#ifndef _PLAYER1_H_
#define _PLAYER1_H_

#include "entity.h"

class Player1 : public Entity {
    public:

        // constructor
        Player1(int x, int y);

        // updates the object
        void Update(float deltaTime);

        // draws the object
        void Render(SDL_Renderer* renderer);

        // draws the object based on the camera's position
        void RenderCam(SDL_Renderer* renderer, int camX, int camY);

        // handles the interactions with other objects
        void handleInteractions(int tag);

		// updates angle for firing based on mouse position
		void updateMouse(float x, float y);

		// shoots projectile
		void shootProj(int camX, int camY);
		
		// Adjust player speed
		void setSpeedX(float x);
		void setSpeedY(float y);

        // handles the interactions with other objects
        void handleInteraction(std::string tag) override;
		
	protected:
		float mouseX;
		float mouseY;
		float cooldown;
		float stepCooldown;
};


#endif /* _PLAYER_H_ */