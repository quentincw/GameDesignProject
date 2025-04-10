#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "playerView.h"
#include "gameProcess.h"
#include "gameObject.h"

PlayerView::PlayerView() {}

void PlayerView::initialize()
{
	// Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) std::cerr << " (" << SDL_GetError() << ")" << std::endl;

    // Create window
    window = SDL_CreateWindow( "playerView", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL ) std::cerr << " (" << SDL_GetError() << ")" << std::endl;

    // Small delay to allow the system to create the window.
    SDL_Delay(100);
    
    // Create renderer
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL) std::cerr << " (" << SDL_GetError() << ")" << std::endl;
}

void PlayerView::cleanup()
{
	// Destroy renderer
	SDL_DestroyRenderer( renderer );
  
    // Destroy window
    SDL_DestroyWindow( window );

    // Quit SDL subsystems
    SDL_Quit();
}

int PlayerView::handleInputs(ProcessManager* pm)
{
	SDL_Event e;
	auto player = dynamic_cast<Player1*>(pm->getPlayer());
	auto curProcesses = pm->getProcessList();
	while( SDL_PollEvent( &e ) != 0)
        {
            // User requests quit
            if( e.type == SDL_QUIT ) return -1;

            // User presses a key
            if( e.type == SDL_KEYDOWN ){

                switch(e.key.keysym.sym){
                    case SDLK_q:
                        return -1;
                    /*case SDLK_s:
                        // check which list is active (true = room1)
                        if(curRoom){
                            room1 = manager.getProcessList();
                            manager.loadProcessList(room2);
                            curRoom = false;
                        }
                        else{
                            room2 = manager.getProcessList();
                            manager.loadProcessList(room1);
                            curRoom = true;
                        }
                        break;*/
                    case SDLK_k:
                        //kill all the current processes
                        for(int i = 0; i < curProcesses.size(); i++){
                            auto curProcess = curProcesses[i];
                            curProcess->markForDeletion();
                        }
                        break;
                    case SDLK_w:
                        player->setSpeedY(-3);
                        break;
                    case SDLK_s:
                        player->setSpeedY(3);
                        break;
                    case SDLK_d:
                        player->setSpeedX(3);
                        break;
                    case SDLK_a:
                        player->setSpeedX(-3);
                }
            }
			// User releases a key
			else if( e.type == SDL_KEYUP ){

                switch(e.key.keysym.sym){
					case SDLK_w:
						player->setSpeedY(0);
						break;
					case SDLK_s:
						player->setSpeedY(0);
						break;
					case SDLK_d:
						player->setSpeedX(0);
						break;
					case SDLK_a:
						player->setSpeedX(0);
						break;
				}
			}
			else if( e.type == SDL_MOUSEBUTTONDOWN ){
				switch(e.button.button){
					case SDL_BUTTON_LEFT:
						int mouseX = 0;
						int mouseY = 0;
					 	Uint32 mouse = SDL_GetMouseState(&mouseX, &mouseY);
						player->updateMouse(mouseX, mouseY);

						player->shootProj(cameraX, cameraY);
						break;
				}
			}
            else {
            // no keys pressed,
            }
        }
	return 0;
}

void PlayerView::render(vector<GameObject*> walls, ProcessManager* pm)
{
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );
	
    updateCameraPosition(pm);

	renderLevel(walls);

    renderProcesses(pm);
	
	//renderMinimap(walls);
	
	SDL_RenderPresent( renderer );
}

void PlayerView::renderLevel(vector<GameObject*> walls)
{
	GameObject* curWall;
	for(int i = 0; i < walls.size(); i++){
        curWall = walls[i];
        curWall->RenderCam(renderer, cameraX, cameraY );
    }
    /*const auto& walls = levelManager->getWalls();
    for (const auto& tile : walls)
    {
        tile.RenderCam( renderer, cameraX, cameraY);  
    }*/
}

void PlayerView::renderProcesses(ProcessManager* pm)
{
	pm->renderProcessesCam( renderer, cameraX, cameraY );
    /*const auto& processes = pm->getProcessList();
    for (GameProcess* process : processes)
    {
        if (!process) 
            continue;

        process->Render(renderer);
    }
	pm->getPlayer()->Render(renderer);*/
}

/*
void PlayerView::renderMinimap(walls)
{
	
}
*/

// updates the camera's position based on the player's position
void PlayerView::updateCameraPosition(ProcessManager* pm)
{
    GameProcess* player = pm->getPlayer();
    cameraX = (player->getHitbox().x + player->getHitbox().width / 2) - SCREEN_WIDTH / 2;
    cameraY = (player->getHitbox().y + player->getHitbox().height / 2) - SCREEN_HEIGHT / 2;
}

