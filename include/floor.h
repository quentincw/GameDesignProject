#ifndef _FLOOR_H_
#define _FLOOR_H_

#include <vector>
#include <SDL_rect.h>
#include "rectangle.h"
using namespace std;

// struct for holding room position in 2D array
struct RoomPosition {
    int x;
    int y;
};


class Floor {
    public:
    // Constructor
    Floor();
    
    // Methods
    vector<vector<vector<vector<int>>>> gen(int level, int width, int height, int gen_rooms);
    void setCurRoom(int posX, int posY);
    SDL_Rect getCurRoom();

    // returns a rectangle represing the current room
    Rectangle getCurRoomRect();

    vector<vector<int>> getRooms();
    vector<vector<int>> getRoomsCol();

    int getLevel();

    vector<int> getBossLoc();

    // returns a 2D vector representing where each room is
    vector<vector<int>> getRoomsPos();

    // returns the current room's position in the 2D array
    RoomPosition getRoomPos();

    // returns a vector containing rectangles that represent each room
    vector<Rectangle> getRoomDimensions();
    
    private:
    // additional padding between rooms
    int cur_level;
    vector<int> boss_loc;
    SDL_Rect curRoom;
    vector<int> roomCoord;
    int pad;
    int grid_width;
    int grid_height;
    // 2D vector of [up, right, down, left]
    vector<vector<vector<int>>> door_map;
    // row, col, tilemap[]
    vector<vector<int>> rooms;
    // row, col, collision map[]
    vector<vector<int>> rooms_col;
    // rect areas in which tile and colliders will be used
    vector<vector<SDL_Rect>> render_grid;

    // 2D vector of 1 and 0, stores where each room is.
    vector<vector<int>> roomPosCoords;

    // current room position in 2D array
    RoomPosition curRoomPos;

    // vector of rectangles that stores x, y, height, width of each room for level manager
    vector<Rectangle> roomDimensions;
};

#endif /* _FLOOR_H_ */