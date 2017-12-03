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

			SDL_Renderer *renderer = get_renderer();
			tex_wall = IMG_LoadTexture(renderer, "res/wall.png");
			tex_floor = IMG_LoadTexture(renderer, "res/floor.png");
			tex_man = IMG_LoadTexture(renderer, "res/man.png");

			return true;
		}

	virtual bool OnUpdate(float elapsed_time)
		{
			SDL_Renderer *renderer = get_renderer();
			SDL_Rect src = { 0, 0, 16, 16 };

			// Sort out player movement
			const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_LEFT])
			{
				man_vx = -1.0f;
			}
			if (state[SDL_SCANCODE_RIGHT])
			{
				man_vx = 1.0f;
			}
			if (state[SDL_SCANCODE_UP])
			{
				man_vy = -1.0f;
			}
			if (state[SDL_SCANCODE_DOWN])
			{
				man_vy = 1.0f;
			}

			float new_man_x = man_x + man_vx * elapsed_time;
			float new_man_y = man_y + man_vy * elapsed_time;

			// Check four corners of player for collision
			if (get_map(new_man_x, new_man_y) == ' ' &&
				get_map(new_man_x + 0.99f, new_man_y) == ' ' &&
				get_map(new_man_x, new_man_y + 0.99f) == ' ' &&
				get_map(new_man_x + 0.99f, new_man_y + 0.99f) == ' ')
			{
				man_x = new_man_x;
				man_y = new_man_y;
			}
			else
			{
				// This isn't ideal and need fixing as it'll just stop the player dead
				man_vx = 0.0f;
				man_vy = 0.0f;
			}

			// Draw the maze
			for (int y=0; y<maze_height; y++)
			{
				for (int x=0; x<maze_width; x++)
				{
					SDL_Rect dst = { x*32, y*32, 32, 32 };
					if (get_map(x, y) == '#')
						SDL_RenderCopy(renderer, tex_wall, &src, &dst);
					else
						SDL_RenderCopy(renderer, tex_floor, &src, &dst);
				}
			}

			// Draw the man
			SDL_Rect dst_man = { static_cast<int>(man_x * 32), static_cast<int>(man_y * 32), 32, 32 };
			SDL_RenderCopy(renderer, tex_man, &src, &dst_man);

			SDL_RenderPresent(renderer);
			return true;
		}

	virtual void OnDestroy()
	{
	}

private:
	const char get_map(float x, float y) const
	{
		return get_map(static_cast<int>(x), static_cast<int>(y));
	}
	const char get_map(int x, int y) const
	{
		return maze[y * maze_width + x];
	}

	string maze;
	int maze_height = 21;
	int maze_width = 19;

	float man_x = 9.0f;
	float man_y = 11.0f;
	float man_vx = 0.0f;
	float man_vy = 0.0f;

	SDL_Texture *tex_wall;
	SDL_Texture *tex_floor;
	SDL_Texture *tex_man;
};

#endif
