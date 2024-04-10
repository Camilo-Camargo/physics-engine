#include "main.h"
#include "engine/math/vector2d.h"

#include "SDL_error.h"
#include "SDL_video.h"
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void clear(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
}

int main(void) {
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    // TODO: Add loggers with custom profiles
    fprintf(stderr, "SDL couldn't initiate %s\n", SDL_GetError());
    return -1;
  }

  window = SDL_CreateWindow(PROGRAM_TITLE, SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    fprintf(stderr, "SDL couldn't not create window:  %s\n", SDL_GetError());
    return -1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    fprintf(stderr, "SDL couldn't not create renderer:  %s\n", SDL_GetError());
    return -1;
  }

  // start creation
  // end creation

  SDL_Event e;
  bool is_open = true;
  while (is_open) {

    Uint64 timer_start = SDL_GetPerformanceCounter();
    clear(renderer);

    // start events
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        is_open = false;
      }
    } 
    //end events




    // start physics
    // end physics
    



    // start render
    // end Render
    Uint64 timer_end = SDL_GetPerformanceCounter();
    float elapsedMS = (timer_end - timer_start) /
                      (float)SDL_GetPerformanceFrequency() * 1000.0f;
    SDL_Delay(floor(16.666f - elapsedMS));
  }

  // start deletion
  // end deletion

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
