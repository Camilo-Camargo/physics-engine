#include "main.h"
#include "vector2d.h"

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

  Vector2D *square_speed = vector2d_new(2.5, 2);
  Vector2D *square_position = vector2d_new(20, 20);
  uint16_t square_w = 100;
  uint16_t square_h = 100;

  SDL_Event e;
  bool is_open = true;
  while (is_open) {

    Uint64 timer_start = SDL_GetPerformanceCounter();
    clear(renderer);

    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        is_open = false;
      }
    }

    vector2d_add(square_position, square_speed);

    if (square_position->x > (SCREEN_WIDTH - square_w) || square_position->x < 0) {
      square_speed->x *= -1;
    }

    if (square_position->y > (SCREEN_HEIGHT - square_h) || square_position->y < 0) {
      square_speed->y *= -1;
    }

    SDL_Rect square = {square_position->x, square_position->y, 100, 100};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &square);
    SDL_RenderPresent(renderer);

    Uint64 timer_end = SDL_GetPerformanceCounter();
    float elapsedMS = (timer_end - timer_start) /
                      (float)SDL_GetPerformanceFrequency() * 1000.0f;
    SDL_Delay(floor(16.666f - elapsedMS));
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
