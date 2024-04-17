#ifndef PHYSICS_SHAPE_OBJECT
#define PHYSICS_SHAPE_OBJECT

#include "physics/physics_object.h"

enum PhysicsShapeObjectType { PHYSICS_SHAPE_SQUARE, PHYSICS_SHAPE_CIRCLE };

typedef struct {
  PhysicsObject *physics;
  void *shape;
  enum PhysicsShapeObjectType shape_type;
} PhysicsShapeObject;

PhysicsShapeObject *physics_shape_object_new(void *shape,
                                             PhysicsObject *physics);
void physics_circle_object_del(PhysicsShapeObject *obj);

#endif
