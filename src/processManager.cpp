#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include "processManager.h"
#include "gameProcess.h"
#include "playerProjectile.h"
#include "enemy.h"
#include "Player1.h"
#include "stairway.h"
#include "gameDoor.h"
#include <algorithm>
#include <iostream>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

// constructor for process manager
ProcessManager::ProcessManager() {
    player = new Player1(0, 0);
}

// constructor for testing targetting
ProcessManager::ProcessManager(Player1* newPlayer) {
    player = newPlayer;
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

    // add any sounds to the sound list
	findSounds();

    // remove marked processes
    removeMarkedProcesses();

}

// draws the objects
void ProcessManager::renderProcesses(SDL_Renderer* renderer) {

    for(int i = 0; i < processList.size(); i++){
        processList[i]->Render( renderer );
    }
    player->Render( renderer );
}

// draws the objects based on the camera's postion
void ProcessManager::renderProcessesCam(SDL_Renderer* renderer, int camX, int camY) {

    for(int i = 0; i < processList.size(); i++){
        processList[i]->RenderCam( renderer, camX, camY );
    }
    player->RenderCam( renderer, camX, camY );
}

// loads a process list from a room
void ProcessManager::loadProcessList(std::vector<GameProcess*> newList) {
    processList = newList;
        for (auto& curProcess : processList) {
            // check if the current process is an door
            if (auto door = dynamic_cast<GameDoor*>(curProcess)) {
				soundList.push_back(SoundType::DOOR_CLOSE);
            }
		}
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

	// getting the player if it has a projectile or blood stain
	if (player->hasChildren()){
		processChildren = player->getChildren();
        // iterate through the children vector and add them to full list of children
        for(int j = 0; j < processChildren.size(); j++){
            childrenList.push_back(processChildren[j]);
        }
	}

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

// iterate through the processList for any that have children (add to process list)
void ProcessManager::findSounds() {
    // the sounds of the current process
    std::vector<SoundType> curSoundList;
    // the current process
    GameProcess* curProcess;

	// getting the player sounds
	if (player->hasSounds()){
		curSoundList = player->getSounds();
        // iterate through the sound vector and add them to full list of sounds
        for(int j = 0; j < curSoundList.size(); j++){
            soundList.push_back(curSoundList[j]);
        }
	}

    // iterate through the vector
    for(int i = 0; i < processList.size(); i++){
        curProcess = processList[i];
        // check for sounds
        if(curProcess->hasSounds()){
            // get the children vector
            curSoundList = curProcess->getSounds();
            // iterate through the sound vector and add them to full list of sounds
            for(int j = 0; j < curSoundList.size(); j++){
                soundList.push_back(curSoundList[j]);
            }
        }
    }
}

// iterate through the processList and get every sound
std::vector<SoundType> ProcessManager::getSoundList() {
	std::vector<SoundType> tempSoundList = soundList;
	soundList.clear();
	return tempSoundList;
}

// gets the enemy count
int ProcessManager::getEnemyCount() const {
    return enemyCount;
}

// gives the player's position any enemies
void ProcessManager::updateEnemyAI() {
    enemyCount = 0;
    for (auto& curProcess : processList) {
        // check if the current process is an enemy
        if (auto enemy = dynamic_cast<Enemy*>(curProcess)) {
            enemy->UpdateAI(player->getHitbox());
            enemyCount++;
        }
    }
    // all enemies are dead
    if(enemyCount == 0){
        for (auto& curProcess : processList) {
            // check if the current process is an door
            if (auto door = dynamic_cast<GameDoor*>(curProcess)) {
                door->markForDeletion();
				soundList.push_back(SoundType::DOOR_OPEN);
            }
            // check if current process is a stairway
            else if (auto stairs = dynamic_cast<Stairway*>(curProcess)) {
                stairs->openStairs();
            }
        }
    }
}

// returns the player's position
GameProcess* ProcessManager::getPlayer() {
    return player;
}
