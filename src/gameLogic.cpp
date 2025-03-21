// #include "gameLogic.h"
// #include "gameProcess.h"
// #include "gameObject.h"

// GameLogic::GameLogic(ProcessManager* pm, LevelManager* lm)
//     : processManager(pm), levelManager(lm)
// {
// }

// void GameLogic::update()
// {
//     checkCollisions();
// }

// bool GameLogic::isColliding(const GameObject* a, const GameObject* b) const
// {
//     return (a->x < (b->x + b->width)) &&
//            ((a->x + a->width) > b->x) &&
//            (a->y < (b->y + b->height)) &&
//            ((a->y + a->height) > b->y);
// }

// void GameLogic::checkCollisions()
// {
//     auto& processes = processManager->getProcesses();
//     for (size_t i = 0; i < processes.size(); ++i)
//     {
//         Process* p1 = processes[i];
//         for (size_t j = i + 1; j < processes.size(); ++j)
//         {
//             Process* p2 = processes[j];
            
//             if (!p1 || !p2) 
//                 continue;

//             const auto& interactions = p1->getInteractions();
            
//             for (const auto& kv : interactions)
//             {
//                 if (p2->hasTag(kv.first))
//                 {
//                     if (isColliding(p1, p2))
//                     {
//                         handleCollision(p1, p2, kv.first);
//                     }
//                 }
//             }
//         }
//     }

//     const auto& walls = levelManager->getWalls();
//     for (Process* proc : processes)
//     {
//         if (!proc) 
//             continue;

//         for (const auto& wall : walls)
//         {
//             if (isColliding(proc, &wall))
//             {
//                 proc->handleInteraction("wall");
//             }
//         }
//     }
// }

// void GameLogic::handleCollision(Process* p1, Process* p2, const std::string& matchedTag)
// {
//     p2->adjustHealth(p1->getInteractions().at(matchedTag));
//     p1->handleInteraction(matchedTag);
// }