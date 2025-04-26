#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <vector>
#include <SDL.h>
#include "floor.h"
#include "processManager.h"
#include <random>
using namespace std;

class LevelManager {

public:
    // Constructor
    LevelManager();

    // Methods
    void genFloor(int level);

    // generates the next level based on the level number
    void genNextFloor(GameProcess* player);

    // checks if the player has moved to a different room and swaps process lists accordingly
    void setCurrentRoom(ProcessManager* pm);

    // returns the current floor
    Floor* getCurrentFloor();


private:
    // the current floor
    Floor* curfloor;
    // all of the process lists associated with rooms of current floor
    vector<vector<vector<GameProcess*>>> roomLists;
    // the coordinates of the current room
    int roomX, roomY;

    // flag for deleting first room
    bool startDelete;


    // the current floor number (1, 2, 3)
    int floorNumber;

    // random number generators
    random_device rd;
    mt19937 gen;

    // takes a process list and a room. Finds valid locations inside the room to place the enemies
    void findValidSpots(vector<GameProcess*>& curList, Rectangle rectangle);

    // fills a process list based on a difficulty level
    void fillProcessList(vector<GameProcess*>& curList, int difficulty);

    // fills a process list with a boss encounter
    void fillProcessListBoss(vector<GameProcess*>& curList);


};

#endif