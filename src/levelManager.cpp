#include "gameProcess.h"
#include "gameObject.h"
#include "constants.h"
#include "levelManager.h"
#include "floor.h"
#include "enemyFactory.h"
#include "gameDoor.h"
#include "stairway.h"
#include <random>
#include <ctime>
#include <algorithm>
#include <set>
#include <iostream>
#include "alienQueen.h"
#include "healthPickup.h"
#include "deadSoldier.h"
using namespace std;

LevelManager::LevelManager() {
    mt19937 gen(rd()); 
    floorNumber = 1;
}

void LevelManager::genNextFloor(GameProcess* player) {

    if(floorNumber > 3) {
        return;
    }
    // generate the next floor
    switch (floorNumber) {
        case 1:
            // first floor - easy
            genFloor(1);
            break;
        case 2:
            // second floor - medium
            genFloor(2);
            break;
        case 3:
            // third floor - hard + final boss
            genFloor(3);
            break;
    }
    //player->setPosition((roomX) * TILE_SIZE, (roomY) * TILE_SIZE);
    // increment the floor number for next generation
    Rectangle rect = curfloor->getCurRoomRect();
    player->setPosition((rect.x * TILE_SIZE) + 100, (rect.y * TILE_SIZE) + 100);
    floorNumber = floorNumber + 1;

}


