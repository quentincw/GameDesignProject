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
#include "spitterProjectile.h"
#include "processManager.h"
#include "testWall.h"
#include "gameObject.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;


void csci437_error(const std::string& msg)
{
  std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
  exit(0);
}

bool checkCollision(GameObject* rect1, GameObject* rect2){
    Rectangle hitbox1 = rect1->getHitbox();
    Rectangle hitbox2 = rect2->getHitbox();

    if((hitbox1.x + hitbox1.width >= hitbox2.x) &&
       (hitbox1.x <= hitbox2.x + hitbox2.width) &&
       (hitbox1.y + hitbox1.height >= hitbox2.y) &&
       (hitbox1.y <= hitbox2.y + hitbox2.height)) {

        return true;
    }
    return false;

}

int moveInbounds(GameObject* rect1, GameObject* rect2){
    Rectangle hitbox1 = rect1->getHitbox();
    Rectangle hitbox2 = rect2->getHitbox();

    Point center1 = rect1->getCenter(&hitbox1);
    Point center2 = rect2->getCenter(&hitbox2);

    // left side collision
    if(center2.x <= hitbox1.x){
        rect2->setPosition(hitbox1.x - hitbox2.width, hitbox2.y);
        return 1;
    }
    // right side collision
    else if(center2.x >= hitbox1.x + hitbox1.width){
        rect2->setPosition(hitbox1.x + hitbox1.width, hitbox2.y);
        return 3;
    }
    // top side collision
    if(center2.y <= hitbox1.y){
        rect2->setPosition(hitbox2.x, hitbox1.y - hitbox2.height);
        return 2;
    }
    // bottom side collision
    else if(center2.y >= hitbox1.y + hitbox1.height){
        rect2->setPosition(hitbox2.x, hitbox1.y + hitbox1.height);
        return 4;
    }
    return 0;
}

void projectileCollision(PlayerProjectile* ball){

    /*
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
    */

    Rectangle hitbox = ball->getHitbox();
    int height = hitbox.height;
    int width = hitbox.height;
    int x = hitbox.x;
    int y = hitbox.y;

    // collision with left side of screen
    if (x <= 0) {
        ball->bounceX(0);
    }
    // collision with right side of screen
    else if (x + width >= SCREEN_WIDTH){
        ball->bounceX(SCREEN_WIDTH - width);
    }
    // collision with top of screen
    if (y <= 0) {
        ball->bounceY(0);
    }
    // collision with bottom of screen
    else if (y + height >= SCREEN_HEIGHT){
        ball->bounceY(SCREEN_HEIGHT - height);
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


    // create "player"
    PlayerProjectile ball1(0, 0, 3.0f, 3.0f);

    // create process manager
    ProcessManager manager(&ball1);
    // vector of current processes to check collisions/ oob
    vector<GameProcess*> curProcesses;
    // pointer to the current game process
    GameProcess* curProcess;
    // current circle
    //Circle curCircle;
    Rectangle curHitbox;

    //create test wall
    TestWall wall1(400, 400, 100, 100);

    // create roach
    Roach roach1(1000, 700);

    // create spitter
    Spitter spitter1(200,500);

    // add processes to process manager
    manager.addProcess(&roach1);
    manager.addProcess(&spitter1);
    //manager.addProcess(&ball1);

    // storage for "room" process lists
    vector<GameProcess*> room1;
    vector<GameProcess*> room2;
    bool curRoom = true;

    Spitter spitter2(30, 30);
    Spitter spitter3(700, 500);
    Spitter spitter4(1000, 30);

    room2.push_back(&spitter2);
    room2.push_back(&spitter3);
    room2.push_back(&spitter4);





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
                    case SDLK_s:
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

        manager.updateProcesses(1);

        projectileCollision(&ball1);

        curProcesses = manager.getProcessList();
        /*
        for(int i = 0; i < curProcesses.size(); i++){
            curProcess = curProcesses[i];
            curCircle = curProcess->getHitbox();
            if((curCircle.x - curCircle.radius <= 0) || (curCircle.y - curCircle.radius <= 0)){
                curProcess->markForDeletion();
            }
            else if((curCircle.x + curCircle.radius >= SCREEN_WIDTH) || (curCircle.y + curCircle.radius >= SCREEN_HEIGHT)){
                curProcess->markForDeletion();
            }
        }*/

        for(int i = 0; i < curProcesses.size(); i++){
            curProcess = curProcesses[i];
            curHitbox = curProcess->getHitbox();

            if((curHitbox.x <= 0) || (curHitbox.y <= 0)){
                if (auto projectile = dynamic_cast<SpitterProjectile*>(curProcess)){
                        curProcess->markForDeletion();
                    }
            }
            else if((curHitbox.x + curHitbox.width >= SCREEN_WIDTH) || (curHitbox.y + curHitbox.height >= SCREEN_HEIGHT)){
                if (auto projectile = dynamic_cast<SpitterProjectile*>(curProcess)){
                    curProcess->markForDeletion();
                }
            }
        }

        if(checkCollision(&wall1, &ball1)){
            //cout << "collision";
            int code = moveInbounds(&wall1, &ball1);
            if (code == 1 || code == 3){
                ball1.bounceX(ball1.getHitbox().x);
            }
            else {
                ball1.bounceY(ball1.getHitbox().y);
            }
        }

        for(int i = 0; i < curProcesses.size(); i++){
            curProcess = curProcesses[i];
            if(checkCollision(&wall1, curProcess)){
                moveInbounds(&wall1, curProcess);
            }
        }

        // draw screen
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        SDL_RenderClear( renderer );
        wall1.Render( renderer );
        manager.renderProcesses( renderer );
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
