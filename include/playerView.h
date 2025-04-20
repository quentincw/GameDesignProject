#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "processManager.h"
#include "constants.h"
#include "floor.h"

class PlayerView
{
public:
    PlayerView();
	
	void initialize();
	
	void cleanup();

    void render(Floor* floor, ProcessManager* pm);

    void render(std::vector<GameObject*> walls, ProcessManager* pm);
	
	int handleInputs(ProcessManager* pm, int state);
	
	void renderPause();

private:

    void renderLevel(Floor* floor);

    void renderLevel(std::vector<GameObject*> walls);

    void testLevelRendering(Floor* floor);

    void renderProcesses(ProcessManager* pm);

    // updates the camera's position based on the player's position
    void updateCameraPosition(ProcessManager* pm);

    // The x and y of the camera
    int cameraX;
    int cameraY;
	
	SDL_Window* window;
	SDL_Renderer* renderer;
    SDL_Texture* tile_texture;
};

#endif
