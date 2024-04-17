#include "./physics_object.h"
#include "math/vector2d.h"
#include <stdio.h>
#include <stdlib.h>

PhysicsObject *physics_object_new(double x, double y, double mass) {
  PhysicsObject *obj = malloc(sizeof(PhysicsObject));
  if (obj == NULL) {
    fprintf(stderr, "You can't allocate more memory");
  }

  obj->mass = mass;
  obj->position = vector2d_new(x, y);
  obj->velocity = vector2d_new(0, 0.1);
  obj->acceleration = vector2d_new(0, 0);

  return obj;
}

void physics_object_new_parent(PhysicsObject *obj, double x, double y,
                               double mass) {
  if (obj == NULL) {
    fprintf(stderr, "You can't allocate more memory");
  }

  obj->mass = mass;
  obj->position = vector2d_new(x, y);
  obj->velocity = vector2d_new(0, 0);
  obj->acceleration = vector2d_new(0, 0);
}

void physics_object_apply_force(PhysicsObject *obj, Vector2D *force) {
  Vector2D *force_clone = vector2d_clone(force);
  vector2d_div(force_clone, obj->mass);
  vector2d_add(obj->acceleration, force_clone);
  vector2d_del(force_clone);
}

void physics_object_del(PhysicsObject *obj) {
  if (obj == NULL) {
    return;
  }

  vector2d_del(obj->position);
  vector2d_del(obj->velocity);
  vector2d_del(obj->acceleration);

  free(obj);
}
