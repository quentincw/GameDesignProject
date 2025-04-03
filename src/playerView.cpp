// #include "playerView.h"
// #include "gameProcess.h"
// #include "gameObject.h"

// PlayerView::PlayerView(ProcessManager* pm, LevelManager* lm)
//     : processManager(pm), levelManager(lm)
// {
// }

// void PlayerView::render()
// {
//     updateCameraPosition();

//     renderLevel();

//     renderProcesses();
// }

// void PlayerView::renderLevel()
// {
//     const auto& walls = levelManager->getWalls();
//     for (const auto& tile : walls)
//     {
//         tile.RenderCam( renderer, cameraX, cameraY);  
//     }
// }

// void PlayerView::renderProcesses()
// {
//     processManager.RenderProcessesCam( renderer, cameraX, cameraY );

//     /*const auto& processes = processManager->getProcesses();
//     for (Process* process : processes)
//     {
//         if (!process) 
//             continue;

//         process->render();
//     }*/
// }

   // updates the camera's position based on the player's position
// void PlayerView::updateCameraPosition()
// {
//     GameProcess* player = processManager.getPlayer();
//     cameraX = (player->getHitbox().x + player->getHitbox().width / 2) - SCREEN_WIDTH / 2;
//     cameraY = (player->getHitbox().y + player->getHitbox().height / 2) - SCREEN_HEIGHT / 2;

// }

