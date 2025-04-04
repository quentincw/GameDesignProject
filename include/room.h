#ifndef _ROOM_H_
#define _ROOM_H_

#include <vector>
#include <SDL_rect.h>
using namespace std;

class Room {
    public:
    // Constructor
    Room();
    
    // Methods
    vector<vector<int>> gen(int width, int height, vector<int> door, int walk_pct = 0);
    vector<vector<int>> genPassage(int startX, int startY, int offsetX, int offsetY, int maxX, int maxY, vector<int> door, vector<vector<int>> floor_grid);
    vector<vector<int>> genPassageCol(int startX, int startY, int offsetX, int offsetY, int maxX, int maxY, vector<int> door, vector<vector<int>> floor_grid_col);
    vector<vector<int>> getTilemapCollision();
    
    private:
    int grid_width;
    int grid_height;
    // tile[], side
    vector<vector<int>> tiles;
    // row, col, tile[]
    vector<vector<vector<int>>> grid;
    // row, col, tile#
    vector<vector<int>> fin_grid;
    // row, col
    vector<vector<bool>> walk_grid;
    bool is_contiguous(int width, int height, vector<vector<vector<int>>> grid, vector<vector<bool>> walk_grid);
};

#endif  /* _ROOM_H_ */