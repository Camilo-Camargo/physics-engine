#include "./physics_circle_object.h"
#include "physics/physics_shape_object.h"
#include <stdio.h>
#include <stdlib.h>



PhysicsShapeObject *physics_circle_object_new(double x, double y, double radius, double mass){
  PhysicsCircleShape *shape = malloc(sizeof(PhysicsCircleShape));
  if (shape == NULL) {
    fprintf(stderr, "You can't allocate more memory");
  }

  shape->radius = radius;

  PhysicsObject *physics = physics_object_new(x, y, mass);

  PhysicsShapeObject *shape_object = physics_shape_object_new(shape, physics);
  shape_object->shape = shape;
  shape_object->shape_type = PHYSICS_SHAPE_CIRCLE;
  shape_object->physics = physics;
  return shape_object;
}

void physics_circle_objec_del(PhysicsShapeObject *obj){
  if (obj == NULL) {
    return;
  }

  PhysicsCircleShape *shape = obj->shape;
  if (shape != NULL) {
    free(shape);
  }

  PhysicsObject *physics = obj->physics;

  if (physics != NULL) {
    physics_object_del(physics);
  }

  if (obj->shape == NULL) {
    return;
  }

  free(obj);
}
