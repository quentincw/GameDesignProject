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

// boss room: empty, circle-ish shape, 1 door, 24x24
// small: empty (enemy encounter or reward), 2 doors, 8x8 - 11x11
// normal: ~80-90 walk_pct, 2-4 doors, 12x12 - 15x15
// large: ~60-80 walk_pct, 2-4 doors, 16x16 - 20x20

// should be normal room in between any non-normal rooms
// always start with: start -> normal -> normal -> etc.
// always end with: normal -> boss
// start will be at least 3 steps from boss
// small: 3-4 rooms
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
    // 2D vector of vector<vector<int>> (collision map of a room)
    vector<vector<vector<vector<int>>>> grid_col(width, vector<vector<vector<int>>>(height));
    // 2D vector of [up, right, down, left]
    vector<vector<vector<int>>> door_map(width, vector<vector<int>>(height, {-1, -1, -1, -1}));
    // vector of x, y coordinates for all rooms in order
    vector<vector<int>> layout;
    // vector of room_width, room_height, and walk_pct for all rooms in order
    vector<vector<int>> dimensions;

    dimensions.push_back({room_width, room_height, walk_pct});

    int room_w_min = room_width;
    int room_h_min = room_height;

    for (int r = 1; r < gen_rooms - 1; r++) {
        if (r != 1 && r != 2 && r != gen_rooms - 2 && room_width < 15 && room_width > 12) {
            room_width = (distr(eng) % 12) + 8;
            room_height = (distr(eng) % 12) + 8;
            if (room_width * room_height > 256) {
                walk_pct = (distr(eng) % 20) + 60;
            }
            else {
                walk_pct = (distr(eng) % 10) + 80;
            }
        }
        // for the first second and last (not including start and boss) room or if previous room was not normal, set normal conditions
        else {
            room_width = (distr(eng) % 3) + 12;
            room_height = (distr(eng) % 3) + 12;
            walk_pct = (distr(eng) % 10) + 80;
        }
        dimensions.push_back({room_width, room_height, walk_pct});
        if (room_w_min > room_width) room_w_min = room_width;
        if (room_h_min > room_height) room_h_min = room_height;
    }

    room_width = 24;
    room_height = 24;
    walk_pct = 100;
    dimensions.push_back({room_width, room_height, walk_pct});

    int x = distr(eng) % width;
    int y = distr(eng) % height;

    layout.push_back({x, y});

    bool start_con = false;

    while (layout.size() < gen_rooms) {
        bool room_taken = false;
        int locX = (distr(eng) % (room_h_min - 4)) + 2;
        int locY = (distr(eng) % (room_w_min - 4)) + 2;
        bool up = y + 1 <= height - 1 && door_map[x][y][0] == -1 && (!start_con || (start_con && (layout[0][0] != x || layout[0][1] != y + 1)));
        bool right = x + 1 <= width - 1 && door_map[x][y][1] == -1 && (!start_con || (start_con && (layout[0][0] != x + 1 || layout[0][1] != y)));
        bool down = y - 1 >= 0 && door_map[x][y][2] == -1 && (!start_con || (start_con && (layout[0][0] != x || layout[0][1] != y - 1)));
        bool left = x - 1 >= 0 && door_map[x][y][3] == -1 && (!start_con || (start_con && (layout[0][0] != x - 1 || layout[0][1] != y)));
        vector<int> pool = {};
        int layout_index = 0;

        while (!left && !right && !up && !down) {
            x = layout[layout.size() - 1 - layout_index][0];
            y = layout[layout.size() - 1 - layout_index][1];
            up = y + 1 <= height - 1 && door_map[x][y][0] == -1 && (!start_con || (start_con && (layout[0][0] != x || layout[0][1] != y + 1)));
            right = x + 1 <= width - 1 && door_map[x][y][1] == -1 && (!start_con || (start_con && (layout[0][0] != x + 1 || layout[0][1] != y)));
            down = y - 1 >= 0 && door_map[x][y][2] == -1 && (!start_con || (start_con && (layout[0][0] != x || layout[0][1] != y - 1)));
            left = x - 1 >= 0 && door_map[x][y][3] == -1 && (!start_con || (start_con && (layout[0][0] != x - 1 || layout[0][1] != y)));
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

        if (left) {
            if (rand == 0) {
                // mark door location for room and effected adjacent room
                door_map[x][y][3] = locX;
                door_map[x - 1][y][1] = locX;
                x--;
            }
            else if (door_map[x - 1][y][0] != -1 || door_map[x - 1][y][2] != -1 || door_map[x - 1][y][3] != -1) {
                door_map[x][y][3] = locX;
                door_map[x - 1][y][1] = locX;
            }
        }
        if (right) {
            if (rand == 1) {
                door_map[x][y][1] = locX;
                door_map[x + 1][y][3] = locX;
                x++;
            }
            else if (door_map[x + 1][y][0] != -1 || door_map[x + 1][y][1] != -1 || door_map[x + 1][y][2] != -1) {
                door_map[x][y][1] = locX;
                door_map[x + 1][y][3] = locX;
            }
        }
        if (up) {
            if (rand == 2) {
                door_map[x][y][0] = locY;
                door_map[x][y + 1][2] = locY;
                y++;
            }
            else if (door_map[x][y + 1][0] != -1 || door_map[x][y + 1][1] != -1 || door_map[x][y + 1][3] != -1) {
                door_map[x][y][0] = locY;
                door_map[x][y + 1][2] = locY;
            }
        }
        if (down) {
            if (rand == 3) {
                door_map[x][y][2] = locY;
                door_map[x][y - 1][0] = locY;
                y--;
            }
            else if (door_map[x][y - 1][1] != -1 || door_map[x][y - 1][2] != -1 || door_map[x][y - 1][3] != -1) {
                door_map[x][y][2] = locY;
                door_map[x][y - 1][0] = locY;
            }
        }

        start_con = true;

        for (vector<int> coord : layout) {
            if (coord[0] == x && coord[1] == y) {
                room_taken = true;
                break;
            }
        }
        if (!room_taken) {
            layout.push_back({x, y});
        }
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
                curRoomPos.x = x;
                curRoomPos.y = y;
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
    vector<vector<int>> rooms_col(max_col_total * 2, vector<int>(max_row_total * 2, 0));

    // stores rects that determine what should be rendered at given coordinates
    // for rooms render rooms and connected doors, for doors render doors and connected rooms
    // since render boxes overlap in connected doors, both rooms will render for doors
    vector<vector<SDL_Rect>> render_grid(grid_width, vector<SDL_Rect>(grid_height, SDL_Rect()));
    

    int x_offset = 0;
    int y_offset = 0;

    for (int x = 0; x < grid_width; x++) {
        for (int iy = 0; iy < grid_height; iy++) {
            int y = grid_height - 1 - iy;
            if (!grid[x][y].empty()) {
                for (int i = 0; i < grid[x][y].size(); i++) {
                    for (int j = 0; j < grid[x][y][i].size(); j++) {
                        rooms[i + x_offset][j + y_offset] = grid[x][y][i][j];
                        rooms_col[i + x_offset][j + y_offset] = grid_col[x][y][i][j];
                        rooms_col[i + x_offset + 1][j + y_offset] = grid_col[x][y][i + 1][j];
                        rooms_col[i + x_offset][j + y_offset + 1] = grid_col[x][y][i][j + 1];
                        rooms_col[i + x_offset + 1][j + y_offset + 1] = grid_col[x][y][i + 1][j + 1];
                    }
                }
                // create passages and passage collisions
                rooms = room.genPassage(x_offset + grid[x][y].size(), y_offset + grid[x][y][0].size(), x_offset, y_offset, x_offset + max_col[x] + pad, y_offset + max_row[y] + pad, door_map[x][y], rooms);
                rooms_col = room.genPassageCol(x_offset + grid[x][y].size(), y_offset + grid[x][y][0].size(), x_offset, y_offset, x_offset + max_col[x] + pad, y_offset + max_row[y] + pad, pad, door_map[x][y], rooms_col);

                render_grid[x][y] = {x_offset, y_offset, int(grid[x][y].size()), int(grid[x][y][0].size())};

                std::cout << "grid: x = "<< x << ", "<< y << " | "<< "Render grid: x = " << render_grid[x][y].x << ", y = " << render_grid[x][y].y << ", w = " << render_grid[x][y].w << ", h = " << render_grid[x][y].h << std::endl;
            }
            if (max_row[y] > 0) y_offset += max_row[y] + pad;
        }
        if (max_col[x] > 0) x_offset += max_col[x] + pad;
        y_offset = 0;
    }

    this->door_map = door_map;
    this->rooms = rooms;
    this->rooms_col = rooms_col;
    this->render_grid = render_grid;

    roomCoord = {layout[0][0], layout[0][1]};
    curRoom = render_grid[roomCoord[0]][roomCoord[1]];

    // 2D vector to hold the room positions
    vector<vector<int>> roomPos(grid_width, vector<int>(grid_height, 0));
    // iterate the possible positions to find which x,y have a room
    int count = 0;
    for (int gridX = 0; gridX < grid_width; gridX++) {
        for (int gridY = 0; gridY < grid_height; gridY++) {
            for(int roomC = 0; roomC < layout.size(); roomC++) {
                // check if the coordinates map to a room in the layout
                if((gridX == layout[roomC][0] && (gridY == layout[roomC][1]))) {
                    //cout << gridX << ' ' << gridY << endl;
                    roomPos[gridX][gridY] = 1;
                    count++;
                }
            }
        }
    }
    this->roomPosCoords = roomPos;
    /*
    // print out each room in the coordinate grid
    for (int i = 0; i < roomPos.size(); i++) {
        for (int j = 0; j < roomPos[i].size(); j++) {
          cout << roomPos[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << count;
    */
    return grid;
}

void Floor::setCurRoom(int posX, int posY)
{
    if (door_map[roomCoord[0]][roomCoord[1]][3] != -1) {
        if (render_grid[roomCoord[0] - 1][roomCoord[1]].x + render_grid[roomCoord[0] - 1][roomCoord[1]].w > posX) {
            // decrement x coord and set curRoom to room left
            roomCoord[0]--;
            cout<<roomCoord[0]<<", "<<roomCoord[1]<<endl;
        }
    }

    if (door_map[roomCoord[0]][roomCoord[1]][1] != -1) {
        if (render_grid[roomCoord[0] + 1][roomCoord[1]].x < posX) {
            // increment x coord and set curRoom to room right
            roomCoord[0]++;
            cout<<roomCoord[0]<<", "<<roomCoord[1]<<endl;
        }
    }

    if (door_map[roomCoord[0]][roomCoord[1]][0] != -1) {
        if (render_grid[roomCoord[0]][roomCoord[1] + 1].y + render_grid[roomCoord[0]][roomCoord[1] + 1].h > posY) {
            // increment y coord and set curRoom to room above
            roomCoord[1]++;
            cout<<roomCoord[0]<<", "<<roomCoord[1]<<endl;
        }
    }
    
    if (door_map[roomCoord[0]][roomCoord[1]][2] != -1) {
        if (render_grid[roomCoord[0]][roomCoord[1] - 1].y < posY) {
            // decrement y coord and set curRoom to room below
            roomCoord[1]--;
            cout<<roomCoord[0]<<", "<<roomCoord[1]<<endl;
        }
    }

    curRoom = render_grid[roomCoord[0]][roomCoord[1]];
    curRoomPos.x = roomCoord[0];
    curRoomPos.y = roomCoord[1];
    //cout<<curRoomPos.x<<", "<<curRoomPos.x<<endl;
    return;    
}

// returns a 2D vector representing where each room is
vector<vector<int>> Floor::getRoomsPos() {
    return roomPosCoords;
}

SDL_Rect Floor::getCurRoom()
{
    return curRoom;
}

// returns the current room's position in the 2D array
RoomPosition Floor::getRoomPos() {
    return curRoomPos;
}

vector<vector<int>> Floor::getRooms() {
    return rooms;
}

vector<vector<int>> Floor::getRoomsCol() {
    return rooms_col;
}
