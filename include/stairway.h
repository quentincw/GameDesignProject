#ifndef STAIRWAY_H
#define STAIRWAY_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"

// put player into interactions
class Stairway : public GameProcess {

    public:

        // default constructor
        Stairway(int x, int y, int height, int width);

        // updates the object
        void Update(float deltaTime);

        // draws the object
        void Render(SDL_Renderer* renderer);

        // draws the object based on the camera's position
        void RenderCam(SDL_Renderer* renderer, int camX, int camY);

        // handles the interactions with other objects
        void handleInteraction(std::string tag) override;

        // opens the stairway by changing the interactivity (by removing player tag)
        void openStairs();


    protected:

        // whether the stairway is open (interactable)
        bool open;

};


#endif