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

    void render(Floor* floor, ProcessManager* pm, int state);

    void render(std::vector<GameObject*> walls, ProcessManager* pm);
	
	int handleInputs(ProcessManager* pm, int state);

    // plays sounds from processes in the process manager
    void playSounds(ProcessManager* pm);

	void renderPause();

private:
	void renderTitle();
	
	void renderStory();
	
	void renderWin();
	
	void renderLose();

    void renderLevel(Floor* floor);

    void renderLevel(std::vector<GameObject*> walls);

    void renderProcesses(ProcessManager* pm);
	
	//void renderMinimap(LevelManager* lm);

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

    const int total_frames = 24;
    vector<SDL_Texture*> frames;

    // the sound player
    SoundPlayer soundPlayer;
};

#endif
