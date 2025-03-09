#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include "gameProcess.h"


// constructor
GameProcess::GameProcess(std::vector<std::string> taglist) {
    tags = taglist;
    deleteFlag = false;
}

// marks process for deletion by changing delete flag (boolean)
void GameProcess::markForDeletion() {
    deleteFlag = true;
}

// returns whether the process is marked for deletion
bool GameProcess::getMarkForDeletion() const {
    return deleteFlag;
}


// returns the vector of tags of the process
std::vector<std::string> GameProcess::getTags() const {
    return tags;
}