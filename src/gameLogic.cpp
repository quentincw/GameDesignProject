#include "gameLogic.h"
#include "gameProcess.h"
#include "gameObject.h"
#include "processManager.h"
#include "levelManager.h"

GameLogic::GameLogic(ProcessManager* pm, LevelManager* lm)
    : processManager(pm), levelManager(lm)
{
    processManager = pm;
    levelManager = lm;
}

void GameLogic::update()
{
    checkCollisions();
}

bool GameLogic::isColliding(const GameObject* a, const GameObject* b) const
{
    auto a_hitbox = a->getHitbox();
    auto b_hitbox = b->getHitbox();
    return (a_hitbox.x < (b_hitbox.x + b_hitbox.width)) &&
           ((a_hitbox.x + a_hitbox.width) > b_hitbox.x) &&
           (a_hitbox.y < (b_hitbox.y + b_hitbox.height)) &&
           ((a_hitbox.y + a_hitbox.height) > b_hitbox.y);
}

bool GameLogic::isColliding(const GameObject* obj, float rx, float ry, float rw, float rh) const
{
    auto obj_hitbox = obj->getHitbox();
    return (obj_hitbox.x < (rx + rw)) &&
           ((obj_hitbox.x + obj_hitbox.width) > rx) &&
           (obj_hitbox.y < (ry + rh)) &&
           ((obj_hitbox.y + obj_hitbox.height) > ry);
}

void GameLogic::checkCollisions()
{
    auto processes = processManager->getProcessList();
    for (size_t i = 0; i < processes.size(); ++i)
    {
        GameProcess* p1 = processes[i];
        for (size_t j = i + 1; j < processes.size(); ++j)
        {
            GameProcess* p2 = processes[j];
            
            if (!p1 || !p2) 
                continue;

            const auto& interactions = p1->getInteractions();
            
            for (const auto& kv : interactions)
            {
                if (p2->hasTag(kv.first))
                {
                    if (isColliding(p1, p2))
                    {
                        handleCollision(p1, p2, kv.first);
                    }
                }
            }
        }
    }

    const auto& tilemapData = levelManager->getTilemap();
    if (tilemapData.empty()) return;
    int mapWidth = tilemapData.size();
    int mapHeight = tilemapData[0].size();
    int tileSize = levelManager->getTileSize(); // this may be in constants file

    for (Process* proc : processes)
    {
        if (!proc) continue;
        float px1 = proc->x;
        float py1 = proc->y;
        float px2 = px1 + proc->width;
        float py2 = py1 + proc->height;

        int leftTile = px1 / tileSize;
        int rightTile = px2 / tileSize;
        int topTile = py1 / tileSize;
        int bottomTile = py2 / tileSize;

        if (leftTile < 0) leftTile = 0;
        if (rightTile >= mapWidth) rightTile = mapWidth - 1;
        if (topTile < 0) topTile = 0;
        if (bottomTile >= mapHeight) bottomTile = mapHeight - 1;

        for (int tx = leftTile; tx <= rightTile; tx++)
        {
            for (int ty = topTile; ty <= bottomTile; ty++)
            {
                if (tilemapData[tx][ty] == 1)
                {
                    float rx = tx * tileSize;
                    float ry = ty * tileSize;
                    if (isColliding(proc, rx, ry, tileSize, tileSize))
                    {
                        proc->handleInteraction("wall");
                    }
                }
            }
        }
    }
}

void GameLogic::handleCollision(Process* p1, Process* p2, const std::string& matchedTag)
{
    //p2->adjustHealth(p1->getInteractions().at(matchedTag)); // might be doing damage as a field now
    p2->adjustHealth(p1->getDamage());
    p1->handleInteraction(matchedTag);
}