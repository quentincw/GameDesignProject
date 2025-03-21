int main(int argc, char** argv) {}

// //Using SDL and standard IO
// #include <SDL.h>
// #include <SDL2_gfxPrimitives.h>
// #include <iostream>
// #include <stdio.h>
// #include "Player.h"

// //Screen dimension constants
// const int SCREEN_WIDTH = 1024;
// const int SCREEN_HEIGHT = 768;

// void csci437_error(const std::string& msg)
// {
//   std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
//   exit(0);
// }

// int main(int argc, char** argv)
// {
//   /*** Initialization ***/
  
//   // Initialize SDL
//   if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) csci437_error("SDL could not initialize!");

//   // Create window
//   SDL_Window* window = SDL_CreateWindow( "CSCI-437 Skeleton", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
//   if( window == NULL ) csci437_error("Window could not be created!");

//   // Small delay to allow the system to create the window.
//   SDL_Delay(100);
    
//   // Create renderer
//   SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
//   if (renderer == NULL) csci437_error("Unable to create renderer!");
  
//   /*** Main Loop ***/
//   bool running = true;
//   float playerX = 0;
//   float playerY = 0;
//   int mouseX = 0;
//   int mouseY = 0;
//   Player P(100,100);
//   SDL_Event e;

//   // While application is running
//   while( running )
//   {
//     // Handle events on queue
//     while( SDL_PollEvent( &e ) != 0 )
//     {
//       // User requests quit
//       if( e.type == SDL_QUIT ) running = false;

//       // User presses a key
//       if( e.type == SDL_KEYDOWN )
//       {
// 		if( e.key.keysym.sym == SDLK_q ) running = false;
// 		if( e.key.keysym.sym == SDLK_w) playerY = -0.5;
// 		if( e.key.keysym.sym == SDLK_a) playerX = -0.5;
// 		if( e.key.keysym.sym == SDLK_s) playerY = 0.5;
// 		if( e.key.keysym.sym == SDLK_d) playerX = 0.5;
//       }
// 	  if( e.type == SDL_KEYUP )
// 	  {
// 		if( e.key.keysym.sym == SDLK_w) playerY = 0;
// 		if( e.key.keysym.sym == SDLK_a) playerX = 0;
// 		if( e.key.keysym.sym == SDLK_s) playerY = 0;
// 		if( e.key.keysym.sym == SDLK_d) playerX = 0;
// 	  }
//     }
// 	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
//     SDL_RenderClear( renderer );
	
// 	P.setX(playerX);
// 	P.setY(playerY);
	
// 	Uint32 mouse = SDL_GetMouseState(&mouseX, &mouseY);
// 	P.setMouse(mouseX, mouseY);
	
// 	P.Update(1);
	
// 	P.Render(renderer);
	
// 	SDL_RenderPresent( renderer );
//   }

//   /*** Clean Up ***/

//   // Destroy renderer
//   SDL_DestroyRenderer( renderer );
  
//   // Destroy window
//   SDL_DestroyWindow( window );

//   // Quit SDL subsystems
//   SDL_Quit();
  
//   // Done.
//   return 0;
// }
