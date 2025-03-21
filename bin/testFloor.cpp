//Using SDL and standard IO
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_mixer.h>
#include <iostream>
#include <stdio.h>
#include "constants.h"
#include "room.h"
#include "floor.h"
#include "player.h"

int main(int argc, char** argv)
{
  /*** Initialization ***/
  // Create window
  SDL_Window* window = SDL_CreateWindow( "Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
  
  // Small delay to allow the system to create the window.
  SDL_Delay(100);
    
  // Create renderer
  SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED );

  // render tiles
  SDL_Surface* tile_surface = SDL_LoadBMP("../resource/tile.bmp");
  
  // convert to texture
  SDL_Texture* tile_texture = SDL_CreateTextureFromSurface( renderer, tile_surface );
  
  // delete image
  SDL_FreeSurface( tile_surface );
  tile_surface = NULL;

  SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
  Uint64 startTicks = SDL_GetTicks();
  Player player;
  Floor floor;
  // width * height >= gen_rooms + 2 (start and boss room)
  floor.gen(6, 6, 16);
  SDL_Rect curRoom = floor.getCurRoom();

  player.setPos((curRoom.x + (curRoom.w / 2)) * TILE_SIZE, (curRoom.y + (curRoom.h / 2)) * TILE_SIZE);

  vector<vector<int>> rooms = floor.getRooms();
  int rooms_width = rooms.size();
  int rooms_height = rooms[0].size();
  vector<vector<vector<SDL_Rect>>> rooms_col = floor.getRoomsCol();

  SDL_Rect tile[rooms_width][rooms_height];
  SDL_Rect map[rooms_width][rooms_height];
  vector<SDL_Rect> render_map;
  static const int MAP_SIZE = 2;
  for (int x = 0; x < rooms_width; x++) {
    for (int y = 0; y < rooms_height; y++) {
        if (rooms[x][y] >= 0) {
            map[x][y].x = x * MAP_SIZE;
            map[x][y].y = y * MAP_SIZE;
            map[x][y].w = MAP_SIZE;
            map[x][y].h = MAP_SIZE;

            render_map.push_back(map[x][y]);
        }
        tile[x][y].x = x * TILE_SIZE;
        tile[x][y].y = y * TILE_SIZE;
        tile[x][y].w = TILE_SIZE;
        tile[x][y].h = TILE_SIZE;
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

  SDL_Rect tileTextures[14] = {tile_0, tile_1, tile_2, tile_3, tile_4, tile_5, tile_6, tile_7, tile_8, tile_9, tile_10, tile_11, tile_12, tile_13};
  
  /*** Main Loop ***/
  bool running = true;
  SDL_Event e;

  // While application is running
  while( running ) 
  {
    Uint64 curTicks = SDL_GetTicks();
    float deltaTime = curTicks - startTicks;
    // Handle events on queue
    while( SDL_PollEvent( &e ) != 0 ) {
      // User requests quit
      if( e.type == SDL_QUIT ) running = false;

      // User presses a key
      if( e.type == SDL_KEYDOWN ) {
        if ( e.key.keysym.sym == SDLK_q ) running = false;
        if ( e.key.keysym.sym == SDLK_d ) player.setVelX(1);
        if ( e.key.keysym.sym == SDLK_a ) player.setVelX(-1);
        if ( e.key.keysym.sym == SDLK_w ) player.setVelY(-1);
        if ( e.key.keysym.sym == SDLK_s ) player.setVelY(1);
      }
      if ( e.type == SDL_KEYUP ) {
        if ( e.key.keysym.sym == SDLK_d ) player.setVelX(0);
        if ( e.key.keysym.sym == SDLK_a ) player.setVelX(0);
        if ( e.key.keysym.sym == SDLK_w ) player.setVelY(0);
        if ( e.key.keysym.sym == SDLK_s ) player.setVelY(0);
      }
    }
    if (deltaTime > 1000 / 60.0) {
        // render
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        SDL_RenderClear( renderer );

        camera.x = player.getPos()[0] + player.rad - (SCREEN_WIDTH / 2);
        camera.y = player.getPos()[1] + player.rad - (SCREEN_HEIGHT / 2);

        floor.setCurRoom(player.getPos()[0] / TILE_SIZE, player.getPos()[1] / TILE_SIZE);
        curRoom = floor.getCurRoom();

        int min_x = max(0, (camera.x / TILE_SIZE));
        int max_x = min(rooms_width, ((camera.x + SCREEN_WIDTH) / TILE_SIZE) + 1);
        int min_y = max(0, (camera.y / TILE_SIZE));
        int max_y = min(rooms_height, ((camera.y + SCREEN_HEIGHT) / TILE_SIZE) + 1);

        for (int x = min_x; x < max_x; x++) {
            for (int y = min_y; y < max_y; y++) {
                SDL_Rect tileRect = {tile[x][y].x - camera.x, tile[x][y].y - camera.y, TILE_SIZE, TILE_SIZE};
                if (rooms[x][y] >= 0 && rooms[x][y] < 14) {
                    SDL_RenderCopy(renderer, tile_texture, &tileTextures[rooms[x][y]], &tileRect);
                }
            }
        }

        circleRGBA(renderer, player.getPos()[0] - camera.x, player.getPos()[1] - camera.y, player.rad, 255, 255, 0, 255);
        player.move(rooms_col);

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        for (SDL_Rect rect: render_map) {
            if (rect.x / MAP_SIZE >= curRoom.x && rect.x / MAP_SIZE < curRoom.x + curRoom.w && rect.y / MAP_SIZE >= curRoom.y && rect.y / MAP_SIZE < curRoom.y + curRoom.h) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
            }
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_RenderPresent( renderer );

        startTicks = curTicks;
    }
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