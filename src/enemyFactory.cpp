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
        case EnemyType::SPAWNER:
            enemy = new Spawner(0,0);
            return enemy;
        case EnemyType::EXPLODER:
            enemy = new Exploder(0,0);
            return enemy;
        case EnemyType::ALPHASPITTER:
            enemy = new AlphaSpitter(0,0);
            return enemy;
        case EnemyType::CHARGER:
            enemy = new Charger(0,0);
            return enemy;
        case EnemyType::ALPHACHARGER:
            enemy = new AlphaCharger(0,0);
            return enemy;
        case EnemyType::ALPHASPEWER:
            enemy = new AlphaSpewer(0,0);
            return enemy;
        case EnemyType::BURROWER:
            enemy = new Burrower(0,0);
            return enemy;
        default:
            // return nullptr if invalid type
            return enemy;
    }
}