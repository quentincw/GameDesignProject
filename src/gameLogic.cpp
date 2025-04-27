#include "gameLogic.h"
#include "gameProcess.h"
#include "gameObject.h"
#include "processManager.h"
#include "levelManager.h"
#include "constants.h"
#include "entity.h"
#include "stairway.h"
#include "iostream"

GameLogic::GameLogic(ProcessManager* pm, LevelManager* lm)
    : processManager(pm), levelManager(lm), player(pm->getPlayer()) {}

void GameLogic::update()
{
    auto processes = processManager->getProcessList();

    // Positional updates
    updateLastPositions(processes);
    updateLastPositions({player});

    // Collisions
    checkProcessCollisions(processes);
    checkWallCollisions(processes);
    checkWallCollisions({player});

    // Floor Completion
    checkFloorCompletion(processes);
}

inline TileRange GameLogic::getTileRange(float x, float y, float w, float h) const
{
    const auto& floor = levelManager->getCurrentFloor();
    const auto& tilemapData = floor->getRoomsCol();

    if (tilemapData.empty()) return {0, 0, 0, 0};

    int mapWidth = tilemapData.size();
    int mapHeight = tilemapData[0].size();

    float px1 = x + 32;
    float py1 = y + 32;
    float px2 = px1 + w;
    float py2 = py1 + h;

    return {
        std::max(0, (int)(px1 / TILE_SIZE)),
        std::min(mapWidth - 1, (int)((px2 - 1) / TILE_SIZE)),
        std::max(0, (int)(py1 / TILE_SIZE)),
        std::min(mapHeight - 1, (int)((py2 - 1) / TILE_SIZE))
    };
}

bool GameLogic::isLegalPosition(const GameObject* obj, float x, float y) const
{
    // Check against tilemap
    const auto& floor = levelManager->getCurrentFloor();
    const auto& tilemapData = floor->getRoomsCol();
    if (tilemapData.empty()) return true;

    auto hb = obj->getHitbox();
    auto tr = getTileRange(x, y, hb.width, hb.height);

    for (int tx = tr.left; tx <= tr.right; tx++) {
        for (int ty = tr.top; ty <= tr.bottom; ty++) {
            if (tilemapData[tx][ty] == 1) {
                return false;
            }
        }
    }

    // Check against doors
    const auto& processes = processManager->getProcessList();
    for (const auto* process : processes)
    {
        if (!process) continue;
        const auto& tags = process->getTags();
        if (tags.find("door") != tags.end())
        {
            if (isColliding(obj, process))
            {
                return false;
            }
        }
    }

    return true;
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
    return (obj_hitbox.x <= rx + rw) &&
           (obj_hitbox.x + obj_hitbox.width >= rx) &&
           (obj_hitbox.y <= ry + rh) &&
           (obj_hitbox.y + obj_hitbox.height >= ry);
}

void GameLogic::checkProcessCollisions(const std::vector<GameProcess*>& processes)
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
        for (size_t j = 0; j < processes.size(); ++j)
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

void GameLogic::checkWallCollisions(const std::vector<GameProcess*>& processes)
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
        auto tr = getTileRange(procHitbox.x, procHitbox.y, procHitbox.width, procHitbox.height);

        for (int tx = tr.left; tx <= tr.right; tx++)
        {
            for (int ty = tr.top; ty <= tr.bottom; ty++)
            {
                if (tilemapData[tx][ty] == 1)
                {
                    float rx = tx * TILE_SIZE - 32;
                    float ry = ty * TILE_SIZE - 32;

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

            std::cout << "doing damage: " << p1->getDamage() << ::endl;
        }
    }
    
    p1->handleInteraction(matchedTag);
}

void GameLogic::updateLastPositions(const std::vector<GameProcess*>& processes)
{
    for (GameProcess* proc : processes)
    {
        if (!proc) continue;

        auto hb = proc->getHitbox();
        float currX = hb.x;
        float currY = hb.y;
        float lastX = proc->getLastX();
        float lastY = proc->getLastY();

        // Full position is legal
        if (isLegalPosition(proc, currX, currY))
        {
            proc->setLastPosition(currX, currY);
        }

        // Only X is legal (slide vertically)
        else if (isLegalPosition(proc, currX, lastY))
        {
            proc->setLastPosition(currX, lastY);
        }

        // Only Y is legal (slide horizontally)
        else if (isLegalPosition(proc, lastX, currY))
        {
            proc->setLastPosition(lastX, currY);
        }
    }
}

void GameLogic::checkFloorCompletion(const std::vector<GameProcess*>& processes)
{
    for (GameProcess* proc : processes)
    {
        auto tags = proc->getTags();

        if (tags.find("stairway") != tags.end())
        {
            if (dynamic_cast<Stairway*>(proc)->isTriggered()) {
                levelManager->genNextFloor(player);           
            }
        }
    }
}