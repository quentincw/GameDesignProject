#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <random>
#include "constants.h"
#include "room.h"

Room::Room() {
    // ⬛ = path, ⬜ = wall
    // 1 = wall, 2 = wall up/left, 3 = wall down/right, 4 = none
    // [up, right, down, left]
    tiles = {
        // 0: ⬜⬜
        //    ⬜⬛
        {1, 2, 2, 1}, 
        // 1: ⬜⬜
        //    ⬛⬛
        {1, 2, 4, 2}, 
        // 2: ⬜⬜
        //    ⬛⬜
        {1, 1, 3, 2}, 
        // 3: ⬛⬛
        //    ⬛⬜
        {4, 3, 3, 4}, 
        // 4: ⬛⬛
        //    ⬜⬛
        {4, 4, 2, 3}, 
        // 5: ⬜⬛
        //    ⬜⬛
        {2, 4, 2, 1}, 
        // 6: ⬛⬛
        //    ⬛⬛
        {4, 4, 4, 4}, 
        // 7: ⬛⬜
        //    ⬛⬜
        {3, 1, 3, 4}, 
        // 8: ⬛⬜
        //    ⬛⬛
        {3, 2, 4, 4}, 
        // 9: ⬜⬛
        //    ⬛⬛
        {2, 4, 4, 2}, 
        // 10: ⬜⬛
        //     ⬜⬜
        {2, 3, 1, 1}, 
        // 11: ⬛⬛
        //     ⬜⬜
        {4, 3, 1, 3}, 
        // 12: ⬛⬜
        //     ⬜⬜
        {3, 1, 1, 3}, 
        // 13: ⬜⬜
        //     ⬜⬜
        {1, 1, 1, 1}
    };
}

