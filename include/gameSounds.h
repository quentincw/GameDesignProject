#ifndef GAMESOUNDS_H
#define GAMESOUNDS_H

#include <array>
#include <functional>

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
    SPIT_HIGH,
	SPIT_LOW,
	SPIT_MEDIUM,
    BUG_DEATH1,
	BUG_DEATH2,
    PLAYER_DAMAGE1,
    PLAYER_DAMAGE2,
    PLAYER_DAMAGE3,
    PLAYER_DAMAGE4,
    PLAYER_DAMAGE5,
    PLAYER_DAMAGE6,
    PLAYER_KILLS1,
    PLAYER_KILLS2,
    PLAYER_KILLS3,
    PLAYER_KILLS4,
    PLAYER_KILLS5,
    PLAYER_KILLS6,
    PLAYER_KILLS7,
    PLAYER_KILLS8,
    DOOR_OPEN,
    DOOR_CLOSE,
    PLAYER_SAD1,
    PLAYER_SAD2,
    PLAYER_SAD3,
    PLAYER_SAD4,
    PLAYER_SAD5,
    PLAYER_SAD6,
    PLAYER_SHOOT,
    EXPLOSION,
    PICKUP,
    ROLL,
    ALIENQUEEN1,
    ALIENQUEEN2,
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
    SoundType::SPIT_HIGH,
    SoundType::SPIT_LOW,
    SoundType::SPIT_MEDIUM,
    SoundType::BUG_DEATH1,
	SoundType::BUG_DEATH2,
    SoundType::PLAYER_DAMAGE1,
	SoundType::PLAYER_DAMAGE2,
	SoundType::PLAYER_DAMAGE3,
	SoundType::PLAYER_DAMAGE4,
	SoundType::PLAYER_DAMAGE5,
	SoundType::PLAYER_DAMAGE6,
    SoundType::PLAYER_KILLS1,
	SoundType::PLAYER_KILLS2,
	SoundType::PLAYER_KILLS3,
	SoundType::PLAYER_KILLS4,
	SoundType::PLAYER_KILLS5,
	SoundType::PLAYER_KILLS6,
	SoundType::PLAYER_KILLS7,
	SoundType::PLAYER_KILLS8,
    SoundType::DOOR_OPEN,
    SoundType::DOOR_CLOSE,
    SoundType::PLAYER_SAD1,
	SoundType::PLAYER_SAD2,
	SoundType::PLAYER_SAD3,
	SoundType::PLAYER_SAD4,
	SoundType::PLAYER_SAD5,
	SoundType::PLAYER_SAD6,
    SoundType::PLAYER_SHOOT,
    SoundType::EXPLOSION,
    SoundType::PICKUP,
    SoundType::ALIENQUEEN1,
    SoundType::ALIENQUEEN2,
    SoundType::ROLL
}};

// basic mapping of sound type to a file path
const char* toFilePath(SoundType sound);

namespace std
{
    template <>
    struct hash<SoundType>
    {
        size_t operator()(const SoundType& sound) const
        {
            return hash<int>()(static_cast<int>(sound));
        }
    };
}

#endif
