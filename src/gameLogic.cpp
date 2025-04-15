#include "gameLogic.h"
#include "gameProcess.h"
#include "gameObject.h"
#include "processManager.h"
#include "levelManager.h"
#include "constants.h"
#include "entity.h"

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

bool contains(const std::vector<std::string>& vec, const std::string& target) {
    return std::find(vec.begin(), vec.end(), target) != vec.end();
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
                if (contains(p2->getTags(), kv))
                {
                    if (isColliding(p1, p2))
                    {
                        handleCollision(p1, p2, kv);
                    }
                }
            }
        }
    }

    const auto& floor = levelManager->getCurrentFloor();
    const auto& tilemapData = floor->getRoomsCol();
    if (tilemapData.empty()) return;
    int mapWidth = tilemapData.size();
    int mapHeight = tilemapData[0].size();

    for (GameProcess* proc : processes)
    {
        //testing
        auto tags = proc->getTags();
        for (std::string s: tags) {
            //std::cout << s << std::endl;
        }

        //std::cout << std::endl;

        if (!proc) continue;

        auto procHitbox = proc->getHitbox();
        float px1 = procHitbox.x;
        float py1 = procHitbox.y;
        float px2 = px1 + procHitbox.width;
        float py2 = py1 + procHitbox.height;

        int leftTile = px1 / TILE_SIZE;
        int rightTile = px2 / TILE_SIZE;
        int topTile = py1 / TILE_SIZE;
        int bottomTile = py2 / TILE_SIZE;

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
                    float rx = tx * TILE_SIZE;
                    float ry = ty * TILE_SIZE;
                    if (isColliding(proc, rx, ry, TILE_SIZE, TILE_SIZE))
                    {
                        proc->handleInteraction("wall");
                    }
                }
            }
        }
    }
}

void GameLogic::handleCollision(GameProcess* p1, GameProcess* p2, const std::string& matchedTag)
{
    if (contains(p2->getTags(), "entity"))
    {
        Entity* entity = dynamic_cast<Entity*>(p2);
        if (entity)
        {
            entity->adjustHealth(p1->getDamage());
        }
    }
    
    p1->handleInteraction(matchedTag);
}