void LevelManager::genFloor(int level) {
    curfloor = new Floor();
    // different parameters for floor generation
    switch (level) {
        case 1:
            // 3, 4, 5
            curfloor->gen(1, 3, 5, 14);
            break;
        case 2:
            // 4, 5, 6
            curfloor->gen(2, 6, 6, 16);
            break;
        case 3:
            // 4, 5, 6
            curfloor->gen(3, 4, 4, 7);
            break;
        default:
            curfloor->gen(1, 5, 5, 14);
    }

    // set the current room to the start room
    RoomPosition newPos = curfloor->getRoomPos();
    roomX = newPos.x;
    roomY = newPos.y;

    // get the room coordinates
    vector<vector<int>> roomPos = curfloor->getRoomsPos();
    
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
    vector<Rectangle> rooms = curfloor->getRoomDimensions();

    // 1 == room, 0 == gap
    int count = 0;
    Rectangle curRect;
    GameProcess* enemy = nullptr;
    vector<vector<int>> roomsCol = curfloor->getRoomsCol();
    GameProcess* gameDoor = nullptr;

    //cout << "roomsCol size x: " << roomsCol.size() << endl;
    cout << "how many rooms: " << rooms.size() << endl;

    // loop through every room
    for (size_t i = 0; i < roomPos.size(); ++i) {
        for (size_t j = 0; j < roomPos[i].size(); ++j) {
            // if there is not a gap in this spot
            if(roomPos[i][j] == 1) {
                // get the next rectangle
                Rectangle curRect = rooms[count];
                // cout << "RoomPos " << i << " " << j << ": " << curRect.x << " " << curRect.y << endl;
                // boss room check
                vector<int> boss_loc = curfloor->getBossLoc();
                if(curRect.x == boss_loc[0] && curRect.y == boss_loc[1]){
                    // add stairway to next floor
                    gameDoor = new Stairway(0, 0, 100, 100);
                    roomLists[i][j].push_back(gameDoor);
                    // fill room with boss encounter
                    fillProcessListBoss(roomLists[i][j]);
                }
                else {
                    // level filler call (fill list using the rectangle)
                    fillProcessList(roomLists[i][j]);
                }
                // find valid places for each enemy
                findValidSpots(roomLists[i][j], curRect);

                //cout << "RoomPos h/w: " << i << " " << j << ": " << curRect.width << " " << curRect.height << endl;
                
                
                // check for door on top side
                bool door = false;
                for(size_t w = 0; w < curRect.width; ++w) {
                    //cout << roomsCol[curRect.x + w][curRect.y] << " ";
                    if((door == false) && (roomsCol[curRect.x + w][curRect.y] == 0)) {
                        door = true;
                        // create a door at the position
                        gameDoor = new GameDoor((curRect.x + w - 1) * TILE_SIZE, (curRect.y - 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE * 3, 180);
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
                        gameDoor = new GameDoor((curRect.x - 2) * TILE_SIZE, (curRect.y + h - 1) * TILE_SIZE, TILE_SIZE * 3, TILE_SIZE, 90);
                        roomLists[i][j].push_back(gameDoor);
                    }
                }

                // check for door on bottom side
                door = false;
                for(size_t w = 0; w < curRect.width; ++w) {
                    if((door == false) && (roomsCol[curRect.x + w][curRect.y + curRect.height] == 0)) {
                        door = true;
                        // create a door at the position
                        gameDoor = new GameDoor((curRect.x + w - 1) * TILE_SIZE, (curRect.y + curRect.height + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE * 3, 0);
                        roomLists[i][j].push_back(gameDoor);
                    }
                }

                // check for door on right side
                door = false;
                for(size_t h = 0; h < curRect.height; ++h) {
                    if((door == false) && (roomsCol[curRect.x + curRect.width][curRect.y + h] == 0)) {
                        door = true;
                        // create a door at the position
                        gameDoor = new GameDoor((curRect.x + curRect.width + 1) * TILE_SIZE, (curRect.y + h - 1) * TILE_SIZE, TILE_SIZE * 3, TILE_SIZE, -90);
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
    
    // flag for deleting first room enemies
    startDelete = false;


}

// takes a process list and a room. Finds valid locations inside the room to place the enemies
void LevelManager::findValidSpots(vector<GameProcess*>& curList, Rectangle rectangle) {


    // random number ranges (height/width)
    uniform_real_distribution<> width(2, rectangle.width - 2);
    uniform_real_distribution<> height(2, rectangle.height- 2);

    // potential position (tile)
    int x,y;
    // boolean for loop
    bool invalid = true;
    // height and width of process
    int pHeight, pWidth;

    // vector of valid/ invalid locations
    vector<vector<int>> roomsCol = curfloor->getRoomsCol();

    // loop through each process
    for (size_t i = 0; i < curList.size(); ++i) {
        invalid = true;
        while(invalid){

            // generate a position
            x = width(gen) + rectangle.x;
            y = height(gen) + rectangle.y;

            pHeight = (curList[i]->getHitbox().height) / TILE_SIZE;
            pWidth = (curList[i]->getHitbox().width) / TILE_SIZE;

            // loop through each tile that touches the hitbox
            invalid = false;
            int offset = 1;
            for(int i = x - offset; i < x + pWidth + offset; i++){
                for(int j = y - offset; j < y + pHeight + offset; j++) {
                    if(roomsCol[i][j] == 1){
                        // intersects with wall
                        invalid = true;
                    }
                }
            }
            // repeat until valid
        }
        // null pointer check
        if (curList[i] != nullptr) {
            curList[i]->setPosition(x * TILE_SIZE - 32, y * TILE_SIZE - 32);
            curList[i]->setLastPosition(x * TILE_SIZE - 32, y * TILE_SIZE - 32);
        } else {
            cout << "Null pointer encountered at index " << i << endl;
        }
        
    }

}
// fills a process list with a boss encounter
void LevelManager::fillProcessListBoss(vector<GameProcess*>& curList) {

    GameProcess* enemy;

    if(floorNumber == 1){
        // Alpha Spewer
        enemy = EnemyFactory::createEnemy(EnemyFactory::EnemyType::ALPHASPEWER);
        curList.push_back(enemy);
        return;
    }
    else if(floorNumber == 2){
        // Alpha Charger Duo
        enemy = EnemyFactory::createEnemy(EnemyFactory::EnemyType::ALPHACHARGER);
        curList.push_back(enemy);
        enemy = EnemyFactory::createEnemy(EnemyFactory::EnemyType::ALPHACHARGER);
        curList.push_back(enemy);
        return;
    }
    else if(floorNumber == 3){
        AlienQueen* alienQueen = new AlienQueen(0,0);
        curList.push_back(alienQueen);
        return;
    }      
}

// fills a process list based on a difficulty level
void LevelManager::fillProcessList(vector<GameProcess*>& curList) {

    // add dead soldier to room
    DeadSoldier* deadSoldier = new DeadSoldier(0, 0);
    curList.push_back(deadSoldier);

    // add health pack to room
    HealthPickup* healthPickup = new HealthPickup(0, 0, -20, 0, 0);
    curList.push_back(healthPickup);

    // random enemy generator
    // increase for every enemy added
    uniform_int_distribution<> enemyDist(0, 7);

    // get difficulty
    int difficulty;
    switch (floorNumber) {
        case 1:
            // first floor = easy
            difficulty = 10;
            break;
        case 2:
            // second floor = medium
            difficulty = 15;
            break;
        case 3:
            // third floor = hard
            difficulty = 20;
            break;
        default:
            difficulty = 15;
            break;
    }
 
    GameProcess* enemy = nullptr;

    while(difficulty > 2) {
        // generate an enemy number
        int enemyType = enemyDist(gen);
        switch (enemyType) {
            case 0:
                // spawn roach
                enemy = EnemyFactory::createEnemy(EnemyFactory::EnemyType::ROACH);
                difficulty-=1;
                break;
            case 1:
                // spawn spitter
                enemy = EnemyFactory::createEnemy(EnemyFactory::EnemyType::SPITTER);
                difficulty-=2;
                break;
            case 2:
                // spawn spewer
                enemy = EnemyFactory::createEnemy(EnemyFactory::EnemyType::SPEWER);
                difficulty-=3;
                break;
            case 3:
                // spawn spawner
                enemy = EnemyFactory::createEnemy(EnemyFactory::EnemyType::SPAWNER);
                difficulty-=3;
                break;
            case 4:
                // spawn Exploder
                enemy = EnemyFactory::createEnemy(EnemyFactory::EnemyType::EXPLODER);
                difficulty-=2;
                break;
            case 5:
                // spawn Alpha Spitter
                enemy = EnemyFactory::createEnemy(EnemyFactory::EnemyType::ALPHASPITTER);
                difficulty-=5;
                break;
            case 6:
                // spawn Charger
                enemy = EnemyFactory::createEnemy(EnemyFactory::EnemyType::CHARGER);
                difficulty-=5;
                break;
            case 7:
                // spawn Burrower
                enemy = EnemyFactory::createEnemy(EnemyFactory::EnemyType::BURROWER);
                difficulty-=4;
                break;
            default:
                break;
        }
        // add enemy to the list
        if (enemy != nullptr) {
            curList.push_back(enemy);
        }
    }
}


void LevelManager::setCurrentRoom(ProcessManager* pm) {

    //get the player
    GameProcess* player = pm->getPlayer();
    int pX = player->getHitbox().x;
    int pY = player->getHitbox().y;

    // set the current room within the floor
    curfloor->setCurRoom(pX / TILE_SIZE, pY / TILE_SIZE);

    // get the current room
    RoomPosition newPos = curfloor->getRoomPos();


    // check if the player entered a different room
    if ((roomX != newPos.x) || (roomY != newPos.y)) {

        // save process list
        roomLists[roomX][roomY] = pm->getProcessList();

        // delete the list if it is the first room
        if(startDelete == false){
            roomLists[newPos.x][newPos.y].clear();
            startDelete = true;
        }


        // load new list
        pm->loadProcessList(roomLists[newPos.x][newPos.y]);

        // update current room
        roomX = newPos.x;
        roomY = newPos.y;
    }
}

// returns the current floor
Floor* LevelManager::getCurrentFloor() {
    return curfloor;
}

// returns the current floor number
int LevelManager::getFloorNumber(){
	return floorNumber;
}
