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
void vector2d_div(Vector2D *u, double s);
Vector2D *vector2d_clone(Vector2D *u);
Vector2D *vector2d_normalize_new(Vector2D *u);
void vector2d_normalize(Vector2D *u);
double vector2d_mag(Vector2D *u);
void vector2d_limit(Vector2D *u, double l);
void vector2d_set_mag(Vector2D *u, double s);
void vector2d_del(Vector2D *u);

#endif
