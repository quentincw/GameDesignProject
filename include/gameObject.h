#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

class GameObject {

    public:

        // updates the object
        virtual void Update(float deltaTime) = 0;

        // draws the object
        virtual void Render(SDL_Renderer* renderer) = 0;


};


#endif