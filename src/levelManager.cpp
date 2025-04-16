#include "gameProcess.h"
#include "gameObject.h"
#include "constants.h"
#include "levelManager.h"
#include "floor.h"
#include "enemyFactory.h"
#include "gameDoor.h"
#include <random>
#include <ctime>
//#include <algorithm> // reverse
#include <set>
using namespace std;

LevelManager::LevelManager() {
    mt19937 gen(rd()); 
}


void LevelManager::genFloor(int level) {
    // different parameters for floor generation
    switch (level) {
        case 1:
            // 3, 4, 5
            curfloor.gen(3, 5, 14);
            break;
        case 2:
            // 4, 5, 6
            curfloor.gen(6, 6, 16);
            break;
        case 3:
            // 4, 5, 6
            curfloor.gen(5, 5, 18);
            break;
        default:
            curfloor.gen(5, 5, 14);
    }

    // set the current room to the start room
    RoomPosition newPos = curfloor.getRoomPos();
    roomX = newPos.x;
    roomY = newPos.y;

    // get the room coordinates
    vector<vector<int>> roomPos = curfloor.getRoomsPos();
    
    // reverse y vector
    //reverse(roomPos.begin(), roomPos.end());
    for (size_t i = 0; i < roomPos.size(); ++i) {
        reverse(roomPos[i].begin(), roomPos[i].end());
    }

    // make the 2D vector of process lists match the rooms
    // rows
    roomLists.resize(roomPos.size());

    //columns
    for (size_t i = 0; i < roomPos.size(); ++i) {
        roomLists[i].resize(roomPos[i].size()); 

        // fill each element with an empty vector of GameProcess*
        for (size_t j = 0; j < roomPos[i].size(); ++j) {
            roomLists[i][j] = vector<GameProcess*>();
        }
    }

    // fill room lists with enemies
    //fillProcessLists();

    // get the dimensions of the floor
    vector<Rectangle> rooms = curfloor.getRoomDimensions();
    /*
    for (size_t i = 0; i < rooms.size(); ++i) {
        cout << "x: " << rooms[i].x << " y: " << rooms[i].y << " width: " << rooms[i].width << " height: " << rooms[i].height << endl;
    }*/

    // 1 == room, 0 == gap
    int count = 0;
    Rectangle curRect;
    GameProcess* enemy = nullptr;
    vector<vector<int>> roomsCol = curfloor.getRoomsCol();
    GameProcess* gameDoor = nullptr;

    cout << "roomsCol size x: " << roomsCol.size() << endl;
    
    for (size_t i = 0; i < roomsCol.size(); ++i) {
        for (size_t j = 0; j < 70; ++j) {
            cout << roomsCol[i][j] << " ";
        }
        cout << "\n";
    }


    // loop through every room
    for (size_t i = 0; i < roomPos.size(); ++i) {
        for (size_t j = 0; j < roomPos[i].size(); ++j) {
            // if there is not a gap in this spot
            if(roomPos[i][j] == 1) {
                // get the next rectangle
                Rectangle curRect = rooms[count];
                cout << "RoomPos " << i << " " << j << ": " << curRect.x << " " << curRect.y << endl;
                // level filler call (fill list using the rectangle)
                fillProcessList(roomLists[i][j], 2);
                // find valid places for each enemy
                findValidSpots(roomLists[i][j], curRect);

                cout << "RoomPos h/w: " << i << " " << j << ": " << curRect.width << " " << curRect.height << endl;
                
                
                // check for door on top side
                bool door = false;
                for(size_t w = 0; w < curRect.width; ++w) {
                    //cout << roomsCol[curRect.x + w][curRect.y] << " ";
                    if((door == false) && (roomsCol[curRect.x + w][curRect.y] == 0)) {
                        door = true;
                        // create a door at the position
                        gameDoor = new GameDoor((curRect.x + w - 1) * TILE_SIZE, (curRect.y - 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE * 3);
                        roomLists[i][j].push_back(gameDoor);
                    }
                }
                //cout << "\n";

                // check for door on left side
                door = false;
                for(size_t h = 0; h < curRect.height; ++h) {
                    if((door == false) && (roomsCol[curRect.x][curRect.y + h] == 0)) {
                        door = true;
                        // create a door at the position
                        gameDoor = new GameDoor((curRect.x - 1) * TILE_SIZE, (curRect.y + h - 1) * TILE_SIZE, TILE_SIZE * 3, TILE_SIZE);
                        roomLists[i][j].push_back(gameDoor);
                    }
                }

                // check for door on bottom side
                door = false;
                for(size_t w = 0; w < curRect.width; ++w) {
                    if((door == false) && (roomsCol[curRect.x + w][curRect.y + curRect.height] == 0)) {
                        door = true;
                        // create a door at the position
                        gameDoor = new GameDoor((curRect.x + w - 1) * TILE_SIZE, (curRect.y + curRect.height) * TILE_SIZE, TILE_SIZE, TILE_SIZE * 3);
                        roomLists[i][j].push_back(gameDoor);
                    }
                }

                // check for door on right side
                door = false;
                for(size_t h = 0; h < curRect.height; ++h) {
                    if((door == false) && (roomsCol[curRect.x + curRect.width][curRect.y + h] == 0)) {
                        door = true;
                        // create a door at the position
                        gameDoor = new GameDoor((curRect.x + curRect.width) * TILE_SIZE, (curRect.y + h - 1) * TILE_SIZE, TILE_SIZE * 3, TILE_SIZE);
                        roomLists[i][j].push_back(gameDoor);
                    }
                }


                // iterate count
                count++;
            }
        }
    }
    //cout << "out of geen" << endl;
    // reverse y vectors
    for (size_t i = 0; i < roomPos.size(); ++i) {
        reverse(roomLists[i].begin(), roomLists[i].end());
    }
    


}

// takes a process list and a room. Finds valid locations inside the room to place the enemies
void LevelManager::findValidSpots(vector<GameProcess*>& curList, Rectangle rectangle) {


    // random number ranges (height/width)
    uniform_real_distribution<> width(2, rectangle.width - 2);
    uniform_real_distribution<> height(2, rectangle.height- 2);

    // potential position (tile)
    int x,y;

    cout << rectangle.x << endl;
    cout << rectangle.y << endl;
    cout << rectangle.width << endl;
    cout << rectangle.height << endl;
    cout << "generate" << endl;

    // vector of valid/ invalid locations
    vector<vector<int>> roomsCol = curfloor.getRoomsCol();

    // loop through each process
    for (size_t i = 0; i < curList.size(); ++i) {
        // generate a position
        x = width(gen) + rectangle.x;
        y = height(gen) + rectangle.y;
        cout << x << endl;
        cout << y << endl;
        cout << roomsCol[x][y] << endl;
        // cheeck if valid
        while(roomsCol[x][y] == 1){
            // repeat until valid
            x = width(gen) + rectangle.x;
            y = height(gen) + rectangle.y;
        }
        cout << "found spot" << endl;
        if (curList[i] != nullptr) {
            curList[i]->setPosition(x * TILE_SIZE, y * TILE_SIZE);
        } else {
            cout << "Null pointer encountered at index " << i << endl;
        }
        cout << "seet spot" << endl;
    }
    cout << "fin spots" << endl;
}

// fills a process list based on a difficulty level
void LevelManager::fillProcessList(vector<GameProcess*>& curList, int difficulty) {

    // random enemy generator
    // increase for every enemy added
    uniform_int_distribution<> enemyDist(0, 6);

    cout << "made it" << endl;
 
    GameProcess* enemy = nullptr;

    // loop for generating enemies
    // spawns difficulty * 2 enemies
    for (int i = 0; i < difficulty * 2; ++i) { 
        // generate an enemy number
        int enemyType = enemyDist(gen);

        switch (enemyType) {
            case 0:
                // spawn roach
                enemy = EnemyFactory::createEnemy(EnemyFactory::EnemyType::ROACH);
                break;
            case 1:
                // spawn spitter
                enemy = EnemyFactory::createEnemy(EnemyFactory::EnemyType::SPITTER);
                break;
            case 2:
                // spawn spewer
                enemy = EnemyFactory::createEnemy(EnemyFactory::EnemyType::SPEWER);
                break;
            case 3:
                // spawn spawner
                enemy = EnemyFactory::createEnemy(EnemyFactory::EnemyType::SPAWNER);
                break;
            case 4:
                // spawn Exploder
                enemy = EnemyFactory::createEnemy(EnemyFactory::EnemyType::EXPLODER);
                break;
            case 5:
                // spawn Alpha Spitter
                enemy = EnemyFactory::createEnemy(EnemyFactory::EnemyType::ALPHASPITTER);
                break;
            case 6:
                // spawn Charger
                enemy = EnemyFactory::createEnemy(EnemyFactory::EnemyType::CHARGER);
                break;


            default:
                break;
        }

        // add enemy to the list
        curList.push_back(enemy);

    }
}


void LevelManager::setCurrentRoom(ProcessManager* pm) {

    //get the player
    GameProcess* player = pm->getPlayer();
    int pX = player->getHitbox().x;
    int pY = player->getHitbox().y;

    // set the current room within the floor
    curfloor.setCurRoom(pX / TILE_SIZE, pY / TILE_SIZE);

    // get the current room
    RoomPosition newPos = curfloor.getRoomPos();


    // check if the player entered a different room
    if ((roomX != newPos.x) || (roomY != newPos.y)) {

        cout << "entered new room: " << newPos.x << " " << newPos.y << endl;

        // save process list
        roomLists[roomX][roomY] = pm->getProcessList();

        cout << "saved list" << endl;

        // load new list
        pm->loadProcessList(roomLists[newPos.x][newPos.y]);

        cout << "loaded list" << endl;

        // update current room
        roomX = newPos.x;
        roomY = newPos.y;
    }
}

// returns the current floor
Floor* LevelManager::getCurrentFloor() {
    return &curfloor;
}
