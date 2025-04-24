#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "processManager.h"
#include "levelManager.h"

class GameLogic
{
public:
    GameLogic(ProcessManager* pm, LevelManager* lm);
    
    void update();

private:
    ProcessManager* processManager;
    LevelManager* levelManager;
    GameProcess* player;

    void checkCollisions();

    bool isColliding(const GameObject* a, const GameObject* b) const;
    bool isColliding(const GameObject* obj, float rx, float ry, float rw, float rh) const;

    bool isLegalPosition(const GameObject* obj, float x, float y) const;

    void checkProcessCollisions(const std::vector<GameProcess*>& processes);
    void checkWallCollisions(const std::vector<GameProcess*>& processes);
    
    void handleCollision(GameProcess* p1, GameProcess* p2, const std::string& matchedTag);

    void updateLastPositions(const std::vector<GameProcess*>& processes);
};

#endif