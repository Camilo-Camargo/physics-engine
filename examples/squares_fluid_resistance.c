#include "main.h"
#include "engine/math/vector2d.h"
#include "engine/physics/physics_object.h"

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
#include <sys/_types/_size_t.h>

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
  int figure_width = 100;
  int figure_height = 100;

  double x_middle = ((double)SCREEN_WIDTH / 2) - ((double)figure_width / 2);
  double y_middle = ((double)SCREEN_WIDTH / 2) - ((double)figure_height / 2);

  double width = SCREEN_WIDTH - figure_width;
  double height = SCREEN_HEIGHT - figure_height;

  PhysicsObject *obj = physics_object_new(
      x_middle, (double)SCREEN_HEIGHT / 2 - figure_height, 1);

  PhysicsObject *obj2 =
      physics_object_new(x_middle + figure_width + 20,
                         (double)SCREEN_HEIGHT / 2 - figure_height, 20);


  PhysicsObject *obj3 =
      physics_object_new(x_middle - figure_width - 20,
                         (double)SCREEN_HEIGHT / 2 - figure_height, 10);

  PhysicsObject *objects[] = {obj, obj2, obj3};
  size_t objects_len = sizeof objects / sizeof objects[0];
  printf("%zu", objects_len);

  Vector2D *gravity = vector2d_new(0, 0.1);
  Vector2D *wind = vector2d_new(0.1, 0);

  double friction_coefficient = 0.1;
  double normal = 1;
  double friction_mag = friction_coefficient * normal;
  double bounce = -0.9;

  double rho = 1;
  double frontal_surface = 1;
  double coefficient_of_drag = 1;
  double liquid_y = ((double)SCREEN_HEIGHT / 2) + ((double)SCREEN_HEIGHT / 6);
  // end creation

  SDL_Event e;
  bool is_open = true;
  while (is_open) {

    Uint64 timer_start = SDL_GetPerformanceCounter();
    clear(renderer);

    bool is_mouse_pressed = false;
    // start events
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        is_open = false;
      }

      if (e.type == SDL_MOUSEBUTTONDOWN) {
        is_mouse_pressed = true;
      }
    }
    // end events
    SDL_SetRenderDrawColor(renderer, 46, 163, 242, 255);
    SDL_Rect liquid = {0, liquid_y, SCREEN_WIDTH, SCREEN_HEIGHT - liquid_y};
    SDL_RenderFillRect(renderer, &liquid);

    // start physics
    for (size_t i = 0; i < objects_len; i++) {

      if (objects[i]->position->x > width || objects[i]->position->x < 0) {
        objects[i]->velocity->x *= -1;
      }

      if (objects[i]->position->y > height || objects[i]->position->y < 0) {
        objects[i]->position->y = height;
        // objects[i]->velocity->y *= bounce;
      }

      if (objects[i]->position->y >= liquid_y - figure_height) {
        Vector2D *drag = vector2d_clone(objects[i]->velocity);
        vector2d_mul(drag, -1);
        double mag = vector2d_mag(objects[i]->velocity);
        double speed = mag * mag;
        vector2d_set_mag(drag, (0.1) * rho * speed * frontal_surface *
                                   coefficient_of_drag);
        physics_object_apply_force(objects[i], drag);
        vector2d_del(drag);
      }

      if (objects[i]->position->y > height - 1) {
        Vector2D *friction = vector2d_clone(objects[i]->velocity);
        vector2d_mul(friction, -1);
        vector2d_mul(friction, friction_mag);
        physics_object_apply_force(objects[i], friction);
        vector2d_del(friction);
      }

      if (is_mouse_pressed &&
          objects[i]->position->y < liquid_y - figure_height) {
        Vector2D *force_x = vector2d_clone(wind);
        physics_object_apply_force(objects[i], force_x);
        vector2d_del(force_x);
      }

      Vector2D *force_y = vector2d_clone(gravity);
      vector2d_mul(force_y, objects[i]->mass);
      physics_object_apply_force(objects[i], gravity);
      vector2d_del(force_y);

      // update
      vector2d_add(objects[i]->velocity, objects[i]->acceleration);
      vector2d_add(objects[i]->position, objects[i]->velocity);
      vector2d_mul(objects[i]->acceleration, 0);
      // end physics

      // start render
      SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
      SDL_Rect rect = {objects[i]->position->x, objects[i]->position->y,
                       figure_width, figure_height};
      SDL_RenderFillRect(renderer, &rect);
    }

    // end Render
    Uint64 timer_end = SDL_GetPerformanceCounter();
    float elapsedMS = (timer_end - timer_start) /
                      (float)SDL_GetPerformanceFrequency() * 1000.0f;
    SDL_Delay(floor(16.666f - elapsedMS));
    SDL_RenderPresent(renderer);
  }

  physics_object_del(obj);
  physics_object_del(obj2);
  physics_object_del(obj3);
  // start deletion
  // end deletion

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
