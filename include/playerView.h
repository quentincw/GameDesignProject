#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "ProcessManager.h"
#include "LevelManager.h"

class PlayerView
{
public:
    PlayerView(ProcessManager* pm, LevelManager* lm);

    void render();

private:
    ProcessManager* processManager;
    LevelManager*   levelManager;

    void renderLevel();

    void renderProcesses();
};

#endif
