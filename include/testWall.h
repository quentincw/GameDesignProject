#ifndef TESTWALL_H
#define TESTWALL_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include "gameObject.h"



class TestWall : public GameObject {

    public:

        // constructor for process
        TestWall(int x, int y, int height, int width);

        // draws the object
        void Render(SDL_Renderer* renderer);


};


#endif