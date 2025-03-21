#ifndef _FLOOR_H_
#define _FLOOR_H_

#include <vector>
#include <SDL_rect.h>
using namespace std;

class Floor {
    public:
    // Constructor
    Floor();
    
    // Methods
    vector<vector<vector<vector<int>>>> gen(int width, int height, int gen_rooms);
    void setCurRoom(int posX, int posY);
    SDL_Rect getCurRoom();
    vector<vector<int>> getRooms();
    vector<vector<vector<SDL_Rect>>> getRoomsCol();
    
    private:
    // additional padding between rooms
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
    vector<vector<vector<SDL_Rect>>> rooms_col;
    // rect areas in which tile and colliders will be used
    vector<vector<SDL_Rect>> render_grid;
};

#endif /* _FLOOR_H_ */