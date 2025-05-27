#ifndef GPROCESS_H
#define GPROCESS_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include "gameObject.h"
#include <unordered_set>
#include "gameSounds.h"

class GameProcess : public GameObject {

    public:
        // constructor for process
        GameProcess();

        // destructor
        virtual ~GameProcess();

        // updates the object
        virtual void Update(float deltaTime) = 0;

        // draws the object
        virtual void Render(SDL_Renderer* renderer) = 0;

        // draws the object based on the camera's position
        virtual void RenderCam(SDL_Renderer* renderer, int camX, int camY) = 0;

        // marks process for deletion by changing delete flag (boolean)
        void markForDeletion();

        // returns whether the process is marked for deletion
        bool getMarkForDeletion() const;

        // returns whether the process has children
        bool hasChildren() const;

        // returns whether the process has children
        bool hasSounds() const;

        // returns a vector of all the children of a process
        std::vector<GameProcess*> getChildren();

        // returns a vector of all the sounds of a process
        std::vector<SoundType> getSounds();

        // returns a vector of target tags the proccess can interact with
        std::unordered_set<std::string> getInteractions() const;

        // returns the vector of tags of the process
        std::unordered_set<std::string> getTags() const;

        // handles interaction with a given tag
        virtual void handleInteraction(std::string tag);

        // gets the damage an enemy does on contact
        int getDamage() const;

    protected:

        // list of tags associated with the process
        std::unordered_set<std::string> tags;

        // list of tags process can interact with
        std::unordered_set<std::string> interactions;

        // vector of all the sounds currently produced by a process
        std::vector<SoundType> soundList;

        // the radius of the circle for rendering
        int radius;

        // mark for deletion flag
        bool deleteFlag;

        // flag for if a process has children
        bool children;

        // vector of all the children of a process
        std::vector<GameProcess*> childrenList;

        // flag for if a process has sounds
        bool sounds;

        // the damage a process does on collision
        int damage;
};

#endif