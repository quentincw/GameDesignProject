#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "roach.h"
#include "spitter.h"
#include "spewer.h"
#include "spawner.h"

class EnemyFactory {

    public:
        
        // enum class for enemy type
        enum class EnemyType {
            ROACH,
            SPITTER,
            SPEWER,
            SPAWNER,
            EXPLODER
        };

        // create and return an enemy of the type provided
        static GameProcess* createEnemy(EnemyType type);

};

#endif