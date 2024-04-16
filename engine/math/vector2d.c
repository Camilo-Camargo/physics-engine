#include "vector2d.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: Implement safe malloc and safe free
Vector2D *vector2d_new(double x, double y) {
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

void vector2d_add(Vector2D *u, Vector2D *v) {
  if (u == NULL || v == NULL) {
    fprintf(stderr, "add vector2d");
  }

  u->x += v->x;
  u->y += v->y;
}

void sub(Vector2D *u, Vector2D *v) {
  if (u == NULL || v == NULL) {
    fprintf(stderr, "add vector2d");
  }

  u->x -= v->x;
  u->y -= v->y;
}

void vector2d_mul(Vector2D *u, double s) {
  if (u == NULL) {
    fprintf(stderr, "add vector2d");
  }

  Vector2D *w = vector2d_new(0, 0);

  u->x *= s;
  u->y *= s;
}

void vector2d_div(Vector2D *u, double s) {
  if (u == NULL) {
    fprintf(stderr, "add vector2d");
  }

  if (s == 0) {
    fprintf(stderr, "You try divide by 0");
    exit(1);
  }

  u->x /= s;
  u->y /= s;
}

Vector2D *vector2d_clone(Vector2D *u) {
  if (u == NULL) {
    fprintf(stderr, "add vector2d");
  }

  return vector2d_new(u->x, u->y);
}

void vector2d_normalize(Vector2D *u) {
  if (u == NULL) {
    fprintf(stderr, "add vector2d");
  }
  double mag = vector2d_mag(u);
  vector2d_div(u, mag);
}

Vector2D *vector2d_normalize_new(Vector2D *u) {
  if (u == NULL) {
    fprintf(stderr, "add vector2d");
  }

  double mag = vector2d_mag(u);
  Vector2D *v = vector2d_clone(u);
  vector2d_div(v, mag);

  return v;
}

double vector2d_mag(Vector2D *u) {
  if (u == NULL) {
    fprintf(stderr, "add vector2d");
  }

  return fabs(sqrt(u->x * u->x + u->y * u->y));
}

void vector2d_set_mag(Vector2D *u, double s) {
  if (u == NULL) {
    fprintf(stderr, "add vector2d");
  }

  vector2d_normalize(u);
  vector2d_mul(u, s);
}

void vector2d_limit(Vector2D *u, double l) {
  if (u == NULL) {
    fprintf(stderr, "add vector2d");
  }

  if (vector2d_mag(u) > l) {
    vector2d_set_mag(u, l);
  }
}
