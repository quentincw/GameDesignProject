#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include "processManager.h"
#include "gameProcess.h"
#include "playerProjectile.h"
#include "enemy.h"



// constructor for process manager
ProcessManager::ProcessManager() {
    player = new PlayerProjectile(0, 0, 3.0f, 3.0f);
}

// constructor for testing targetting
ProcessManager::ProcessManager(PlayerProjectile* newProj) {
    player = newProj;
}

// updates the list of processes
void ProcessManager::updateProcesses(float deltaTime) {

    // update player
    player->Update(deltaTime);

    // update everything else
    for(int i = 0; i < processList.size(); i++){
        processList[i]->Update(deltaTime);
    }

    // update AI
    updateEnemyAI();

    // add any children to the list
    findChildren();

    // remove marked processes
    //removeMarkedProcesses();

}

// draws the objects
void ProcessManager::renderProcesses(SDL_Renderer* renderer) {

    
    for(int i = 0; i < processList.size(); i++){
        processList[i]->Render( renderer );
    }
    player->Render( renderer );
}

// loads a process list from a room
void ProcessManager::loadProcessList(std::vector<GameProcess*> newList) {
    processList = newList;
}

// returns the process list
std::vector<GameProcess*> ProcessManager::getProcessList() const {
    return processList;
}

// adds a new process to the process list
void ProcessManager::addProcess(GameProcess* newProcess) {
    processList.push_back(newProcess);
}

// iterates through the processList and removes any marked processes
void ProcessManager::removeMarkedProcesses() {
    // remove processes that are marked for deletion
    processList.erase(
        std::remove_if(processList.begin(), processList.end(), [](GameProcess* gameProcess) {
            return gameProcess->getMarkForDeletion(); 
        }),
        processList.end()
    );
}

// iterate through the processList for any that have children (add to process list)
void ProcessManager::findChildren() {

    // list of all the children to add to the process list
    std::vector<GameProcess*> childrenList;
    // the children of the current process
    std::vector<GameProcess*> processChildren;
    // the current process
    GameProcess* curProcess;

    // iterate through the vector
    for(int i = 0; i < processList.size(); i++){
        curProcess = processList[i];
        // check for children
        if(curProcess->hasChildren()){
            // get the children vector
            processChildren = curProcess->getChildren();
            // iterate through the children vector and add them to full list of children
            for(int j = 0; j < processChildren.size(); j++){
                childrenList.push_back(processChildren[j]);
            }
        }
    }
    // add children to process list
    processList.insert(processList.end(), childrenList.begin(), childrenList.end());
    

}

// gets the enemy count
int ProcessManager::getEnemyCount() const {
    return enemyCount;
}

// gives the player's position any enemies
void ProcessManager::updateEnemyAI() {
    for (auto& curProcess : processList) {
        // Attempt to cast to DerivedGameProcess
        if (auto enemy = dynamic_cast<Enemy*>(curProcess)) {
            enemy->UpdateAI(player->getHitbox());
        }
    }
}
