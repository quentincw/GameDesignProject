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
    int x = rx * (TILE_SIZE / 2);
    int y = ry * (TILE_SIZE / 2);
    
    if (obj_hitbox.x + obj_hitbox.width < x) {
        return false;
    }
    if (obj_hitbox.x > x + (TILE_SIZE / 2)) {
        return false;
    }
    if (obj_hitbox.y + obj_hitbox.height < y) {
        return false;
    }
    if (obj_hitbox.y > y + (TILE_SIZE / 2)) {
        return false;
    }
    
    return true;
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
        
        // check collisions with x tiles
        int tileRange = 2;

        // tile coordinates of the player's position
        int tileX = (procHitbox.x + (procHitbox.width / 2)) / (TILE_SIZE / 2);
        int tileY = (procHitbox.y + (procHitbox.height / 2)) / (TILE_SIZE / 2);

        // limit tileRange such that it does not reach out of bounds
        for (int x = max(0, tileX - tileRange); x < min(int(tilemapData.size()), tileX + tileRange); x++) {
            for (int y = max(0, tileY - tileRange); y < min(int(tilemapData[x].size()), tileY + tileRange); y++) {
                if (tilemapData[x][y]) {
                    if (isColliding(proc, x, y, TILE_SIZE / 2, TILE_SIZE / 2)) {
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