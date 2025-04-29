#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "processManager.h"
#include "constants.h"
#include "floor.h"
#include "soundPlayer.h"

class PlayerView
{
public:
    PlayerView();
	
	void initialize();
	
	void cleanup();

    void render(Floor* floor, ProcessManager* pm, int state, bool paused);
	
	int handleInputs(ProcessManager* pm, int state);

    // plays sounds from processes in the process manager
    void playSounds(ProcessManager* pm);

	void renderPause();

private:
	void renderTitle();
	
	void renderStory();
	
	void renderWin();
	
	void renderLose();

    // renders the floor
    void renderLevel(Floor* floor);

    // renders all the processes (bloodstains first)
    void renderProcesses(ProcessManager* pm);
    
    // renders the minimap
	void renderMinimap(Floor* floor);

    // updates the camera's position based on the player's position
    void updateCameraPosition(ProcessManager* pm);

    // renders HUD for healthbar
    void renderHealthBar(Player1* player);

    // The x and y of the camera
    int cameraX;
    int cameraY;
	
	SDL_Window* window;
	SDL_Renderer* renderer;
    SDL_Texture* tile_texture;
	
	SDL_Texture* pauseS;
	SDL_Texture* titleS;
	SDL_Texture* storyS;
	SDL_Texture* winS;
	SDL_Texture* loseS;

    SDL_Texture* tile_texture_1;
    SDL_Texture* tile_texture_2;
    SDL_Texture* tile_texture_3;

    SDL_Rect tileTextures[14];

    const int total_frames = 24;
    vector<SDL_Texture*> frames;
    vector<SDL_Texture*> frames_1;
    vector<SDL_Texture*> frames_2;
    vector<SDL_Texture*> frames_3;

    // booleans for player movement
    bool right;
    bool left;
    bool up;
    bool down;

    // the sound player
    SoundPlayer soundPlayer;
};

#endif
