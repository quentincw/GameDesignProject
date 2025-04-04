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

void PlayerView::render(vector<GameObject*> walls, ProcessManager* pm)
{
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );
	
    updateCameraPosition(pm);

	renderLevel(walls);

    renderProcesses(pm);
	
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

// updates the camera's position based on the player's position
void PlayerView::updateCameraPosition(ProcessManager* pm)
{
    GameProcess* player = pm->getPlayer();
    cameraX = (player->getHitbox().x + player->getHitbox().width / 2) - SCREEN_WIDTH / 2;
    cameraY = (player->getHitbox().y + player->getHitbox().height / 2) - SCREEN_HEIGHT / 2;
}

