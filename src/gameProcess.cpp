#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include "gameObject.h"
#include "gameProcess.h"


// constructor
GameProcess::GameProcess() : tags{}, childrenList{} {
    tags.push_back("Wall");
    deleteFlag = false;
    children = false;
    radius = 0;
}

// marks process for deletion by changing delete flag (boolean)
void GameProcess::markForDeletion() {
    deleteFlag = true;
}

// returns whether the process has children
bool GameProcess::hasChildren() const {
    return children;
}

// returns whether the process is marked for deletion
bool GameProcess::getMarkForDeletion() const {
    return deleteFlag;
}

// returns a vector of all the children of a process
std::vector<GameProcess*> GameProcess::getChildren(){
    children = false;
    return childrenList;
}


// returns the vector of tags of the process
std::vector<std::string> GameProcess::getTags() const {
    return tags;
}
