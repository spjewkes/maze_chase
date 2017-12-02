#ifndef __MAZE_CHASE_H__
#define __MAZE_CHASE_H__

#include <SDL2/SDL.h>
#include <string>
#include <cmath>
#include <iostream>
#include "gameframework.h"

using namespace std;

class GameMazeChase : public GameFramework
{
public:
	using GameFramework::GameFramework;

	virtual bool OnCreate()
		{
			return true;
		}

	virtual bool OnUpdate(float elapsed_time)
		{
			const Uint8 *state = SDL_GetKeyboardState(NULL);
			SDL_Renderer *renderer = get_renderer();
			SDL_RenderPresent(renderer);
			
			return true;
		}

	virtual void OnDestroy()
	{
	}

private:
	SDL_Texture* loadTexture(const char *filename)
	{
			SDL_Renderer *renderer = get_renderer();
			SDL_Surface *surf = SDL_LoadBMP(filename);
			if (!surf)
			{
				cerr << "Failed to load texture: " << filename << " : " <<  SDL_GetError() << endl;
				return NULL;
			}
			SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
			if (!tex)
			{
				cerr << "Failed to create texture from surface: " << filename << " : " <<  SDL_GetError() << endl;
				return NULL;
			}
			SDL_FreeSurface(surf);
			return tex;
	}
};

#endif
