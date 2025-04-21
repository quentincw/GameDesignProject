#ifndef BLOODSTAIN_H
#define BLOODSTAIN_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include "gameProcess.h"



class BloodStain : public GameProcess {

    public:

        // constructor for process
        BloodStain(int x, int y, int height, int width);

        // draws the object
        void Render(SDL_Renderer* renderer);

        // draws the object based on the camera's position
        void RenderCam(SDL_Renderer* renderer, int camX, int camY);

        // updates the object
        void Update(float deltaTime);

        // handles the interactions with other objects
        void handleInteractions(int tag);
    
    private:
    
        int currentSpriteIndex;
        
};


#endif