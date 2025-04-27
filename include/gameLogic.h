#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "processManager.h"
#include "levelManager.h"

struct TileRange {
    int left, right, top, bottom;
};

class GameLogic
{
public:
    GameLogic(ProcessManager* pm, LevelManager* lm);
    
    void update();

private:
    ProcessManager* processManager;
    LevelManager* levelManager;
    GameProcess* player;

    // Checks if two things are colliding
    bool isColliding(const GameObject* a, const GameObject* b) const;
    bool isColliding(const GameObject* obj, float rx, float ry, float rw, float rh) const;

    // Checks if the given position is not overlapping a wall or door
    bool isLegalPosition(const GameObject* obj, float x, float y) const;

    // Checks collisions between processes
    void checkProcessCollisions(const std::vector<GameProcess*>& processes);

    // Checks for wall collisions
    void checkWallCollisions(const std::vector<GameProcess*>& processes);

    // Adjusts health and gives collision information to processes
    void handleCollision(GameProcess* p1, GameProcess* p2, const std::string& matchedTag);

    // Updates the last/stored position of each process
    void updateLastPositions(const std::vector<GameProcess*>& processes);

    // Checks if the floor is complete
    void checkFloorCompletion(const std::vector<GameProcess*>& processes);

    // Returns the corner coords of the range of tiles that 
    // could interact with the provided x, y, w, h
    inline TileRange getTileRange(float x, float y, float w, float h) const;
};

#endif