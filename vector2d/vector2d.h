#ifndef VECTOR2D
#define VECTOR2D

typedef struct Vector2DStruct {
  double x;
  double y;
} Vector2D;

Vector2D *vector2d_new(double x, double y);
void vector2d_add(Vector2D *u, Vector2D *v);
void vector2d_sub(Vector2D *u, Vector2D *v);
void vector2d_mul(Vector2D *u, double s);
void vector2d_del(Vector2D *u);

#endif
