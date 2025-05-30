#ifndef GOBJECT_H
#define GOBJECT_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include "rectangle.h"

struct Point {
    int x;
    int y;
};


class GameObject {

    public:

        // constructor
        GameObject();

        // draws the object
        virtual void Render(SDL_Renderer* renderer) = 0;

        // draws the object based on the camera's position
        virtual void RenderCam(SDL_Renderer* renderer, int camX, int camY) = 0;

        // get the hitbox of the game object
        Rectangle getHitbox() const;

        // sets the position of the rectangle
        void setPosition(float x, float y);

        // getters and setters for last position
        void setLastPosition(float x, float y);
        float getLastX();
        float getLastY();

        // calculates and returns the center point of the hitbox
        Point getCenter(Rectangle* rectangle) const;

        // reverts to previous position
        void revertPosition();

    protected:

        // hitbox for game object
        Rectangle hitbox;

        // the last position
        float lastX;
        float lastY;  
};


#endif