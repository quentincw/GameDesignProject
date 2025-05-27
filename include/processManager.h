#ifndef _PROCESSMANAGER_H_
#define _PROCESSMANAGER_H_

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include "gameProcess.h"
#include "playerProjectile.h"
#include "enemy.h"
#include "Player1.h"



class ProcessManager {

    public:

        // constructor for process manager
        ProcessManager();

        // constructor for testing targetting
        ProcessManager(Player1* newPlayer);

        // updates the list of processes
        void updateProcesses(float deltaTime);

        // loads a process list from a room
        void loadProcessList(std::vector<GameProcess*> newList);

        // returns the process list
        std::vector<GameProcess*> getProcessList() const;

        // iterate through the processList and get every sound
        std::vector<SoundType> getSoundList();

        // adds a new process to the process list
        void addProcess(GameProcess* newProcess);

        // gets the player object
        GameProcess* getPlayer();

        // gets the enemy count
        int getEnemyCount() const;

    private:

        // list of all the processes
        std::vector<GameProcess*> processList;
		
		// list of all the sounds
        std::vector<SoundType> soundList;

        // player object
        Player1* player;

        // number of enemies in the process list
        int enemyCount;

        // iterates through the processList and removes any marked processes
        void removeMarkedProcesses();

        // iterate through the processList for any that have children (add to process list)
        void findChildren();
		
		// iterate through the processList for any sounds (add to sound list)
        void findSounds();

        // gives the player's position any enemies
        void updateEnemyAI();

        // delete bloodstains if too many things in list
        void manageSize();

};

#endif /* _PROCESSMANAGER_H_ */