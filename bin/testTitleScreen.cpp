//Using SDL and standard IO
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_mixer.h>
#include <iostream>
#include <stdio.h>
#include "constants.h"
#include "floor.h"
#include "levelManager.h"
#include "playerView.h"
#include "gameLogic.h"
#include "oldLogic.h"


using namespace std;

void csci437_error(const std::string& msg)
{
  std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
  exit(0);
}

void floorGen(LevelManager *lm, ProcessManager *pm) {
	// generate the floor
    lm->genFloor(1);
	
	// set the players position in the starting room
    Floor* curFloor = lm->getCurrentFloor();
    SDL_Rect curRoom = curFloor->getCurRoom();
    pm->getPlayer()->setPosition((curRoom.x + (curRoom.w / 2)) * TILE_SIZE, (curRoom.y + (curRoom.h / 2)) * TILE_SIZE);
}

int main(int argc, char** argv) {
	// keep track of game state
	// 0 = title screen, 1 = lore, 2 = playing, 3 = win, -1 = game over
	int state = 0;
	
    // create a level manager
    LevelManager levelManager;

    // create process manager w/ player at 0,0
    ProcessManager processManager;
	
	// generates the first floor
	floorGen(&levelManager, &processManager);

    // create player view
    PlayerView playerView;
    playerView.initialize();

    // make game logic
    //GameLogic gameLogic(&processManager, &levelManager);
    OldGameLogic gameLogic(&processManager, &levelManager);


    /*** Main Loop ***/
    bool running = true;
	bool paused = false;
    SDL_Event e;
    const int FPS = 60;
    const int TARGETMS = 1000/FPS;
	int startMS, deltaMS;
    // While application is running
    while( running )
    {
        // get start timee
        startMS = SDL_GetTicks();
        // Handle events on queue
		int ret = playerView.handleInputs(&processManager, state);
        if (ret == -1) {
            running = false;
        }
		if (ret == -2) {
			paused = !paused;
		}
		if (ret >=1 ) state+=ret;
		
		if (!paused){
			// update the player and current process list
			processManager.updateProcesses(deltaMS);

			// update game logic
			gameLogic.update();

			// check if the player moved to a new room
			levelManager.setCurrentRoom(&processManager);
		}

		playerView.render(state, levelManager.getCurrentFloor(), &processManager);
		
		if (paused){
			playerView.renderPause();
		}

		// delta time calculation
		deltaMS = SDL_GetTicks() - startMS;
		if(deltaMS < TARGETMS){
			SDL_Delay(TARGETMS - deltaMS);
		}
    }
    return 0;
}