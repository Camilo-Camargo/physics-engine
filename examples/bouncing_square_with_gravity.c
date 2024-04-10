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
  int obj_width = 100;
  int obj_height = 100;
  double mass = 10;
  double x_middle = ((double)SCREEN_WIDTH / 2) - ((double)obj_width / 2);
  double y_middle = ((double)SCREEN_WIDTH / 2) - ((double)obj_height / 2);

  double width = SCREEN_WIDTH - obj_width;
  double height = SCREEN_HEIGHT - obj_height;

  Vector2D *position = vector2d_new(x_middle, (double)SCREEN_HEIGHT/2 - obj_height);
  Vector2D *velocity = vector2d_new(0, 0);
  Vector2D *acceleration = vector2d_new(0, 0);
  Vector2D *gravity = vector2d_new(0, 1);
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
    // end events

    // start physics

    if (position->x >  width || position->x < 0) {
      position->x = width;
      velocity->x *= -1;
    }

    if (position->y > height  || position->y < 0) {
      position->y = height;
      velocity->y *= -1;
    }

    Vector2D *force = vector2d_clone(gravity);
    vector2d_div(force, mass);
    vector2d_add(acceleration, force);
    vector2d_del(force);
    vector2d_add(velocity, acceleration);
    vector2d_add(position, velocity);
    vector2d_mul(acceleration, 0);
    // end physics

    // start render
    SDL_Rect rect = {position->x, position->y, obj_width, obj_height};

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    // end Render
    Uint64 timer_end = SDL_GetPerformanceCounter();
    float elapsedMS = (timer_end - timer_start) /
                      (float)SDL_GetPerformanceFrequency() * 1000.0f;
    SDL_Delay(floor(16.666f - elapsedMS));
    SDL_RenderPresent(renderer);
  }

  // start deletion
  // end deletion

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
