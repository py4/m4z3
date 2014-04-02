#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
using namespace std;
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

SDL_Surface* load_image(string);
void apply_surface(int x,int y, SDL_Surface*&, SDL_Surface*&);
