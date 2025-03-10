#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include "gameProcess.h"



class ProcessManager {

    public:

        // constructor for process manager
        ProcessManager();

        // updates the list of processes
        void updateProcesses(float deltaTime);

        // draws the object
        void renderProcesses(SDL_Renderer* renderer);

        // loads a process list from a room
        void loadProcessList(std::vector<GameProcess*> newList);

        // returns the process list
        std::vector<GameProcess*> getProcessList() const;

        // adds a new process to the process list
        void addProcess(GameProcess newProcess);

    private:

        // vector of all the processes
        std::vector<GameProcess*> processList;

        // iterates through the processList and removes any marked processes
        void removeMarkedProcesses();

        // iterate through the processList for any that have children (add to process list)
        void findChildren();



};