#ifndef PHYSICS_CIRCLE_SHAPE
#define PHYSICS_CIRCLE_SHAPE

#include "physics/physics_shape_object.h"
typedef struct {
  double radius;
} PhysicsCircleShape;

PhysicsShapeObject *physics_circle_object_new(double x, double y, double radius, double mass);
void physics_circle_object_del(PhysicsShapeObject *obj);

#endif
