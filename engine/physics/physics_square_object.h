#ifndef PHYSICS_SQUARE_OBJECT
#define PHYSICS_SQUARE_OBJECT

#include "physics/physics_shape_object.h"

typedef struct {
  double width;
  double height;
} PhysicsSquareShape;

PhysicsShapeObject *physics_square_object_new(double x, double y, double width,
                                              double height, double mass);
void physics_square_object_del(PhysicsShapeObject *obj);

#endif
