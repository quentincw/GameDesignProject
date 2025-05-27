#ifndef GAMEDOOR_H
#define GAMEDOOR_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "gameProcess.h"

// put player into interactions
class GameDoor : public GameProcess {

    public:

        // default constructor
        GameDoor(int x, int y, int height, int width, int rotation);

        // updates the object
        void Update(float deltaTime);

        // draws the object
        void Render(SDL_Renderer* renderer);

        // draws the object based on the camera's position
        void RenderCam(SDL_Renderer* renderer, int camX, int camY);

        // handles the interactions with other objects
        void handleInteraction(std::string tag) override;


    protected:

    private:

        // determines the rotation of the rendered wall
        int rot;


};


#endif