#ifndef DEADSOLDIER_H
#define DEADSOLDIER_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"
#include "gameSounds.h"

// put player into interactions
class DeadSoldier : public GameProcess {

    public:

        // default constructor
        DeadSoldier(int x, int y);

        // updates the object
        void Update(float deltaTime);

        // updates the ai based on the player's position
        void UpdateAI(Rectangle phitbox);

        // draws the object
        void Render(SDL_Renderer* renderer);

        // draws the object based on the camera's position
        void RenderCam(SDL_Renderer* renderer, int camX, int camY);

        // handles the interactions with other objects
        void handleInteraction(std::string tag) override;


    protected:

        // flag for checking whether a voiceline has been played
        bool soundPlayed;

        int spriteNum;

        SDL_RendererFlip flip;


};


#endif