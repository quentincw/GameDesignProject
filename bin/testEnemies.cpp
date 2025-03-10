//Using SDL and standard IO
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <vector>
#include "gameProcess.h"
#include "roach.h"
#include "spitter.h"
#include "playerProjectile.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;


void csci437_error(const std::string& msg)
{
  std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
  exit(0);
}

void projectileCollision(PlayerProjectile* ball){

    
    Circle hitbox = ball->getHitbox();
    int radius = hitbox.radius;
    int x = hitbox.x;
    int y = hitbox.y;
    // check for collision with top of screen
    if (y - radius <= 0){
        ball->bounceY(0 + radius);
    }
    // check for collision with bottom of the screen
    else if(y + radius >= SCREEN_HEIGHT){
        ball->bounceY(SCREEN_HEIGHT - radius);
    }
    // check for collision with left of screen
    if (x - radius <= 0){
        ball->bounceX(0 + radius);
    }
    // check for collision with right of the screen
    else if(x + radius >= SCREEN_WIDTH){
        ball->bounceX(SCREEN_WIDTH - radius);
    }
}

int main(int argc, char** argv)
{

    /*** Initialization ***/
  
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

    vector<GameProcess*> objectList;
  
    Roach roach1(1000, 700);

    PlayerProjectile ball1(0, 0, 3.0f, 3.0f);

    Spitter spitter1(200,500);

    objectList.push_back(&roach1);
    objectList.push_back(&ball1);
    objectList.push_back(&spitter1);




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
        while( SDL_PollEvent( &e ) != 0)
        {
              // User requests quit
            if( e.type == SDL_QUIT ) running = false;

            // User presses a key
            if( e.type == SDL_KEYDOWN ){

                switch(e.key.keysym.sym){
                    case SDLK_q:
                        running = false;
                        break;
                    /*case SDLK_UP:
                        roach1.UpdateAI(roach1.getXpos(), 100);
                        break;
                    case SDLK_DOWN:
                        roach1.UpdateAI(roach1.getXpos(), SCREEN_HEIGHT - 100);
                        break;
                    case SDLK_RIGHT:
                        roach1.UpdateAI(SCREEN_WIDTH - 100, roach1.getYpos());
                        break;
                    case SDLK_LEFT:
                        roach1.UpdateAI(100, roach1.getYpos());
                        break;*/
                }
            }
            else {
            // no keys pressed,
            }
        }

        for(int i = 0; i < objectList.size(); i++){
            objectList[i]->Update(1);
        }
        //roach1.UpdateAI(ball1.getXpos(), ball1.getYpos());
        roach1.UpdateAI(ball1.getHitbox());
        spitter1.UpdateAI(ball1.getHitbox());
    
        if(spitter1.hasChildren()){
            objectList.push_back(spitter1.getChildren());
        }
        

        projectileCollision(&ball1);

        // draw screen
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        SDL_RenderClear( renderer );
        for(int i = 0; i < objectList.size(); i++){
            objectList[i]->Render( renderer );
        }
        SDL_RenderPresent( renderer );

        // delta time calculation
        int deltaMS = SDL_GetTicks() - startMS;
        if(deltaMS < TARGETMS){
            SDL_Delay(TARGETMS - deltaMS);
        }
    }
  
    // Done.
    return 0;
}
