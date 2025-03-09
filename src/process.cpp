#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include "process.h"

using namespace std;

// constructor
Process(vector<string> taglist) : tags(move(taglist)) {

}

// marks process for deletion by changing delete flag (boolean)
void markForDeletion() {
    deleteFlag = true;
}

// returns whether the process is marked for deletion
bool getMarkForDeletion() const {
    return deleteFlag;
}


// returns the vector of tags of the process
vector<string> getTags() const {
    return tags;
}