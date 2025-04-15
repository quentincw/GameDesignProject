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

    // random number generators
    random_device rd;
    mt19937 gen;

    // flag for if the start room was cleared
    bool startDelete;

    // takes a process list and a room. Finds valid locations inside the room to place the enemies
    void findValidSpots(vector<GameProcess*>& curList, Rectangle rectangle);

    // fills a process list based on a difficulty level
    void fillProcessList(vector<GameProcess*>& curList, int difficulty);


};

#endif