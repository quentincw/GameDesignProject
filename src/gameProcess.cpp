#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include "gameObject.h"
#include "gameProcess.h"

// constructor
GameProcess::GameProcess() : tags{}, childrenList{}, soundList{} {
    deleteFlag = false;
    children = false;
    sounds = false;
    radius = 0;
}

// destructor
GameProcess::~GameProcess() {}

// marks process for deletion by changing delete flag (boolean)
void GameProcess::markForDeletion() {
    deleteFlag = true;
}

// returns whether the process has children
bool GameProcess::hasChildren() const {
    return children;
}

// returns whether the process has sounds
bool GameProcess::hasSounds() const {
    return sounds;
}

// returns whether the process is marked for deletion
bool GameProcess::getMarkForDeletion() const {
    return deleteFlag;
}

// returns a vector of all the children of a process
std::vector<GameProcess*> GameProcess::getChildren(){
    children = false;
    std::vector<GameProcess*> childrenTemp = childrenList;
    childrenList.clear();
    return childrenTemp;
}

// returns a vector of all the sounds of a process
std::vector<SoundType> GameProcess::getSounds(){
    sounds = false;
    std::vector<SoundType> soundTemp = soundList;
    soundList.clear();
    return soundTemp;
}

// returns the vector of interactions
std::unordered_set<std::string> GameProcess::getInteractions() const {
    return interactions;
}

// returns a vector of tags associated with the process
std::unordered_set<std::string> GameProcess::getTags() const {
    return tags;
}

// get the damage the enemy causes to the player on contact
int GameProcess::getDamage() const {
    return damage;
}

void GameProcess::handleInteraction(const std::string tag) {
}

