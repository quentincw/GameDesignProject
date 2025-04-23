#include "gameSounds.h"

// basic mapping of sound type to a file path
const char* toFilePath(SoundType sound) {
    switch (sound) {
        case SoundType::ROACH_NOISE:
            return "../resource/sounds/jews_harp_boing-7111.mp3";
        default:
            return "";
    }
}