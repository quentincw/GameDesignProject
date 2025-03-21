#ifndef GPROCESS_H
#define GPROCESS_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include "gameObject.h"



class GameProcess : public GameObject {

    public:

        // constructor for process
        GameProcess();

        // updates the object
        virtual void Update(float deltaTime) = 0;

        // draws the object
        virtual void Render(SDL_Renderer* renderer) = 0;

        // handles the interactions with other objects
        virtual void handleInteractions(int tag) = 0;

        // marks process for deletion by changing delete flag (boolean)
        void markForDeletion();

        // returns whether the process is marked for deletion
        bool getMarkForDeletion() const;

        // returns whether the process has children
        bool hasChildren() const;

        // returns a vector of all the children of a process
        std::vector<GameProcess*> getChildren();

        // returns the vector of tags of the process
        std::vector<std::string> getTags() const;



    protected:

        // list of tags the process can interact with
        std::vector<std::string> tags;

        // map of all possible interactions a process can have
        //map<string, int> interactions;

        // the radius of the circle for rendering
        int radius;

        // mark for deletion flag
        bool deleteFlag;

        // flag for if a process has children
        bool children;

        // vector of all the children of a process
        std::vector<GameProcess*> childrenList;

};


#endif