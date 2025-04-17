#include "gameLogic.h"
#include "gameProcess.h"
#include "gameObject.h"
#include "processManager.h"
#include "levelManager.h"
#include "constants.h"
#include "entity.h"

GameLogic::GameLogic(ProcessManager* pm, LevelManager* lm, Player1* pl)
    : processManager(pm), levelManager(lm), player(pl)
{
    processManager = pm;
    levelManager = lm;
    player = pl;
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
    //std::cout << "checking collision" << std::endl;
    auto a_hitbox = a->getHitbox();
    auto b_hitbox = b->getHitbox();

    // std::cout << "A hitbox: (" << a_hitbox.x << ", " << a_hitbox.y << ", "
    //           << a_hitbox.width << ", " << a_hitbox.height << ")" << std::endl;

    // std::cout << "B hitbox: (" << b_hitbox.x << ", " << b_hitbox.y << ", "
    //           << b_hitbox.width << ", " << b_hitbox.height << ")" << std::endl;


    bool t = (a_hitbox.x < (b_hitbox.x + b_hitbox.width)) &&
           ((a_hitbox.x + a_hitbox.width) > b_hitbox.x) &&
           (a_hitbox.y < (b_hitbox.y + b_hitbox.height)) &&
           ((a_hitbox.y + a_hitbox.height) > b_hitbox.y);

    //std::cout << t << endl;
    return t;
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

    // for (auto* proc : processes) {
    // if (!proc) {
    //     std::cout << "nullptr process" << std::endl;
    //     continue;
    // }

    // std::cout << " | Tags: ";
    // for (const auto& tag : proc->getTags()) std::cout << tag << " ";
    // std::cout << std::endl;
    // }

    for (size_t i = 0; i < processes.size(); ++i)
    {
        GameProcess* p1 = processes[i];
        for (size_t j = i + 1; j < processes.size(); ++j)
        {
            GameProcess* p2 = processes[j];
            
            if (!p1 || !p2) 
                continue;

            const auto& interactions = p1->getInteractions();


            if (interactions.find("player") != interactions.end())
            {
                for (auto i: p1->getTags()) {
                    std::cout << i;
                }

                std::cout << std::endl;
                if (isColliding(p1, player))
                {

                    std::cout << "player collision" << std::endl;
                    handleCollision(p1, player, "player");
                }
            }

            for (const auto& kv : interactions)
            {
                //std::cout << kv << std::endl;
                auto tags = p2->getTags();
                if (tags.find(kv) != tags.end())
                {

                    if (isColliding(p1, p2))
                    {
                        handleCollision(p1, p2, kv);

                        std::cout << "process collision" << std::endl;
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
                    
                    // std::cout << tx << std::endl;
                    // std::cout << ty << std::endl;
                    // std::cout << rx << std::endl;
                    // std::cout << ry << std::endl;
                    // std::cout << std::endl;

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
        if (entity)
        {
            entity->adjustHealth(p1->getDamage());
        }
    }
    
    p1->handleInteraction(matchedTag);
}