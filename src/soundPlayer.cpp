#include "soundPlayer.h"
#include <iostream>

using namespace std;

SoundPlayer::SoundPlayer() {

    // load all sounds
    for (SoundType sound : allSoundTypes) {
        load(sound);
    }
}

// load and returns a sound effect (fills loadedSounds)
Mix_Chunk* SoundPlayer::load(SoundType sound) {

    // check if the sound is already loaded
    auto iter = loadedSounds.find(sound);
    if (iter != loadedSounds.end()) {
        // sound found
        return iter->second;
    }

    // get the file path
    const char* path = toFilePath(sound); 

    // load the sound
    Mix_Chunk* chunk = Mix_LoadWAV(path);
    if (!chunk) {
        cout << "failed to load sound: chunk " << path << endl;
        return nullptr;
    }

    // save the loaded sound
    loadedSounds[sound] = chunk;
    return chunk;
}

// play a specific sound
void SoundPlayer::play(SoundType sound) {

    // get the sound (loads the sound if necessary)
    Mix_Chunk* chunk = load(sound); 
    if (chunk) {
        // play the sound
        Mix_PlayChannel(-1, chunk, 0);
    }
}

// loop through vector of sound types and play each one
void SoundPlayer::playSounds(vector<SoundType> sounds) {

    for(int i = 0; i < sounds.size(); i++){
        play(sounds[i]);
    }
}