vector<vector<int>> Room::gen(int width, int height, vector<int> door_loc, int walk_pct) {
    grid_width = width;
    grid_height = height;
    // set all tiles to blank
    vector<vector<vector<int>>> grid(width, vector<vector<int>>(height, tiles[6]));
    // set all to blank
    vector<vector<int>> fin_grid(width, vector<int>(height, 6));
    // assume all tiles will be walkable
    vector<vector<bool>> walk_grid(width, vector<bool>(height, true));

    // assume bottom is not walkable
    for (int x = 0; x < width; x++) {
        walk_grid[x][height - 1] = false;
    }

    random_device rd;  // get random number
    mt19937 eng(rd()); // seed
    uniform_int_distribution<> distr(0, 100); // Define the range

    int rand_tile;

    for (int t = 0; t < width * height; t++) {
        int x = t % width;
        int y = t / width;

        vector<int> pool = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

        // set up room border
        if (x == 0 && y == 0) {
            pool = {0, 13};
        }
        if (x == width - 1 && y == 0) {
            pool = {2, 13};
        }
        if (x == 0 && y == height - 1) {
            pool = {10, 13};
        }
        if (x == width - 1 && y == height - 1) {
            pool = {12, 13};
        }

        if (y == 0 && x == door_loc[0]) {
            continue;
        }
        if (y == 0 && x > 0 && x < width - 1) {
            pool = {0, 1, 2, 13};
            if (x == door_loc[0] - 1) {
                pool = {5, 9};
            }
            if (x == door_loc[0] + 1) {
                pool = {7, 8};
            }
        }
        if (x == width - 1  && y == door_loc[1]) {
            continue;
        }
        if (x == width - 1 && y > 0 && y < height  - 1) {
            pool = {2, 7, 12, 13};
            if (y == door_loc[1] - 1) {
                pool = {1, 8};
            }
            if (y == door_loc[1] + 1) {
                pool = {3, 11};
            }
        }
        if (y == height - 1 && x == door_loc[2]) {
            continue;
        }
        if (y == height - 1 && x > 0 && x < width - 1) {
            pool = {10, 11, 12, 13};
            if (x == door_loc[2] - 1) {
                pool = {4, 5};
            }
            if (x == door_loc[2] + 1) {
                pool = {3, 7};
            }
        }
        if (x == 0 && y == door_loc[3]) {
            continue;
        }
        if (x == 0 && y > 0 && y < height  - 1) {
            pool = {0, 5, 10, 13};
            if (y == door_loc[3] - 1) {
                pool = {1, 9};
            }
            if (y == door_loc[3] + 1) {
                pool = {4, 11};
            }
        }

        vector<int> new_pool;
        // first row (look at left tile)
        if (y == 0 && door_loc[0] >= 0) {
            // left
            if (x == door_loc[0] - 1) {
                for (int i : pool) {
                    if (tiles[i][1] == 4) {
                        new_pool.push_back(i);
                    }
                }
            }
            if (x == door_loc[0]) {
                grid[x][y] = tiles[6];
                continue;
            }
        }
        // last col (look at left, up, and left/up tile, also check for 12)
        if (door_loc[1] >= 0) {
            // 12
            if (x == width - 3 && y == door_loc[1] - 1 && y > 0) {
                for (int i : pool) {
                    if (tiles[i][1] != 3 || grid[x + 1][y - 1][2] != 3) {
                        new_pool.push_back(i);
                    }
                }
            }
            // left
            if (x == width - 2 && y == door_loc[1]) {
                for (int i : pool) {
                    if (tiles[i][1] == 4) {
                        new_pool.push_back(i);
                    }
                }
            }
            // up
            if (x == width - 1 && y == door_loc[1] - 1) {
                for (int i : pool) {
                    if (tiles[i][2] == 4) {
                        new_pool.push_back(i);
                    }
                }
            }
            // left/up
            if (x == width - 2 && y == door_loc[1] - 1) {
                for (int i : pool) {
                    if (tiles[i][1] != 3 && tiles[i][1] != 1) {
                        new_pool.push_back(i);
                    }
                }
            }
            if (x == width - 1 && y == door_loc[1]) {
                grid[x][y] = tiles[6];
                continue;
            }
        }
        // last row (look at left, up, and left/up tile, also check for 12)
        if (door_loc[2] >= 0) {
            // 12
            if (y == height - 2 && x == door_loc[2] - 2) {
                for (int i : pool) {
                    if (tiles[i][1] != 3 || grid[x + 1][y - 1][2] != 3) {
                        new_pool.push_back(i);
                    }
                }
            }
            // up
            if (y == height - 2 && x == door_loc[2]) {
                for (int i : pool) {
                    if (tiles[i][2] == 4) {
                        new_pool.push_back(i);
                    }
                }
            }
            // left
            if (y == height - 1 && x == door_loc[2] - 1) {
                for (int i : pool) {
                    if (tiles[i][1] == 4) {
                        new_pool.push_back(i);
                    }
                }
            }
            // up/left
            if (y == height - 2 && x == door_loc[2] - 1) {
                for (int i : pool) {
                    if (tiles[i][1] != 3 && tiles[i][1] != 1) {
                        new_pool.push_back(i);
                    }
                }
            }
            if (y == height - 1 && x == door_loc[2]) {
                grid[x][y] = tiles[6];
                continue;
            }
        }
        // first col (look at up tile)
        if (x == 0 && door_loc[3] >= 0) {
            // up
            if (y == door_loc[3] - 1) {
                for (int i : pool) {
                    if (tiles[i][2] == 4) {
                        new_pool.push_back(i);
                    }
                }
            }
            if (y == door_loc[3]) {
                grid[x][y] = tiles[6];
                continue;
            }
        }
        if (!new_pool.empty()) {
            sort(new_pool.begin(), new_pool.end());
            new_pool.erase(unique( new_pool.begin(), new_pool.end() ), new_pool.end());
            pool = new_pool;
        }
        
        // constraint is irrelevant if x > 0 (no tile left)
        if (x > 0) {
            vector<int> new_pool;
            vector<int> left_tile = grid[x - 1][y];
            for (int i : pool) {
                if (left_tile[1] == tiles[i][3]) {
                    new_pool.push_back(i);
                }
            }
            pool = new_pool;
        }
        // constraint is irrelevant if y > 0 (no tile above)
        if (y > 0) {
            vector<int> new_pool;
            vector<int> above_tile = grid[x][y - 1];
            for (int i : pool) {
                if (above_tile[2] == tiles[i][0]) {
                    new_pool.push_back(i);
                }
            }
            pool = new_pool;
        }

        // uses copy of pool so loop is unefected by removals
        vector<int> pool_cpy = pool;
        for (int i : pool_cpy) {
            // set i as placeholder
            grid[x][y] = tiles[i];
            // set walkable to represent placeholder
            if (i == 13) {
                walk_grid[x][y] = false;
            }
            else {
                walk_grid[x][y] = true;
            }
            // if not in first row or last col
            // check if i is placed, the next tile 12 preserves contiguousness
            if (y > 0 && x < width - 1) {
                if (tiles[i][1] == 3 && grid[x + 1][y - 1][2] == 3) {
                    // set 12 as placeholder
                    grid[x + 1][y] = tiles[12];
                    if (!is_contiguous(width, height, grid, walk_grid)) {
                        pool.erase(remove(pool.begin(), pool.end(), i), pool.end());
                    }
                    grid[x + 1][y] = tiles[6];
                }
            }
            // i in pool
            if (find(pool.begin(), pool.end(), i) != pool.end()) {
                if (!is_contiguous(width, height, grid, walk_grid)) {
                    pool.erase(remove(pool.begin(), pool.end(), i), pool.end());
                }
            }
        }

        if (!pool.empty()) {
            rand_tile = pool[distr(eng) % pool.size()];
            if (walk_pct > distr(eng) % 100) {
                if (find(pool.begin(), pool.end(), 6) != pool.end()) {
                    rand_tile = 6;
                }
                else if (find(pool.begin(), pool.end(), 9) != pool.end()) {
                    rand_tile = 9;
                }
                else if (find(pool.begin(), pool.end(), 8) != pool.end()) {
                    rand_tile = 8;
                }
                else if (find(pool.begin(), pool.end(), 4) != pool.end()) {
                    rand_tile = 4;
                }
                else if (find(pool.begin(), pool.end(), 3) != pool.end()) {
                    rand_tile = 3;
                }
                else if (find(pool.begin(), pool.end(), 1) != pool.end()) {
                    rand_tile = 1;
                }
                else if (find(pool.begin(), pool.end(), 5) != pool.end()) {
                    rand_tile = 5;
                }
                else if (find(pool.begin(), pool.end(), 7) != pool.end()) {
                    rand_tile = 7;
                }
                else if (find(pool.begin(), pool.end(), 11) != pool.end()) {
                    rand_tile = 11;
                }
                else if (find(pool.begin(), pool.end(), 0) != pool.end()) {
                    rand_tile = 0;
                }
                else if (find(pool.begin(), pool.end(), 2) != pool.end()) {
                    rand_tile = 2;
                }
                else if (find(pool.begin(), pool.end(), 10) != pool.end()) {
                    rand_tile = 10;
                }
                else if (find(pool.begin(), pool.end(), 12) != pool.end()) {
                    rand_tile = 12;
                }
            }
            fin_grid[x][y] = rand_tile;
            grid[x][y] = tiles[rand_tile];
            // set walkable to represent final value
            if (rand_tile == 13) {
                walk_grid[x][y] = false;
            }
            else {
                walk_grid[x][y] = true;
            }
        }
        else {
            cout << "error: no options available at (" << x << "," << y << ")" << endl;
            break;
        }
    }

    this->grid = grid;

    return fin_grid;
}

