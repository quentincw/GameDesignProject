/*#ifndef LEVELFILLER_H
#define LEVELFILLER_H

#include "spitter.h"
#include "spewer.h"
#include "roach.h"
#include "processManager.h"

class LevelFiller {
    public:
        // Constructor
        LevelFiller();

        // takes the 2D vector from the Level Manager and creates the process lists for each room
        void initializeRoomLists(vector<vector<int>> roomPos);

        // check if the given room coords match the current room coords
        // swap process lists if they don't match
        void setCurrentRoom(int x, int y);

        // returns the current process list
        vector<GameProcess*> getCurrentList();


    private:
        vector<vector<vector<GameProcess*> roomLists;
        //Point currentRoom;
        int curRoomX, curRoomY;

};




#endif
*/