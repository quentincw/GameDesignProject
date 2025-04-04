#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <vector>
#include <SDL.h>
#include "floor.h"
using namespace std;

class LevelManager
{
public:
    // Constructor
    LevelManager();

    // Methods
    void genFloor(int level);
    // vector<vector<vector<SDL_Rect>>> getWalls();
    vector<vector<int>>getTilemap();

private:
    Floor floor;

};

#endif