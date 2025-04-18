#include "gameLogic.h"
#include "gameProcess.h"
#include "gameObject.h"
#include "processManager.h"
#include "levelManager.h"
#include "constants.h"
#include "entity.h"

GameLogic::GameLogic(ProcessManager* pm, LevelManager* lm)
    : processManager(pm), levelManager(lm), player(pm->getPlayer()) {}

void GameLogic::update()
{
    auto processes = processManager->getProcessList();
    handleProcessCollisions(processes);
    handleWallCollisions(processes);
    handleWallCollisions({player});
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
    return (obj_hitbox.x < rx + rw) &&
           (obj_hitbox.x + obj_hitbox.width > rx) &&
           (obj_hitbox.y < ry + rh) &&
           (obj_hitbox.y + obj_hitbox.height > ry);
}

void GameLogic::handleProcessCollisions(const std::vector<GameProcess*>& processes)
{
    for (size_t i = 0; i < processes.size(); ++i)
    {
        GameProcess* p1 = processes[i];
        if (!p1) continue;

        const auto& interactions = p1->getInteractions();

        // Player-specific interaction
        if (interactions.find("player") != interactions.end())
        {
            if (isColliding(p1, player))
            {
                handleCollision(p1, player, "player");
            }
        }

        // General tag-based interaction
        for (size_t j = i + 1; j < processes.size(); ++j)
        {
            GameProcess* p2 = processes[j];
            if (!p2) continue;

            const auto& tags = p2->getTags();

            for (const auto& tag : tags)
            {
                if (interactions.find(tag) != interactions.end() && isColliding(p1, p2))
                {
                    handleCollision(p1, p2, tag);
                }
            }
        }
    }

    // Player interacting with other objects
    const auto& playerInteractions = player->getInteractions();
    for (GameProcess* proc : processes)
    {
        if (!proc) continue;

        const auto& procTags = proc->getTags();
        for (const auto& tag : procTags)
        {
            if (playerInteractions.find(tag) != playerInteractions.end())
            {
                if (isColliding(player, proc))
                {
                    handleCollision(player, proc, tag);
                }
            }
        }
    }
}

void GameLogic::handleWallCollisions(const std::vector<GameProcess*>& processes)
{
    const auto& floor = levelManager->getCurrentFloor();
    const auto& tilemapData = floor->getRoomsCol();
    if (tilemapData.empty()) return;

    int mapWidth = tilemapData.size();
    int mapHeight = tilemapData[0].size();

    for (GameProcess* proc : processes)
    {
        if (!proc) continue;

        auto procHitbox = proc->getHitbox();
        float px1 = procHitbox.x;
        float py1 = procHitbox.y;
        float px2 = px1 + procHitbox.width;
        float py2 = py1 + procHitbox.height;

        int leftTile = std::max(0, (int)((procHitbox.x + 32) / TILE_SIZE));
        int rightTile = std::min(mapWidth - 1, (int)((procHitbox.x + procHitbox.width - 1 + 32) / TILE_SIZE));
        int topTile = std::max(0, (int)((procHitbox.y + 32) / TILE_SIZE));
        int bottomTile = std::min(mapHeight - 1, (int)((procHitbox.y + procHitbox.height - 1 + 32) / TILE_SIZE));

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
    auto tags = p2->getTags();
    if (tags.find("entity") != tags.end())
    {
        Entity* entity = dynamic_cast<Entity*>(p2);
        if (entity && !entity->getMarkForDeletion())
        {
            entity->adjustHealth(p1->getDamage());
        }
    }
    
    p1->handleInteraction(matchedTag);
}