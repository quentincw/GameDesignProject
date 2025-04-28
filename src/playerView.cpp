#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "playerView.h"
#include "gameProcess.h"
#include "gameObject.h"
#include "floor.h"
#include "Player1.h"
#include "bloodStain.h"
#include <iostream>
#include <SDL_mixer.h>

PlayerView::PlayerView() {

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
  
    tileTextures[0] = tile_0;
    tileTextures[1] = tile_1;
    tileTextures[2] = tile_2;
    tileTextures[3] = tile_3;
    tileTextures[4] = tile_4;
    tileTextures[5] = tile_5;
    tileTextures[6] = tile_6;
    tileTextures[7] = tile_7;
    tileTextures[8] = tile_8;
    tileTextures[9] = tile_9;
    tileTextures[10] = tile_10;
    tileTextures[11] = tile_11;
    tileTextures[12] = tile_12;
    tileTextures[13] = tile_13;
}

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
    SDL_Surface* tile_surface_1 = SDL_LoadBMP("../resource/tile_1.bmp");
    SDL_Surface* tile_surface_2 = SDL_LoadBMP("../resource/tile_2.bmp");
    SDL_Surface* tile_surface_3 = SDL_LoadBMP("../resource/tile_3.bmp");
    // convert to texture
    tile_texture_1 = SDL_CreateTextureFromSurface( renderer, tile_surface_1 );
    tile_texture_2 = SDL_CreateTextureFromSurface( renderer, tile_surface_2 );
    tile_texture_3 = SDL_CreateTextureFromSurface( renderer, tile_surface_3 );

    SDL_Texture* texture_1;
    SDL_Texture* texture_2;
    SDL_Texture* texture_3;

    for (int i = 1; i <= total_frames; ++i) {
        SDL_Surface* surface_1 = SDL_LoadBMP(("../resource/frames_1/" + to_string(i) + ".bmp").c_str());
        texture_1 = SDL_CreateTextureFromSurface( renderer, surface_1 );
        frames_1.push_back(texture_1);
    };

    for (int i = 1; i <= total_frames; ++i) {
        SDL_Surface* surface_2 = SDL_LoadBMP(("../resource/frames_2/" + to_string(i) + ".bmp").c_str());
        texture_2 = SDL_CreateTextureFromSurface( renderer, surface_2 );
        frames_2.push_back(texture_2);
    };

    for (int i = 1; i <= total_frames; ++i) {
        SDL_Surface* surface_3 = SDL_LoadBMP(("../resource/frames_3/" + to_string(i) + ".bmp").c_str());
        texture_3 = SDL_CreateTextureFromSurface( renderer, surface_3 );
        frames_3.push_back(texture_3);
    };

    // initialize SDL audio and mixer
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << " (" << SDL_GetError() << ")" << std::endl;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << " (" << SDL_GetError() << ")" << std::endl;
    }

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

// plays sounds from processes in the process manager
void PlayerView::playSounds(ProcessManager* pm) {

    soundPlayer.playSounds(pm->getSoundList());

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
                    case SDLK_SPACE:
                        player->dodgeRoll();
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
                    {
						int mouseX = 0;
						int mouseY = 0;
					 	Uint32 mouse = SDL_GetMouseState(&mouseX, &mouseY);
						player->updateMouse(mouseX, mouseY);

						player->shootProj(cameraX, cameraY);
						break;
                    }
                    case SDL_BUTTON_RIGHT:
                        player->dodgeRoll();
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

    int level = floor->getLevel();
    if (level == 1) {
        frames = frames_1;
    }
    if (level == 2) {
        frames = frames_2;
    }
    if (level == 3) {
        frames = frames_3;
    }

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

    renderMinimap(floor);

    renderHealthBar(dynamic_cast<Player1*>(pm->getPlayer()));
	
    SDL_RenderPresent( renderer );
}


// renders the floor / room
void PlayerView::renderLevel(Floor* floor)
{
    int level = floor->getLevel();
    if (level == 1) {
        tile_texture = tile_texture_1;
    }
    if (level == 2) {
        tile_texture = tile_texture_2;
    }
    if (level == 3) {
        tile_texture = tile_texture_3;
    }

    vector<vector<int>> rooms = floor->getRooms();
    int rooms_width = rooms.size();
    int rooms_height = rooms[0].size();
    vector<vector<int>> rooms_col = floor->getRoomsCol();

    SDL_Rect curRoom = floor->getCurRoom();
  
    vector<vector<SDL_Rect>> tile(rooms_width, vector<SDL_Rect>(rooms_height));

    for (int x = 0; x < rooms_width; x++) {
        for (int y = 0; y < rooms_height; y++) {
            tile[x][y].x = x * TILE_SIZE;
            tile[x][y].y = y * TILE_SIZE;
            tile[x][y].w = TILE_SIZE;
            tile[x][y].h = TILE_SIZE;
        }
    }
    
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
}

void PlayerView::renderProcesses(ProcessManager* pm)
{
	//pm->renderProcessesCam( renderer, cameraX, cameraY );
    vector<GameProcess*> processes = pm->getProcessList();
    GameProcess* curProcess;

    // render bloodstains
	for(int i = 0; i < processes.size(); i++){
        curProcess = processes[i];
        if (auto blood = dynamic_cast<BloodStain*>(curProcess)) {
            curProcess->RenderCam(renderer, cameraX, cameraY );
        }
    }
    // render not blood stains
    for(int i = 0; i < processes.size(); i++){
        curProcess = processes[i];
        if (auto blood = dynamic_cast<BloodStain*>(curProcess)) {
            continue;
        }
        curProcess->RenderCam(renderer, cameraX, cameraY );
    }
	pm->getPlayer()->RenderCam(renderer, cameraX, cameraY);
}

// updates the camera's position based on the player's position
void PlayerView::updateCameraPosition(ProcessManager* pm)
{
    GameProcess* player = pm->getPlayer();
    cameraX = (player->getHitbox().x + player->getHitbox().width / 2) - SCREEN_WIDTH / 2;
    cameraY = (player->getHitbox().y + player->getHitbox().height / 2) - SCREEN_HEIGHT / 2;
}

void PlayerView::renderMinimap(Floor* floor) {

    int level = floor->getLevel();
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
    // minimap rooms
    SDL_Rect curRoom = floor->getCurRoom();
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

void PlayerView::renderHealthBar(Player1* player)
{
    int health = player->getHealth();
    int maxHealth = 100;

    float percent = std::max(0.0f, std::min(1.0f, health / (float)maxHealth));

    int barWidth = 200;
    int barHeight = 20;
    int margin = 20;

    int x = SCREEN_WIDTH - barWidth - margin;
    int y = margin;

    SDL_Rect bg = {x, y, barWidth, barHeight};
    SDL_Rect fill = {x, y, static_cast<int>(barWidth * percent), barHeight};

    // Background
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &bg);

    // Health color (green to red)
    Uint8 red = static_cast<Uint8>((1.0f - percent) * 255);
    Uint8 green = static_cast<Uint8>(percent * 255);
    SDL_SetRenderDrawColor(renderer, red, green, 0, 255);
    SDL_RenderFillRect(renderer, &fill);

    // Border
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &bg);
}