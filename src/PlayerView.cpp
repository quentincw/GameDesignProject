/*#include "PlayerView.h"
#include "Process.h"
#include "GameObject.h"

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
*/