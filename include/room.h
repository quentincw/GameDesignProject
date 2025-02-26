#ifndef _ROOM_H_
#define _ROOM_H_

#include <vector>
using namespace std;

class Room {
    public:
    // Constructor
    Room();
    
    // Methods
    vector<vector<int>> gen(int width, int height, vector<bool> door = {0, 0, 0, 0}, int walk_pct = 0);
    
    private:
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

#endif /* _ROOM_H_ */