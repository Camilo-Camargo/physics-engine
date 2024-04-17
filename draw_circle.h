#ifndef PHYSICS_DRAW_CIRCLE
#define PHYSICS_DRAW_CIRCLE

#include <SDL_render.h>
int SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius);
int SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius);

#endif