vector<vector<int>> Room::genPassage(int startX, int startY, int offsetX, int offsetY, int maxX, int maxY, vector<int> door, vector<vector<int>> floor_grid)
{
    // right
    if (door[1] != -1) {
        for (int x = startX; x < maxX ; x++) {
            floor_grid[x][offsetY + door[1] - 1] = 1;
            floor_grid[x][offsetY + door[1]] = 6;
            floor_grid[x][offsetY + door[1] + 1] = 11;
        }
    }
    // down
    if (door[2] != -1) {
        for (int y = startY; y < maxY; y++) {
            floor_grid[offsetX + door[2] - 1][y] = 5;
            floor_grid[offsetX + door[2]][y] = 6;
            floor_grid[offsetX + door[2] + 1][y] = 7;
        }
    }

    return floor_grid;
}

vector<vector<int>> Room::genPassageCol(int startX, int startY, int offsetX, int offsetY, int maxX, int maxY, vector<int> door, vector<vector<int>> floor_grid_col)
{
    // int size = TILE_SIZE / 2;
    // // right
    // if (door[1] != -1) {
    //     for (int x = startX; x < maxX ; x++) {
    //         int posX = x * TILE_SIZE;

    //         floor_grid_col[x][offsetY + door[1] - 1][0] = {posX, (offsetY + door[1] - 1) * TILE_SIZE, size, size};
    //         floor_grid_col[x][offsetY + door[1] - 1][1] = {posX + size, (offsetY + door[1] - 1) * TILE_SIZE, size, size};

    //         floor_grid_col[x][offsetY + door[1] + 1][2] = {posX, (offsetY + door[1] + 1) * TILE_SIZE + size, size, size};
    //         floor_grid_col[x][offsetY + door[1] + 1][3] = {posX + size, (offsetY + door[1] + 1) * TILE_SIZE + size, size, size};
    //     }
    // }
    // // down
    // if (door[2] != -1) {
    //     for (int y = startY; y < maxY; y++) {
    //         int posY = y * TILE_SIZE;

    //         floor_grid_col[offsetX + door[2] - 1][y][0] = {(offsetX + door[2] - 1) * TILE_SIZE, posY, size, size};
    //         floor_grid_col[offsetX + door[2] - 1][y][2] = {(offsetX + door[2] - 1) * TILE_SIZE, posY + size, size, size};

    //         floor_grid_col[offsetX + door[2] + 1][y][1] = {(offsetX + door[2] + 1) * TILE_SIZE + size, posY, size, size};
    //         floor_grid_col[offsetX + door[2] + 1][y][3] = {(offsetX + door[2] + 1) * TILE_SIZE + size, posY + size, size, size};
    //     }
    // }

    // return floor_grid_col;

    // right
    if (door[1] != -1) {
        for (int x = startX; x < maxX ; x++) {
            floor_grid_col[x][offsetY + door[1] - 1] = (offsetY + door[1] - 1) * TILE_SIZE;
            floor_grid_col[x + 1][offsetY + door[1] - 1] = (offsetY + door[1] - 1) * TILE_SIZE;

            floor_grid_col[x][offsetY + door[1] + 1 + 1] = (offsetY + door[1] + 1) * TILE_SIZE;
            floor_grid_col[x + 1][offsetY + door[1] + 1 + 1] = (offsetY + door[1] + 1);
        }
    }
    // down
    if (door[2] != -1) {
        for (int y = startY; y < maxY; y++) {
            floor_grid_col[offsetX + door[2] - 1][y] = (offsetX + door[2] - 1) * TILE_SIZE;
            floor_grid_col[offsetX + door[2] - 1][y + 1] = (offsetX + door[2] - 1) * TILE_SIZE;

            floor_grid_col[offsetX + door[2] + 1 + 1][y] = (offsetX + door[2] + 1) * TILE_SIZE;
            floor_grid_col[offsetX + door[2] + 1 + 1][y + 1] = (offsetX + door[2] + 1) * TILE_SIZE;
        }
    }

    return floor_grid_col;
}

