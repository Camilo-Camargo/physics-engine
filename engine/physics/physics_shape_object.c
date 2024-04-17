#include "physics/physics_shape_object.h"
#include <stdio.h>
#include <stdlib.h>

PhysicsShapeObject *physics_shape_object_new(void *shape,
                                             PhysicsObject *physics) {
  PhysicsShapeObject *physics_shape = malloc(sizeof(PhysicsShapeObject));

  if (physics_shape == NULL) {
    fprintf(stderr, "You can't allocate more memory");
  }
  physics_shape->physics = physics;
  physics_shape->shape = shape;
  return physics_shape;
}

void physics_circle_object_del(PhysicsShapeObject *obj) {
  if (obj == NULL) {
    return;
  }
  free(obj);
}
