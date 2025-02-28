#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

class GameObject{
	public:
		virtual void Update(float deltaTime) = 0;
		virtual void Render(SDL_Renderer* renderer) = 0;
};


#endif /* _GAMEOBJECT_H_ */