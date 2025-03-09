#ifndef GPROCESS_H
#define GPROCESS_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include <bits/stdc++.h>


struct Circle {
    int x;
    int y;
    int radius;
};

class GameProcess {

    public:

        // constructor for process
        GameProcess();

        // updates the object
        virtual void Update(float deltaTime) = 0;

        // draws the object
        virtual void Render(SDL_Renderer* renderer) = 0;

        // marks process for deletion by changing delete flag (boolean)
        void markForDeletion();

        // returns whether the process is marked for deletion
        bool getMarkForDeletion() const;

        // returns the vector of tags of the process
        std::vector<std::string> getTags() const;



    protected:

        // list of tags the process can interact with
        std::vector<std::string> tags;

        // map of all possible interactions a process can have
        //map<string, int> interactions;

        // mark for deletion flag
        bool deleteFlag;



};


#endif