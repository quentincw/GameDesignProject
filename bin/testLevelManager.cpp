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
    /*Floor floor;
    floor.gen(3, 5, 14);
    vector<vector<int>> roomPos = floor.getRoomsPos();
    cout << '\n';
    for (int i = 0; i < roomPos.size(); i++) {
        for (int j = 0; j < roomPos[i].size(); j++) {
          cout << roomPos[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;*/


    /*** Initialization ***/
    /*
    // Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) csci437_error("SDL could not initialize!");

    // Create window
    SDL_Window* window = SDL_CreateWindow( "CSCI-437 Skeleton", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL ) csci437_error("Window could not be created!");

    // Small delay to allow the system to create the window.
    SDL_Delay(100);
    
    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL) csci437_error("Unable to create renderer!");
    */

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
    SDL_Event e;
    const int FPS = 60;
    const int TARGETMS = 1000/FPS;
    // While application is running
    while( running )
    {
        // get start timee
        int startMS = SDL_GetTicks();
        // Handle events on queue
		int ret = playerView.handleInputs(&processManager);
        if (ret == -1) {
            running = false;
        }
        if (ret == 5) {
            // test genereating a new floor
            levelManager.genNextFloor(processManager.getPlayer());
            // set the players position in the starting room
            //curFloor = levelManager.getCurrentFloor();
            //curRoom = curFloor->getCurRoom();
            //processManager.getPlayer()->setPosition((curRoom.x + (curRoom.w / 2)) * TILE_SIZE, (curRoom.y + (curRoom.h / 2)) * TILE_SIZE);
        }

        // update the player and current process list
        processManager.updateProcesses(1);

        // update game logic
        gameLogic.update();

        // check if the player moved to a new room
        levelManager.setCurrentRoom(&processManager);

        playerView.render(levelManager.getCurrentFloor(), &processManager);

        // delta time calculation
        int deltaMS = SDL_GetTicks() - startMS;
        if(deltaMS < TARGETMS){
            SDL_Delay(TARGETMS - deltaMS);
        }
    }
    return 0;
}