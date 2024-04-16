#ifndef PHYSICS_OBJECT
#define PHYSICS_OBJECT

#include "engine/math/vector2d.h"

typedef struct {
  double mass;
  Vector2D *position;
  Vector2D *velocity;
  Vector2D *acceleration;
} PhysicsObject;

PhysicsObject *physics_object_new(double x, double y, double mass);
void physics_object_apply_force(PhysicsObject *obj, Vector2D *force);
void physics_object_del(PhysicsObject *obj);

#endif
