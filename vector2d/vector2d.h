#ifndef VECTOR2D
#define VECTOR2D


#include <stdint.h>
typedef struct Vector2DStruct {
  int16_t x;
  int16_t y;
} Vector2D;

Vector2D *vector2d_new(int16_t x, int16_t y);
Vector2D *vector2d_add(Vector2D *u, Vector2D *v);
Vector2D *vector2d_sub(Vector2D *u, Vector2D *v);
Vector2D *vector2d_mul(Vector2D *u, double s);
void vector2d_del(Vector2D *u);

#endif
