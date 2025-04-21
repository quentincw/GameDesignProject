#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "playerView.h"
#include "gameProcess.h"
#include "gameObject.h"
#include "floor.h"

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
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED );
    if (renderer == NULL) std::cerr << " (" << SDL_GetError() << ")" << std::endl;

    // render tiles
    SDL_Surface* tile_surface = SDL_LoadBMP("../resource/tile_f4.bmp");
    // convert to texture
    tile_texture = SDL_CreateTextureFromSurface( renderer, tile_surface );

    SDL_Texture* texture;

    for (int i = 1; i <= total_frames; ++i) {
        SDL_Surface* surface = SDL_LoadBMP(("../resource/frames/" + to_string(i) + ".bmp").c_str());
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        frames.push_back(texture);
    };
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
                    case SDLK_g:
                        return 5;
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
                    case SDLK_y:
                        cout << "x: " << player->getHitbox().x << "y: " << player->getHitbox().y << endl;
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

void PlayerView::render(Floor* floor, ProcessManager* pm)
{
	SDL_RenderClear( renderer );

    static const int fps = 12;
    static int frame = 0;

    static Uint64 startTicks = SDL_GetTicks();

    Uint64 curTicks = SDL_GetTicks();
    float deltaTime = curTicks - startTicks;
    if (deltaTime > 1000 / fps) {
        frame = (frame + 1) % total_frames;
        startTicks = curTicks;
    }

    SDL_RenderCopy(renderer, frames[frame], NULL, NULL);
    
    updateCameraPosition(pm);

    renderLevel(floor);

    renderProcesses(pm);
	
    SDL_RenderPresent( renderer );
}

void PlayerView::render(std::vector<GameObject*> walls, ProcessManager* pm)
{
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );
	
    updateCameraPosition(pm);

	renderLevel(walls);

    renderProcesses(pm);
	
	//renderMinimap(walls);
	
	SDL_RenderPresent( renderer );
}

void PlayerView::renderLevel(Floor* floor)
{
    testLevelRendering(floor);
    /*
	GameObject* curWall;
	for(int i = 0; i < walls.size(); i++){
        curWall = walls[i];
        curWall->RenderCam(renderer, cameraX, cameraY );
    }*/
    /*const auto& walls = levelManager->getWalls();
    for (const auto& tile : walls)
    {
        tile.RenderCam( renderer, cameraX, cameraY);  
    }*/
}

void PlayerView::renderLevel(std::vector<GameObject*> walls)
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

void PlayerView::testLevelRendering(Floor* floor) {
    vector<vector<int>> rooms = floor->getRooms();
    int rooms_width = rooms.size();
    int rooms_height = rooms[0].size();
    vector<vector<int>> rooms_col = floor->getRoomsCol();
  
    vector<vector<SDL_Rect>> tile(rooms_width, vector<SDL_Rect>(rooms_height));
    vector<vector<SDL_Rect>> map(rooms_width, vector<SDL_Rect>(rooms_height));
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

    //floor->setCurRoom(player.getPos()[0] / TILE_SIZE, player.getPos()[1] / TILE_SIZE);
    SDL_Rect curRoom = floor->getCurRoom();

    int min_x = max(0, (cameraX / TILE_SIZE));
    int max_x = min(rooms_width, ((cameraX + SCREEN_WIDTH) / TILE_SIZE) + 1);
    int min_y = max(0, (cameraY / TILE_SIZE));
    int max_y = min(rooms_height, ((cameraY + SCREEN_HEIGHT) / TILE_SIZE) + 1);

    for (int x = min_x; x < max_x; x++) {
        for (int y = min_y; y < max_y; y++) {
            SDL_Rect tileRect = {tile[x][y].x - cameraX, tile[x][y].y - cameraY, TILE_SIZE, TILE_SIZE};
            if (rooms[x][y] >= 0 && rooms[x][y] < 14) {
                SDL_RenderCopy(renderer, tile_texture, &tileTextures[rooms[x][y]], &tileRect);
            }
        }
    }

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
}

