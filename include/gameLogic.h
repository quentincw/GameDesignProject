#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "ProcessManager.h"
#include "LevelManager.h"

class GameLogic
{
public:
    GameLogic(ProcessManager* pm, LevelManager* lm);
    
    void update();

private:
    ProcessManager* processManager;
    LevelManager*   levelManager;

    void checkCollisions();

    bool isColliding(const GameObject* a, const GameObject* b) const;

    void handleCollision(Process* p1, Process* p2, const std::string& matchedTag);
};

#endif