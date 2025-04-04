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

private:

    void renderLevel(vector<GameObject*> walls);

    void renderProcesses(ProcessManager* pm);

       // updates the camera's position based on the player's position
    void updateCameraPosition(ProcessManager* pm);

    // The x and y of the camera
    int cameraX;
    int cameraY;
	
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif
