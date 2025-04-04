#include "playerView.h"
#include "gameProcess.h"
#include "gameObject.h"

PlayerView::PlayerView(ProcessManager* pm, LevelManager* lm)
    : processManager(pm), levelManager(lm)
{
}

void PlayerView::render()
{
    renderLevel();

    renderProcesses();
}

void PlayerView::renderLevel()
{
    const auto& walls = levelManager->getWalls();
    for (const auto& tile : walls)
    {
        tile.render();  
    }
}

void PlayerView::renderProcesses()
{
    const auto& processes = processManager->getProcesses();
    for (Process* process : processes)
    {
        if (!process) 
            continue;

        process->render();
    }
}

void Player::update(float deltaMS)
{
    while( SDL_PollEvent( &e ) != 0 )
     {
       // User requests quit
       if( e.type == SDL_QUIT ); //quit;

       // User presses a key
       if( e.type == SDL_KEYDOWN )
       {
		if( e.key.keysym.sym == SDLK_q );//quit;
 		if( e.key.keysym.sym == SDLK_w) player.setVelY(-0.5);
 		if( e.key.keysym.sym == SDLK_a) player.setVelX(0.5);
 		if( e.key.keysym.sym == SDLK_s) player.setVelY(0.5);
 		if( e.key.keysym.sym == SDLK_d) player.setVelX(-0.5);
       }
	   if( e.type == SDL_KEYUP )
 	   {
 		if( e.key.keysym.sym == SDLK_w) player.setVelY(0);
 		if( e.key.keysym.sym == SDLK_a) player.setVelX(0);
 		if( e.key.keysym.sym == SDLK_s) player.setVelY(0);
 		if( e.key.keysym.sym == SDLK_d) player.setVelX(0);
 	   }
     }
	
	//player move
	
}