#include "gameLogic.h"
#include "gameProcess.h"
#include "gameObject.h"
#include "constants.h"
#include "levelManager.h"

LevelManager::LevelManager()
{
    SDL_Rect tile_0;
    tile_0.x = 0;
    tile_0.y = 0;
    tile_0.w = 16;
    tile_0.h = 16;

    SDL_Rect tile_1;
    tile_1.x = 16;
    tile_1.y = 0;
    tile_1.w = 16;
    tile_1.h = 16;

    SDL_Rect tile_2;
    tile_2.x = 32;
    tile_2.y = 0;
    tile_2.w = 16;
    tile_2.h = 16;

    SDL_Rect tile_3;
    tile_3.x = 48;
    tile_3.y = 0;
    tile_3.w = 16;
    tile_3.h = 16;

    SDL_Rect tile_4;
    tile_4.x = 64;
    tile_4.y = 0;
    tile_4.w = 16;
    tile_4.h = 16;

    SDL_Rect tile_5;
    tile_5.x = 0;
    tile_5.y = 16;
    tile_5.w = 16;
    tile_5.h = 16;

    SDL_Rect tile_6;
    tile_6.x = 16;
    tile_6.y = 16;
    tile_6.w = 16;
    tile_6.h = 16;

    SDL_Rect tile_7;
    tile_7.x = 32;
    tile_7.y = 16;
    tile_7.w = 16;
    tile_7.h = 16;

    SDL_Rect tile_8;
    tile_8.x = 48;
    tile_8.y = 16;
    tile_8.w = 16;
    tile_8.h = 16;

    SDL_Rect tile_9;
    tile_9.x = 64;
    tile_9.y = 16;
    tile_9.w = 16;
    tile_9.h = 16;

    SDL_Rect tile_10;
    tile_10.x = 0;
    tile_10.y = 32;
    tile_10.w = 16;
    tile_10.h = 16;

    SDL_Rect tile_11;
    tile_11.x = 16;
    tile_11.y = 32;
    tile_11.w = 16;
    tile_11.h = 16;

    SDL_Rect tile_12;
    tile_12.x = 32;
    tile_12.y = 32;
    tile_12.w = 16;
    tile_12.h = 16;

    SDL_Rect tile_13;
    tile_13.x = 48;
    tile_13.y = 32;
    tile_13.w = 16;
    tile_13.h = 16;

    SDL_Rect tileTextures[14] = {tile_0, tile_1, tile_2, tile_3, tile_4, tile_5, tile_6, tile_7, tile_8, tile_9, tile_10, tile_11, tile_12, tile_13};
}

void LevelManager::genFloor(int level)
{
    switch (level) {
        case 1:
            // 3, 4, 5
            floor.gen(6, 6, 14);
        case 2:
            // 4, 5, 6
            floor.gen(6, 6, 16);
        case 3:
            // 4, 5, 6
            floor.gen(5, 5, 18);
        default:
            floor.gen(5, 5, 14);
    }

    SDL_Rect curRoom = floor.getCurRoom();

    vector<vector<int>> rooms = floor.getRooms();
    int rooms_width = rooms.size();
    int rooms_height = rooms[0].size();

    vector<vector<SDL_Rect>> tile(rooms_width, vector<SDL_Rect>(rooms_height));
    static const int MAP_SIZE = 2;
    for (int x = 0; x < rooms_width; x++) {
        for (int y = 0; y < rooms_height; y++) {
            tile[x][y].x = x * TILE_SIZE;
            tile[x][y].y = y * TILE_SIZE;
            tile[x][y].w = TILE_SIZE;
            tile[x][y].h = TILE_SIZE;
        }
    }
}

vector<vector<int>> LevelManager::getTilemap()
{
    return floor.getRoomsCol();
}
