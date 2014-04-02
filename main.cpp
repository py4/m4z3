#include <iostream>
#include <cstdlib>
#include "maze.h"
using namespace std;

int main()
{
	srand(time(NULL));
	Maze maze;
	if(!maze.init(6,6))
	{
		cerr << "[main] couldn't init" << endl;
		return 0;
	}

	maze.dump_on_screen();

	bool quit = false;
	SDL_Event event;
	while(!quit)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
			if(event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
				case SDLK_UP:
					quit = maze.handle_key('U');
					break;
				case SDLK_DOWN:
					quit = maze.handle_key('D');
					break;
				case SDLK_LEFT:
					quit = maze.handle_key('L');
					break;
				case SDLK_RIGHT:
					quit = maze.handle_key('R');
					break;
				}
				if(quit)
					break;
				maze.dump_on_screen();
			}
		}
	}

	maze.free_everything();
	return 0;
}
