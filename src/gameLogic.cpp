#include "gameLogic.h"
#include "gameProcess.h"
#include "gameObject.h"
#include "processManager.h"
#include "levelManager.h"

GameLogic::GameLogic(ProcessManager* pm, LevelManager* lm)
    : processManager(pm), levelManager(lm)
{
}

void GameLogic::update()
{
    checkCollisions();
}

bool GameLogic::isColliding(const GameObject* a, const GameObject* b) const
{
    return (a->x < (b->x + b->width)) &&
           ((a->x + a->width) > b->x) &&
           (a->y < (b->y + b->height)) &&
           ((a->y + a->height) > b->y);
}

bool GameLogic::isColliding(const GameObject* obj, float rx, float ry, float rw, float rh) const
{
    return (obj->x < (rx + rw)) &&
           ((obj->x + obj->width) > rx) &&
           (obj->y < (ry + rh)) &&
           ((obj->y + obj->height) > ry);
}

void GameLogic::checkCollisions()
{
    auto& processes = processManager->getProcesses();
    for (size_t i = 0; i < processes.size(); ++i)
    {
        Process* p1 = processes[i];
        for (size_t j = i + 1; j < processes.size(); ++j)
        {
            Process* p2 = processes[j];
            
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

    const auto& tilemapData = levelManager->getTilemapData();
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