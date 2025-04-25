#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <SDL_mixer.h>
#include <vector>
#include <unordered_map>
#include "gameSounds.h"

using namespace std;

class SoundPlayer {

    public:

        // constructor
        SoundPlayer();

        // initialize SDL_mixer
	    //void initialize();

        // destroy SDL objects
	    //void cleanup();

        // loop through vector of sound types and play each one
        void playSounds(vector<SoundType> sounds);

    private:

        // Map of sound type to loaded sound
        unordered_map<SoundType, Mix_Chunk*> loadedSounds;

        // load a sound effect (fills loadedSounds)
        Mix_Chunk* load(SoundType sound);

        // play a specific sound
        void play(SoundType sound);

};

#endif
