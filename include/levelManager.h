#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <vector>
#include <SDL.h>
#include "floor.h"
#include "processManager.h"
using namespace std;

class LevelManager {

public:
    // Constructor
    LevelManager();

    // Methods
    void genFloor(int level);
    // vector<vector<vector<SDL_Rect>>> getWalls();
    //vector<vector<int>>getTilemap();

    // checks if the player has moved to a different room and swaps process lists accordingly
    void setCurrentRoom(ProcessManager* pm);

    // returns the current floor
    Floor* getCurrentFloor();


private:
    // the current floor
    Floor curfloor;
    // all of the process lists associated with rooms of current floor
    vector<vector<vector<GameProcess*>>> roomLists;
    // the coordinates of the current room
    int roomX, roomY;

    // calculates the x,y positions and height, width of each room
    void fillProcessLists();


};

#endif