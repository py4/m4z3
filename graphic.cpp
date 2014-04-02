#include <iostream>
#include "graphic.h"
using namespace std;



SDL_Surface* load_image(string file_name)
{
	SDL_Surface* temp_image = NULL;
	SDL_Surface* image = NULL;
	temp_image = IMG_Load(file_name.c_str());
	if(temp_image != NULL)
	{
		image = SDL_DisplayFormat(temp_image);
		SDL_SetColorKey(image,SDL_SRCCOLORKEY,0x000000);
		SDL_FreeSurface(temp_image);
	}
	else
	{
		cerr << "image load failed" << endl;
		cerr << SDL_GetError() << endl;
	}
	return image;
}

void apply_surface(int x,int y, SDL_Surface*& source, SDL_Surface*& destination)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source,NULL,destination,&offset);
}


