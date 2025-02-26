//Using SDL and standard IO
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_mixer.h>
#include <iostream>
#include <stdio.h>
#include "room.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

int main(int argc, char** argv)
{
  /*** Initialization ***/
  
  // Create window
  SDL_Window* window = SDL_CreateWindow( "Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
  
  // Small delay to allow the system to create the window.
  SDL_Delay(100);
    
  // Create renderer
  SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

  // render tiles
  SDL_Surface* tile_surface = SDL_LoadBMP("../resource/tile.bmp");
  
  // convert to texture
  SDL_Texture* tile_texture = SDL_CreateTextureFromSurface( renderer, tile_surface );
  
  // delete image
  SDL_FreeSurface( tile_surface );
  tile_surface = NULL;

  srand(time(NULL));
  // default 16
  int tile_size = 96;
  // max w: 1024/tile_size, max h: 768/tile_size
  int width = 8;
  // screen res is 4x3
  int height = 6;
  // [up, right, down, left], determines which sides will accomidate for doors
  vector<bool> door = {1, 0, 1, 0};
  // 0 - 100 (default room - empty room)
  int walk_pct = 0;
  Room room;
  vector<vector<int>> tilemap = room.gen(width, height, door, walk_pct);

  SDL_Rect tile[width][height];
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
        tile[x][y].x = ((SCREEN_WIDTH - (width * tile_size)) / 2) + (x * tile_size);
        tile[x][y].y = ((SCREEN_HEIGHT - (height * tile_size)) / 2) + ( y * tile_size);
        tile[x][y].w = tile_size;
        tile[x][y].h = tile_size;
    }
  }

  SDL_Rect tile_0;
  tile_0.x = 0;
  tile_0.y = 0;
  tile_0.w = 16;
  tile_0.h = 16;

  SDL_Rect tile_1;
  tile_1.x = 16;
  tile_1.y = 0;
  tile_1.w = 16;
  tile_1.h = 16;

  SDL_Rect tile_2;
  tile_2.x = 32;
  tile_2.y = 0;
  tile_2.w = 16;
  tile_2.h = 16;

  SDL_Rect tile_3;
  tile_3.x = 48;
  tile_3.y = 0;
  tile_3.w = 16;
  tile_3.h = 16;

  SDL_Rect tile_4;
  tile_4.x = 64;
  tile_4.y = 0;
  tile_4.w = 16;
  tile_4.h = 16;

  SDL_Rect tile_5;
  tile_5.x = 0;
  tile_5.y = 16;
  tile_5.w = 16;
  tile_5.h = 16;

  SDL_Rect tile_6;
  tile_6.x = 16;
  tile_6.y = 16;
  tile_6.w = 16;
  tile_6.h = 16;

  SDL_Rect tile_7;
  tile_7.x = 32;
  tile_7.y = 16;
  tile_7.w = 16;
  tile_7.h = 16;

  SDL_Rect tile_8;
  tile_8.x = 48;
  tile_8.y = 16;
  tile_8.w = 16;
  tile_8.h = 16;

  SDL_Rect tile_9;
  tile_9.x = 64;
  tile_9.y = 16;
  tile_9.w = 16;
  tile_9.h = 16;

  SDL_Rect tile_10;
  tile_10.x = 0;
  tile_10.y = 32;
  tile_10.w = 16;
  tile_10.h = 16;

  SDL_Rect tile_11;
  tile_11.x = 16;
  tile_11.y = 32;
  tile_11.w = 16;
  tile_11.h = 16;

  SDL_Rect tile_12;
  tile_12.x = 32;
  tile_12.y = 32;
  tile_12.w = 16;
  tile_12.h = 16;

  SDL_Rect tile_13;
  tile_13.x = 48;
  tile_13.y = 32;
  tile_13.w = 16;
  tile_13.h = 16;
  
  /*** Main Loop ***/
  bool running = true;
  SDL_Event e;

  // While application is running
  while( running ) 
  {
    // Handle events on queue
    while( SDL_PollEvent( &e ) != 0 ) {
      // User requests quit
      if( e.type == SDL_QUIT ) running = false;

      // User presses a key
      if( e.type == SDL_KEYDOWN) {
        if ( e.key.keysym.sym == SDLK_q ) running = false;
        if ( e.key.keysym.sym == SDLK_SPACE) tilemap = room.gen(width, height, door, walk_pct);
      }
    }
    // render
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            switch (tilemap[x][y])
            {
            case 0:
                SDL_RenderCopy(renderer, tile_texture, &tile_0, &tile[x][y]);
                break;
            case 1:
                SDL_RenderCopy(renderer, tile_texture, &tile_1, &tile[x][y]);
                break;
            case 2:
                SDL_RenderCopy(renderer, tile_texture, &tile_2, &tile[x][y]);
                break;
            case 3:
                SDL_RenderCopy(renderer, tile_texture, &tile_3, &tile[x][y]);
                break;
            case 4:
                SDL_RenderCopy(renderer, tile_texture, &tile_4, &tile[x][y]);
                break;
            case 5:
                SDL_RenderCopy(renderer, tile_texture, &tile_5, &tile[x][y]);
                break;
            case 6:
                SDL_RenderCopy(renderer, tile_texture, &tile_6, &tile[x][y]);
                break;
            case 7:
                SDL_RenderCopy(renderer, tile_texture, &tile_7, &tile[x][y]);
                break;
            case 8:
                SDL_RenderCopy(renderer, tile_texture, &tile_8, &tile[x][y]);
                break;
            case 9:
                SDL_RenderCopy(renderer, tile_texture, &tile_9, &tile[x][y]);
                break;
            case 10:
                SDL_RenderCopy(renderer, tile_texture, &tile_10, &tile[x][y]);
                break;
            case 11:
                SDL_RenderCopy(renderer, tile_texture, &tile_11, &tile[x][y]);
                break;
            case 12:
                SDL_RenderCopy(renderer, tile_texture, &tile_12, &tile[x][y]);
                break;
            case 13:
                SDL_RenderCopy(renderer, tile_texture, &tile_13, &tile[x][y]);
                break;
            }
        }
    }

    SDL_RenderPresent( renderer );
  }

  /*** Clean Up ***/

  // Destroy texture
  SDL_DestroyTexture( tile_texture );
  
  // Destroy renderer
  SDL_DestroyRenderer( renderer );
  
  // Destroy window
  SDL_DestroyWindow( window );

  // Quit SDL subsystems
  SDL_Quit();
  
  // Done.
  return 0;
}
