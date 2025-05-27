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
#include "Player1.h"
#include "processManager.h"


using namespace std;

void csci437_error(const std::string& msg)
{
  std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
  exit(0);
}

int main(int argc, char** argv) {
	// keep track of game state
	// 0 = title screen, 1 = lore, 2 = controls, 3 = playing, 4 = win, -1 = game over
	int state = 0;
	
    // create a level manager
    LevelManager levelManager;

    // create process manager w/ player at 0,0
    ProcessManager processManager;

    // create player view
    PlayerView playerView;
    playerView.initialize();

    // generate the floor
    levelManager.genNextFloor(processManager.getPlayer());

    // set the players position in the starting room
    //Floor* curFloor = levelManager.getCurrentFloor();
    //SDL_Rect curRoom = curFloor->getCurRoom();
    //processManager.getPlayer()->setPosition((curRoom.x + (curRoom.w / 2)) * TILE_SIZE, (curRoom.y + (curRoom.h / 2)) * TILE_SIZE);
    //processManager.addProcess(processManager.getPlayer());

    // make game logic
    GameLogic gameLogic(&processManager, &levelManager);

    /*** Main Loop ***/
    bool running = true;
	bool paused = false;
    SDL_Event e;
    const int FPS = 60;
    const int TARGETMS = 1000/FPS;
	int startMS, deltaMS;
	auto player = dynamic_cast<Player1*>(processManager.getPlayer());
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
        if (ret == 5) {
            // test genereating a new floor
            levelManager.genNextFloor(processManager.getPlayer());
            // set the players position in the starting room
            //curFloor = levelManager.getCurrentFloor();
            //curRoom = curFloor->getCurRoom();
            //processManager.getPlayer()->setPosition((curRoom.x + (curRoom.w / 2)) * TILE_SIZE, (curRoom.y + (curRoom.h / 2)) * TILE_SIZE);
        }
		if (ret == 1){
			state+=ret;
			state%=4;
		}
		
		
		if (!paused && state==3){
			// update the player and current process list
			processManager.updateProcesses(deltaMS);

			// update game logic
			gameLogic.update();

			// check if the player moved to a new room
			levelManager.setCurrentRoom(&processManager);
			
			if (player->getHealth()<=0) state = -1;
			
			if (gameLogic.checkWin()) state = 4;
		}

        // render the level and processes		
		playerView.render(levelManager.getCurrentFloor(), &processManager, state, paused);

        // play sounds
        playerView.playSounds(&processManager);

        // delta time calculation
        deltaMS = SDL_GetTicks() - startMS;
        if(deltaMS < TARGETMS){
            SDL_Delay(TARGETMS - deltaMS);
        }
    }
    return 0;
}
