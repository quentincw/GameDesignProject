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

        // draws the object
        void renderProcesses(SDL_Renderer* renderer);

        // draws the objects based on the camera position
        void renderProcessesCam(SDL_Renderer* renderer, int camX, int camY);

        // loads a process list from a room
        void loadProcessList(std::vector<GameProcess*> newList);

        // returns the process list
        std::vector<GameProcess*> getProcessList() const;

        // adds a new process to the process list
        void addProcess(GameProcess* newProcess);

        // gets the player object
        GameProcess* getPlayer();

        // gets the enemy count
        int getEnemyCount() const;

    private:

        // list of all the processes
        std::vector<GameProcess*> processList;

        // player object
        Player1* player;

        // number of enemies in the process list
        int enemyCount;

        // iterates through the processList and removes any marked processes
        void removeMarkedProcesses();

        // iterate through the processList for any that have children (add to process list)
        void findChildren();

        // gives the player's position any enemies
        void updateEnemyAI();




};