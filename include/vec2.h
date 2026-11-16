/*
    16-Nov-2026
    Bora Kirli
*/

#ifndef VEC2_H
#define VEC2_H

#include <math.h>

typedef struct {
    float x, y;
} Vec2;

static inline Vec2 vec2_add(Vec2 a, Vec2 b) { return (Vec2){ a.x + b.x, a.y + b.y }; }
static inline Vec2 vec2_sub(Vec2 a, Vec2 b) { return (Vec2){ a.x - b.x, a.y - b.y }; }
static inline Vec2 vec2_scale(Vec2 v, float s) { return (Vec2){ v.x * s, v.y * s }; }
static inline float vec2_dot(Vec2 a, Vec2 b) { return a.x * b.x + a.y * b.y; }
static inline float vec2_len_sq(Vec2 v) { return v.x * v.x + v.y * v.y; }
static inline float vec2_len(Vec2 v) { return sqrtf(vec2_len_sq(v)); }

#endif
