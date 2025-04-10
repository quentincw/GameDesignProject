#include "enemyFactory.h"

// create and return an enemy of the type provided
GameProcess* EnemyFactory::createEnemy(EnemyType type) {

    // pointer to return
    GameProcess* enemy = nullptr;

    switch (type) {
        case EnemyType::ROACH:
            enemy = new Roach(0,0);
            return enemy;
        case EnemyType::SPITTER:
            enemy = new Spitter(0,0);
            return enemy;
        case EnemyType::SPEWER:
            enemy = new Spewer(0,0);
            return enemy;
        default:
            // return nullptr if invalid type
            return enemy;
    }
}