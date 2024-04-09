#include "vector2d.h"
#include <stdio.h>
#include <stdlib.h>

// TODO: Implement safe malloc and safe free
Vector2D *vector2d_new(int16_t x, int16_t y) {
  Vector2D *u = malloc(sizeof(Vector2D));
  if (u == NULL) {
    fprintf(stderr, "You can't allocate more memory");
  }

  u->x = x;
  u->y = y;

  return u;
}

void vector2d_del(Vector2D *u) {
  if (u == NULL) {
    return;
  }

  free(u);
}

Vector2D *vector2d_add(Vector2D *u, Vector2D *v) {
  if (u == NULL || v == NULL) {
    fprintf(stderr, "add vector2d");
  }

  Vector2D *w = vector2d_new(0, 0);

  w->x = u->x + v->x;
  w->y = u->y + v->y;

  return w;
}

Vector2D *sub(Vector2D *u, Vector2D *v) {
  if (u == NULL || v == NULL) {
    fprintf(stderr, "add vector2d");
  }

  Vector2D *w = vector2d_new(0, 0);

  w->x = u->x - v->x;
  w->y = u->y - v->y;

  return w;
}

Vector2D *vector2d_mul(Vector2D *u, double s) {
  if (u == NULL) {
    fprintf(stderr, "add vector2d");
  }

  Vector2D *w = vector2d_new(0, 0);

  w->x = u->x * s;
  w->y = u->y * s;

  return w;
}
