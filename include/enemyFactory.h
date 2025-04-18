#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "roach.h"
#include "spitter.h"
#include "spewer.h"
#include "spawner.h"
#include "exploder.h"
#include "alphaSpitter.h"
#include "charger.h"
#include "alphaCharger.h"
#include "alphaSpewer.h"
#include "burrower.h"

class EnemyFactory {

    public:
        
        // enum class for enemy type
        enum class EnemyType {
            ROACH,
            SPITTER,
            SPEWER,
            SPAWNER,
            EXPLODER,
            ALPHASPITTER,
            CHARGER,
            ALPHACHARGER,
            ALPHASPEWER,
            BURROWER
        };

        // create and return an enemy of the type provided
        static GameProcess* createEnemy(EnemyType type);

};

#endif