#include "oldLogic.h"
#include "constants.h"
#include "testWall.h"
#include "gameDoor.h"
#include "pickup.h"
#include "spitterProjectile.h"

OldGameLogic::OldGameLogic(ProcessManager* pm, LevelManager* lm)
    : processManager(pm), levelManager(lm)
{
    processManager = pm;
    levelManager = lm;
}

void OldGameLogic::update() {

    // get the player
    GameProcess* player = processManager->getPlayer();

    // check player - wall collisions
    wallCollision(player);

    // check process - wall collisions
    processWallCollision();

    // check player - process collisions
    playerProcessCollisions(player);

    // check process - process collisions
    processProcessCollisions();

}

bool OldGameLogic::checkCollision(GameObject* rect1, GameObject* rect2){
    Rectangle hitbox1 = rect1->getHitbox();
    Rectangle hitbox2 = rect2->getHitbox();

    if((hitbox1.x + hitbox1.width >= hitbox2.x) &&
       (hitbox1.x <= hitbox2.x + hitbox2.width) &&
       (hitbox1.y + hitbox1.height >= hitbox2.y) &&
       (hitbox1.y <= hitbox2.y + hitbox2.height)) {

        return true;
    }
    return false;

}

void OldGameLogic::processProcessCollisions() {

    // current process pointer
    GameProcess* curProcess;
    GameProcess* target;
    // current process list
    vector<GameProcess*> curProcesses;
    curProcesses = processManager->getProcessList();
    bool playerProj = false;

    // loop through process list
    for(int i = 0; i < curProcesses.size(); i++){
        curProcess = curProcesses[i];

        // projectile - door collision
        // player projectile - enemy collision
        playerProj = false;
        if(auto projectile = dynamic_cast<Projectile*>(curProcess)){
            if(auto pProjectile = dynamic_cast<PlayerProjectile*>(projectile)){
                playerProj = true;
            }
            for(int j = 0; j < curProcesses.size(); j++){
                target = curProcesses[j];
                // if the target is a door
                if(auto door = dynamic_cast<GameDoor*>(target)){
                    if(checkCollision(target, projectile)){
                        projectile->markForDeletion();
                    }
                }
                // if the target is an enemy and player projectile is true
                else if(playerProj){
                    if(auto enemy = dynamic_cast<Enemy*>(target)){
                        if(checkCollision(target, projectile)){
                            projectile->markForDeletion();
                            enemy->adjustHealth(projectile->getDamage());
                        }
                    }
                }
            }
        }
    }
}

void OldGameLogic::playerProcessCollisions(GameProcess* player) {

    // current process pointer
    GameProcess* curProcess;
    // current process list
    vector<GameProcess*> curProcesses;
    curProcesses = processManager->getProcessList();

    Player1* player1 = dynamic_cast<Player1*>(player);


    // loop through process list
    for(int i = 0; i < curProcesses.size(); i++){
        curProcess = curProcesses[i];
        
        // check collisions
        if(checkCollision(player, curProcess)){

            // collision occured
            // find out what current process is

            // door = treat as wall
            if(auto wall = dynamic_cast<GameDoor*>(curProcess)){
                moveInbounds(wall, player);
            }
            // projectile = take damage, delete projectile
            else if(auto projectile = dynamic_cast<SpitterProjectile*>(curProcess)){
                player1->adjustHealth(projectile->getDamage());
                projectile->markForDeletion();
                player1->spawnBloodStain();
            }
            // enemy = take contact damage
            else if(auto enemy = dynamic_cast<Enemy*>(curProcess)){
                player1->adjustHealth(enemy->getDamage());
                player1->spawnBloodStain();
            }
            else if(auto pickup = dynamic_cast<Pickup*>(curProcess)){
                player1->adjustHealth(-(pickup->getStats().health));
                pickup->markForDeletion();
            }


        }
    }
}

int OldGameLogic::moveInbounds(GameObject* rect1, GameObject* rect2){
    Rectangle hitbox1 = rect1->getHitbox();
    Rectangle hitbox2 = rect2->getHitbox();

    Point center1 = rect1->getCenter(&hitbox1);
    Point center2 = rect2->getCenter(&hitbox2);

    // left side collision
    if(center2.x <= hitbox1.x){
        rect2->setPosition(hitbox1.x - hitbox2.width, hitbox2.y);
        return 1;
    }
    // right side collision
    else if(center2.x >= hitbox1.x + hitbox1.width){
        rect2->setPosition(hitbox1.x + hitbox1.width, hitbox2.y);
        return 3;
    }
    // top side collision
    if(center2.y <= hitbox1.y){
        rect2->setPosition(hitbox2.x, hitbox1.y - hitbox2.height);
        return 2;
    }
    // bottom side collision
    else if(center2.y >=  hitbox1.y + hitbox1.height){
        rect2->setPosition(hitbox2.x, hitbox1.y + hitbox1.height);
        return 4;
    }
    return 0;
}

void OldGameLogic::processWallCollision() {


    // current process pointer
    GameProcess* curProcess;
    // current process list
    vector<GameProcess*> curProcesses;
    curProcesses = processManager->getProcessList();

    // loop through process list
    for(int i = 0; i < curProcesses.size(); i++){
        curProcess = curProcesses[i];
        // skip doors
        if(auto wall = dynamic_cast<GameDoor*>(curProcess)){
            continue;
        }
        wallCollision(curProcess);
    }



}

void OldGameLogic::wallCollision(GameProcess* curProcess) {

    // get the current floor
    Floor* floor = levelManager->getCurrentFloor();

    // get the 2D array of walkable/ unwalkable area
    vector<vector<int>> roomsCol = floor->getRoomsCol();

    // get the current tile of the process
    int x = (curProcess->getHitbox().x + 32) / TILE_SIZE;
    int y = (curProcess->getHitbox().y + 32) / TILE_SIZE;

    // check 
    //cout << roomsCol[x][y] << endl;

    // check the nine tiles around the process for collision
    // [-1, +1] [0, +1] [+1, +1] 
    // [-1,  0] [0,  0] [+1,  0] 
    // [-1, -1] [0, -1] [+1, -1]

    // create a gameObject to represent the tile 
    TestWall wall1(0, 0, TILE_SIZE, TILE_SIZE);

    int xWall, yWall, code;

    // iterate through each of the 9 positions
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++) {

            // set the x and y of the wall
            xWall = x + i;
            yWall = y + j;

            // skip if out of bounds
            if((xWall < 0)||(yWall < 0)){
                continue;
            }

            // skip if walkable tile
            if(roomsCol[xWall][yWall] == 0){
                //cout << "walkable" << endl;
                continue;
            }

            //cout << "wallX: " << xWall * TILE_SIZE << "   wallY: " << yWall * TILE_SIZE << endl;

            // set the wall x,y to the tile x,y
            wall1.setPosition((xWall * TILE_SIZE) - 32, (yWall * TILE_SIZE) - 32 );

            // check collision
            if(checkCollision(&wall1, curProcess)){
                code = moveInbounds(&wall1, curProcess);
                if(auto projectile = dynamic_cast<Projectile*>(curProcess)){
                    curProcess->markForDeletion();
                }
            }


        }
    }



}