bool Room::is_contiguous(int width, int height, vector<vector<vector<int>>> grid, vector<vector<bool>> walk_grid) {
    // dfs
    vector<vector<int>> to_visit;
    for (int start_x = 0; start_x < width; start_x++) {
        for (int start_y = 0; start_y < height; start_y++) {
            if (walk_grid[start_x][start_y]) {
                // keep list of previously visited tiles to go back to if in outlet
                to_visit.push_back({start_x, start_y});
                break;
            }
        }
        if (!to_visit.empty()) break;
    }
    // keep track of tiles visited
    vector<vector<bool>> visit_grid(width, vector<bool>(height, false));
    // run as long as not visited all tiles possible
    while (!to_visit.empty()) {
        int dx = to_visit.back()[0];
        int dy = to_visit.back()[1];
        to_visit.pop_back();
        if (!visit_grid[dx][dy]) {
            if (dy > 0) {
                if (walk_grid[dx][dy - 1] && grid[dx][dy][0] > 1 && grid[dx][dy - 1][2] > 1) {
                    to_visit.push_back({dx, dy - 1});
                }
            }
            if (dx > 0) {
                if (walk_grid[dx - 1][dy] && grid[dx][dy][3] > 1 && grid[dx - 1][dy][1] > 1) {
                    to_visit.push_back({dx - 1, dy});
                }
            }
            if (dy < height - 1) {
                if (walk_grid[dx][dy + 1] && grid[dx][dy][2] > 1 && grid[dx][dy + 1][0] > 1) {
                    to_visit.push_back({dx, dy + 1});
                }
            }
            if (dx < width - 1) {
                if (walk_grid[dx + 1][dy] && grid[dx][dy][1] > 1 && grid[dx + 1][dy][3] > 1) {
                    to_visit.push_back({dx + 1, dy});
                }
            }
            visit_grid[dx][dy] = true;
        }
    }

    int visit_count = 0;
    int walk_count = 0;
    for (int w = 0; w < width; w++) {
        for (int h = 0; h < height; h++) {
            if (visit_grid[w][h]) {
                visit_count++;
            }
            if (walk_grid[w][h]) {
                walk_count++;
            }
        }
    }

    if (visit_count == walk_count) {
        return true;
    }
    return false;
}

