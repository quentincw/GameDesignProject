#include <iostream>
#include <stdio.h>
#include <random>
#include "constants.h"
#include "floor.h"
#include "room.h"
#include "player.h"

Floor::Floor() {
    pad = 3;
}

// start room: empty, 1 door, 12x9 (normal size)
// boss room: empty, circle-ish shape, 1 door, size tbd
// identify different room types: small, normal, large
// small: empty (enemy encounter or reward), 2 doors, 8x6
// normal: ~80 walk_pct, 2-4 doors, 12x9
// large: ~60-80 walk_pct, 2-4 doors, size tbd (but should vary significantly), scroll

// identify layout possibilities:
// ~10-12 rooms (not including start and boss)
// should be normal room in between any non-normal rooms
// always start with: start -> normal -> normal -> etc.
// always end with: normal -> boss
// there is always at a base of 4 normal rooms, and start will be at least 3 steps from boss
// small: 3-4 rooms
// normal: 6-7 rooms
// large: 2-3 rooms

vector<vector<vector<vector<int>>>> Floor::gen(int width, int height, int gen_rooms) {
    random_device rd;  // get random number
    mt19937 eng(rd()); // seed
    uniform_int_distribution<> distr(0, 100); // Define the range

    Room room;

    grid_width = width;
    grid_height = height;

    // to fit in screen - max w: 1024/TILE_SIZE, max h: 768/TILE_SIZE
    // to accommodate for door width and height min: 5
    int room_width = 8;
    // screen res is 4x3
    int room_height = 8;
    // 0 - 100 (default room - empty room)
    int walk_pct = 100;

    // 2D vector of vector<vector<int>> (tilemap of a room)
    vector<vector<vector<vector<int>>>> grid(width, vector<vector<vector<int>>>(height));
    // 2D vector of vector<vector<vector<SDL_Rect>>> (collision map of a room)
    vector<vector<vector<vector<vector<SDL_Rect>>>>> grid_col(width, vector<vector<vector<vector<SDL_Rect>>>>(height));
    // 2D vector of [up, right, down, left]
    vector<vector<vector<int>>> door_map(width, vector<vector<int>>(height, {-1, -1, -1, -1}));
    // vector of x, y coordinates for all rooms in order
    vector<vector<int>> layout;
    // vector of room_width, room_height, and walk_pct for all rooms in order
    vector<vector<int>> dimensions;

    dimensions.push_back({room_width, room_height, walk_pct});

    int room_w_min = room_width;
    int room_h_min = room_height;

    for (int r = 0; r < gen_rooms; r++) {
        room_width = (distr(eng) % 16) + 8;
        room_height = (distr(eng) % 16) + 8;
        walk_pct = (distr(eng) % 20) + 70;
        dimensions.push_back({room_width, room_height, walk_pct});
        if (room_w_min > room_width) room_w_min = room_width;
        if (room_h_min > room_height) room_h_min = room_height;
    }

    int x = distr(eng) % width;
    int y = distr(eng) % height;

    layout.push_back({x, y});

    // UPDATE:
    // if rooms are adjacent (not becuase they are genrated consecutively), there should be a chance a door is placed

    for (int r = 0; r < gen_rooms; r++) {
        int locX = (distr(eng) % (room_h_min - 4)) + 2;
        int locY = (distr(eng) % (room_w_min - 4)) + 2;
        bool up = y + 1 <= height - 1 && door_map[x][y][0] == -1;
        bool right = x + 1 <= width - 1 && door_map[x][y][1] == -1;
        bool down = y - 1 >= 0 && door_map[x][y][2] == -1;
        bool left = x - 1 >= 0 && door_map[x][y][3] == -1;
        vector<int> pool = {};
        int layout_index = 0;

        while (!left && !right && !up && !down) {
            x = layout[layout.size() - 1 - layout_index][0];
            y = layout[layout.size() - 1 - layout_index][1];
            up = y + 1 <= height - 1 && door_map[x][y][0] == -1;
            right = x + 1 <= width - 1 && door_map[x][y][1] == -1;
            down = y - 1 >= 0 && door_map[x][y][2] == -1;
            left = x - 1 >= 0 && door_map[x][y][3] == -1;
            layout_index++;
        }

        if (left) {
            pool.push_back(0);
        }
        if (right) {
            pool.push_back(1);
        }
        if (up) {
            pool.push_back(2);
        }
        if (down) {
            pool.push_back(3);
        }

        int rand = pool[distr(eng) % pool.size()];

        if (rand == 0) {
            // mark door location for room and effected adjacent room
            door_map[x][y] = {door_map[x][y][0], door_map[x][y][1], door_map[x][y][2], locX};
            door_map[x - 1][y] = {door_map[x - 1][y][0], locX, door_map[x - 1][y][2], door_map[x - 1][y][3]};
            x--;
        }
        if (rand == 1) {
            door_map[x][y] = {door_map[x][y][0], locX, door_map[x][y][2], door_map[x][y][3]};
            door_map[x + 1][y] = {door_map[x + 1][y][0], door_map[x + 1][y][1], door_map[x + 1][y][2], locX};
            x++;
        }
        if (rand == 2) {
            door_map[x][y] = {locY, door_map[x][y][1], door_map[x][y][2], door_map[x][y][3]};
            door_map[x][y + 1] = {door_map[x][y + 1][0], door_map[x][y + 1][1], locY, door_map[x][y + 1][3]};
            y++;
        }
        if (rand == 3) {
            door_map[x][y] = {door_map[x][y][0], door_map[x][y][1], locY, door_map[x][y][3]};
            door_map[x][y - 1] = {locY, door_map[x][y - 1][1], door_map[x][y - 1][2], door_map[x][y - 1][3]};
            y--;
        }
        layout.push_back({x, y});
    }

    // create rooms and room collisions
    for (int r = 0; r < layout.size(); r++) {
        x = layout[r][0];
        y = layout[r][1];
        grid[x][y] = room.gen(dimensions[r][0], dimensions[r][1], door_map[x][y], dimensions[r][2]);
        grid_col[x][y] = room.getTilemapCollision();
    }

    for (int iy = 0; iy < grid_height; ++iy) {
        y = grid_height - 1 - iy;
        for (int x = 0; x < grid_width; ++x) {
            if (!grid[x][y].empty()) {
                if (layout[0][0] == x && layout[0][1] == y) cout << "1 ";
                else cout << "0 ";
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }

    // find largest room width in col and height in row
    vector<int> max_col(grid_width, 0);
    vector<int> max_row(grid_height, 0);
    int max_col_total = 0;
    int max_row_total = 0;

    for (int x = 0; x < grid_width; x++) {
        for (int y = 0; y < grid_height; y++) {
            if (!grid[x][y].empty()) {
                int room_width = grid[x][y].size();
                max_col[x] = max(max_col[x], room_width);
                max_col_total += max(max_col[x], room_width);

                int room_height = grid[x][y][0].size();
                max_row[y] = max(max_row[y], room_height);
                max_row_total += max(max_row[y], room_height);
            }
        }
    }

    // vector that consolidates the rooms in grid to a 2D vector of all rooms (tiles)
    vector<vector<int>> rooms(max_col_total, vector<int>(max_row_total, -1));
    vector<vector<vector<SDL_Rect>>> rooms_col(max_col_total, vector<vector<SDL_Rect>>(max_row_total, vector<SDL_Rect>(4)));

    // stores rects that determine what should be rendered at given coordinates
    // for rooms render rooms and connected doors, for doors render doors and connected rooms
    // since render boxes overlap in connected doors, both rooms will render for doors
    vector<vector<SDL_Rect>> render_grid(grid_width, vector<SDL_Rect>(grid_height, SDL_Rect()));

    int x_offset = 0;
    int y_offset = 0;

    int x_start;
    int y_start;

    for (int x = 0; x < grid_width; x++) {
        for (int iy = 0; iy < grid_height; iy++) {
            int y = grid_height - 1 - iy;
            if (!grid[x][y].empty()) {
                for (int i = 0; i < grid[x][y].size(); i++) {
                    for (int j = 0; j < grid[x][y][i].size(); j++) {
                        rooms[i + x_offset][j + y_offset] = grid[x][y][i][j];
                        rooms_col[i + x_offset][j + y_offset] = grid_col[x][y][i][j];
                        for (int k = 0; k < grid_col[x][y][i][j].size(); k++) {
                            rooms_col[i + x_offset][j + y_offset][k].x += x_offset * TILE_SIZE;
                            rooms_col[i + x_offset][j + y_offset][k].y += y_offset * TILE_SIZE;
                        }
                    }
                }
                // create passages and passage collisions
                rooms = room.genPassage(x_offset + grid[x][y].size(), y_offset + grid[x][y][0].size(), x_offset, y_offset, x_offset + max_col[x] + pad, y_offset + max_row[y] + pad, door_map[x][y], rooms);
                rooms_col = room.genPassageCol(x_offset + grid[x][y].size(), y_offset + grid[x][y][0].size(), x_offset, y_offset, x_offset + max_col[x] + pad, y_offset + max_row[y] + pad, door_map[x][y], rooms_col);

                // set first room to curRoom
                if (layout[0][0] == x && layout[0][1] == y) {
                    x_start = x_offset;
                    y_start = y_offset;
                }
            }
            // max_width, max_height
            render_grid[x][y] = {x_offset, y_offset, 24, 24};

            if (max_row[y] > 0) y_offset += max_row[y] + pad;
        }
        if (max_col[x] > 0) x_offset += max_col[x] + pad;
        y_offset = 0;
    }

    this->door_map = door_map;
    this->rooms = rooms;
    this->rooms_col = rooms_col;
    this->render_grid = render_grid;

    setCurRoom(x_start, y_start);

    return grid;
}

void Floor::setCurRoom(int posX, int posY)
{
    for (int x = 0; x < render_grid.size(); x++) {
        if (render_grid[x][0].x <= posX && render_grid[x][0].x + render_grid[x][0].w >= posX) {
            for (int y = 0; y < render_grid[x].size(); y++) {
                if (render_grid[x][y].w > 0) {
                    if (render_grid[x][y].y <= posY && render_grid[x][y].y + render_grid[x][y].h >= posY) {
                        curRoom = render_grid[x][y];
                        return;
                    }
                }
            }
        }
    }
}

SDL_Rect Floor::getCurRoom()
{
    return curRoom;
}

vector<vector<int>> Floor::getRooms() {
    return rooms;
}

vector<vector<vector<SDL_Rect>>> Floor::getRoomsCol() {
    return rooms_col;
}