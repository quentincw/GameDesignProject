#ifndef OLDGAMELOGIC_H
#define OLDGAMELOGIC_H

#include "processManager.h"
#include "levelManager.h"

class OldGameLogic
{
public:
    OldGameLogic(ProcessManager* pm, LevelManager* lm);
    
    void update();

private:
    ProcessManager* processManager;
    LevelManager*   levelManager;

    bool checkCollision(GameObject* rect1, GameObject* rect2);

    int moveInbounds(GameObject* rect1, GameObject* rect2);

    void wallCollision(GameProcess* curProcess);

    void processWallCollision();

    void playerProcessCollisions(GameProcess* player);

    void processProcessCollisions();
};

#endif