vector<vector<int>> Room::getTilemapCollision() {
    // // row, col, Rect[]
    // vector<vector<vector<SDL_Rect>>> tilemap_collision(grid_width, vector<vector<SDL_Rect>>(grid_height, vector<SDL_Rect>(4)));
    // int size = TILE_SIZE / 2;
    // for (int x = 0; x < grid_width; x++) {
    //     for (int y = 0; y < grid_height; y++) {
    //         int posX = x * TILE_SIZE;
    //         int posY = y * TILE_SIZE;
    //         if (grid[x][y][0] == 1 || grid[x][y][0] == 2) {
    //             tilemap_collision[x][y][0] = {posX, posY, size, size};
    //         }
    //         if (grid[x][y][0] == 1 || grid[x][y][0] == 3) {
    //             tilemap_collision[x][y][1] = {posX + size, posY, size, size};
    //         }
    //         if (grid[x][y][2] == 1 || grid[x][y][2] == 2) {
    //             tilemap_collision[x][y][2] = {posX, posY + size, size, size};
    //         }
    //         if (grid[x][y][2] == 1 || grid[x][y][2] == 3) {
    //             tilemap_collision[x][y][3] = {posX + size, posY + size, size, size};
    //         }
    //     }
    // }
    // return tilemap_collision;

    // subtile x, y (1 = wall, 0 = none)
    vector<vector<int>> tilemap_collision(grid_width * 2, vector<int>(grid_height * 2, 0));
    int size = TILE_SIZE / 2;
    for (int x = 0; x < grid_width; x++) {
        for (int y = 0; y < grid_height; y++) {
            // 1 = wall, 2 = wall up/left, 3 = wall down/right, 4 = none
            // [up, right, down, left]
            if (grid[x][y][0] == 1 || grid[x][y][0] == 2) {
                tilemap_collision[x][y] = 1;
            }
            if (grid[x][y][0] == 1 || grid[x][y][0] == 3) {
                tilemap_collision[x + 1][y] = 1;
            }
            if (grid[x][y][2] == 1 || grid[x][y][2] == 2) {
                tilemap_collision[x][y + 1] = 1;
            }
            if (grid[x][y][2] == 1 || grid[x][y][2] == 3) {
                tilemap_collision[x + 1][y + 1] = 1;
            }
        }
    }
    return tilemap_collision;

}