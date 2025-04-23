#ifndef GAMESOUNDS_H
#define GAMESOUNDS_H

#include <array>

/*
    To add a sound:
    1.) add the type to SoundType
    2.) add the SoundType to the array initialization
    3.) add the file path to the function
*/

// enum class for sound type
enum class SoundType {
    ROACH_NOISE,
    SPITTER_NOISE,
    SPEWER_NOISE,
    SPAWNER_NOISE,
    EXPLODER_NOISE,
    ALPHASPITTER_NOISE,
    CHARGER_NOISE,
    ALPHACHARGER_NOISE,
    ALPHASPEWER_NOISE,
    BURROWER_NOISE,
    BURROWER_DIG,
    SPIT_NOISE,
    BUG_DEATH,
    PLAYER_DAMAGE,
    PLAYER_KILLS,
    DOOR_OPEN,
    DOOR_CLOSE,
    PLAYER_SAD,
    PLAYER_SHOOT,
    EXPLOSION,
    PICKUP,
    ROLL,
    // count needs to be the last element
    Count

};

// array containing every sound type (constant)
constexpr std::array<SoundType, static_cast<std::size_t>(SoundType::Count)> allSoundTypes {{
    SoundType::ROACH_NOISE,
    SoundType::SPITTER_NOISE,
    SoundType::SPEWER_NOISE,
    SoundType::SPAWNER_NOISE,
    SoundType::EXPLODER_NOISE,
    SoundType::ALPHASPITTER_NOISE,
    SoundType::CHARGER_NOISE,
    SoundType::ALPHACHARGER_NOISE,
    SoundType::ALPHASPEWER_NOISE,
    SoundType::BURROWER_NOISE,
    SoundType::BURROWER_DIG,
    SoundType::SPIT_NOISE,
    SoundType::BUG_DEATH,
    SoundType::PLAYER_DAMAGE,
    SoundType::PLAYER_KILLS,
    SoundType::DOOR_OPEN,
    SoundType::DOOR_CLOSE,
    SoundType::PLAYER_SAD,
    SoundType::PLAYER_SHOOT,
    SoundType::EXPLOSION,
    SoundType::PICKUP,
    SoundType::ROLL
}};

// basic mapping of sound type to a file path
const char* toFilePath(SoundType sound);

#endif
