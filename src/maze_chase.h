#ifndef __MAZE_CHASE_H__
#define __MAZE_CHASE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
			maze += "###################";
			maze += "#        #        #";
			maze += "# ## ### # ### ## #";
			maze += "#                 #";
			maze += "# ## # ##### # ## #";
			maze += "#    #   #   #    #";
			maze += "#### ### # ### ####";
			maze += "   # #       # #   ";
			maze += "#### # ## ## # ####";
			maze += "       #   #       ";
			maze += "#### # ##### # ####";
			maze += "   # #       # #   ";
			maze += "#### # ##### # ####";
			maze += "#        #        #";
			maze += "# ## ### # ### ## #";
			maze += "#  #           #  #";
			maze += "## # # ##### # # ##";
			maze += "#    #   #   #    #";
			maze += "# ###### # ###### #";
			maze += "#                 #";
			maze += "###################";

			/* tex_wall = loadTexture("res/wall.png"); */
			/* tex_floor = loadTexture("res/floor.png"); */
			/* tex_man = loadTexture("res/man.png"); */

			SDL_Renderer *renderer = get_renderer();
			tex_wall = IMG_LoadTexture(renderer, "res/wall.png");
			tex_floor = IMG_LoadTexture(renderer, "res/floor.png");
			tex_man = IMG_LoadTexture(renderer, "res/man.png");

			return true;
		}

	virtual bool OnUpdate(float elapsed_time)
		{
			const Uint8 *state = SDL_GetKeyboardState(NULL);
			SDL_Renderer *renderer = get_renderer();

			for (int y=0; y<maze_height; y++)
			{
				for (int x=0; x<maze_width; x++)
				{
					SDL_Rect src = { 0, 0, 16, 16 };
					SDL_Rect dst = { x*32, y*32, 32, 32 };
					if (maze[y * maze_width + x] == '#')
						SDL_RenderCopy(renderer, tex_wall, &src, &dst);
					else
						SDL_RenderCopy(renderer, tex_floor, &src, &dst);
				}
			}

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
			SDL_Surface *surf = IMG_Load(filename);
			if (!surf)
			{
				cerr << "Failed to load image: " << filename << " : " <<  IMG_GetError() << endl;
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

	string maze;
	int maze_height = 21;
	int maze_width = 19;

	SDL_Texture *tex_wall;
	SDL_Texture *tex_floor;
	SDL_Texture *tex_man;
};

#endif
