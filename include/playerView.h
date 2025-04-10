#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "processManager.h"
#include "constants.h"

class PlayerView
{
public:
    PlayerView();
	
	void initialize();
	
	void cleanup();

    void render(vector<GameObject*> walls, ProcessManager* pm);
	//void render(LevelManager* lm, ProcessManager* pm);
	
	int handleInputs(ProcessManager* pm);

private:

    void renderLevel(vector<GameObject*> walls);
	//void renderLevel(LevelManager* lm);

    void renderProcesses(ProcessManager* pm);
	
	//void renderMinimap(LevelManager* lm);

    // updates the camera's position based on the player's position
    void updateCameraPosition(ProcessManager* pm);

    // The x and y of the camera
    int cameraX;
    int cameraY;
	
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif
