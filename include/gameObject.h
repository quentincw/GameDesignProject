#ifndef GOBJECT_H
#define GOBJECT_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>

class GameObject {

    public:

        // draws the object
        virtual void Render(SDL_Renderer* renderer) = 0;

        
};


#endif