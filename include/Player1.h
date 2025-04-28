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

		// updates angle for firing based on mouse position
		void updateMouse(float x, float y);

		// shoots projectile
		void shootProj(int camX, int camY);
		
		// Adjust player speed
		void setSpeedX(float x);
		void setSpeedY(float y);

        // handles the interactions with other objects
        void handleInteraction(std::string tag) override;

        // causes the player to roll, dodging all attacks and moving quickly in one direction
        void dodgeRoll();

        void adjustHealth(int healthDamage) override;
		
	protected:
		float mouseX;
		float mouseY;
		float cooldown;

		float stepCooldown;

        float dodgeCooldown;
        // speeds for dodge
        float dodgeX, dodgeY;

        // timer for tracking how long the player should be invulnerable
        float invulnerability;

        // whether the player is dodging or not
        bool dodging;



    private:
        SDL_Rect dst_weapon;
};


#endif /* _PLAYER_H_ */