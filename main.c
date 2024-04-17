#include "main.h"
#include "engine/math/vector2d.h"
#include "engine/physics/physics_object.h"
#include "physics/physics_circle_object.h"
#include "physics/physics_shape_object.h"
#include "physics/physics_square_object.h"

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
  double x_middle = (double)SCREEN_WIDTH / 2;
  double y_middle = (double)SCREEN_WIDTH / 2;

  double square_width = 100;
  double square_height = 100;

  PhysicsShapeObject *square = physics_square_object_new(
      x_middle-square_width/2, 100, square_width, square_height, 1);

  double circle_radius = 10;
  PhysicsShapeObject *circle =
      physics_circle_object_new(x_middle-circle_radius, 100, circle_radius, 1);

  PhysicsShapeObject *objects[] = {square};

  size_t objects_len = sizeof objects / sizeof objects[0];

  Vector2D *gravity = vector2d_new(0, 0.1);
  Vector2D *wind = vector2d_new(0.1, 0);

  double friction_coefficient = 0.1;
  double normal = 1;
  double friction_mag = friction_coefficient * normal;
  double bounce = -0.9;

  double rho = 1;
  double frontal_surface = 1;
  double coefficient_of_drag = 2;
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
      double width = SCREEN_WIDTH;
      double height = SCREEN_HEIGHT;

      enum PhysicsShapeObjectType shape_object_type = objects[i]->shape_type;

      switch (shape_object_type) {
      case PHYSICS_SHAPE_CIRCLE: {
        PhysicsCircleShape *circle = (PhysicsCircleShape *)objects[i]->shape;
        width -= circle->radius;
        height -= circle->radius;
      } break;
      case PHYSICS_SHAPE_SQUARE: {
        PhysicsSquareShape *square = (PhysicsSquareShape *)objects[i]->shape;
        width -= square->width;
        height -= square->height;
      } break;
      }

      PhysicsObject *physics = objects[i]->physics;

      if (physics->position->x > width || physics->position->x < 0) {
        physics->velocity->x *= -1;
      }

      if (physics->position->y > height || physics->position->y < 0) {
        physics->position->y = height;
        // objects[i]->velocity->y *= bounce;
      }

      if (physics->position->y >= liquid_y - square_height) {
        Vector2D *drag = vector2d_clone(physics->velocity);
        vector2d_mul(drag, -1);
        double mag = vector2d_mag(physics->velocity);
        double speed = mag * mag;
        vector2d_set_mag(drag, (0.1) * rho * speed * frontal_surface *
                                   coefficient_of_drag);
        physics_object_apply_force(physics, drag);
        vector2d_del(drag);
      }

      if (physics->position->y > height - 1) {
        Vector2D *friction = vector2d_clone(physics->velocity);
        vector2d_mul(friction, -1);
        vector2d_mul(friction, friction_mag);
        physics_object_apply_force(physics, friction);
        vector2d_del(friction);
      }

      if (is_mouse_pressed && physics->position->y < liquid_y - square_height) {
        Vector2D *force_x = vector2d_clone(wind);
        physics_object_apply_force(physics, force_x);
        vector2d_del(force_x);
      }

      Vector2D *force_y = vector2d_clone(gravity);
      vector2d_mul(force_y, physics->mass);
      physics_object_apply_force(physics, gravity);
      vector2d_del(force_y);

      // update
      vector2d_add(physics->velocity, physics->acceleration);
      vector2d_add(physics->position, physics->velocity);
      vector2d_mul(physics->acceleration, 0);
      // end physics

      // start render
      switch (shape_object_type) {
      case PHYSICS_SHAPE_CIRCLE: {
        PhysicsCircleShape *shape = (PhysicsCircleShape *)objects[i]->shape;
        break;
      }
      case PHYSICS_SHAPE_SQUARE: {
        PhysicsSquareShape *shape = (PhysicsSquareShape *)objects[i]->shape;
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_Rect rect = {physics->position->x, physics->position->y,
                         shape->width, shape->height};
        SDL_RenderFillRect(renderer, &rect);
        break;
      }
      }
    }

    // end Render
    Uint64 timer_end = SDL_GetPerformanceCounter();
    float elapsedMS = (timer_end - timer_start) /
                      (float)SDL_GetPerformanceFrequency() * 1000.0f;
    SDL_Delay(floor(16.666f - elapsedMS));
    SDL_RenderPresent(renderer);
  }

  physics_square_object_del(square);
  physics_circle_object_del(circle);
  // start deletion
  // end deletion

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
