#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdint.h>
#include "vec2.h"

#define MAX_PARTICLES 1024

typedef struct {
    Vec2 pos[MAX_PARTICLES];
    Vec2 vel[MAX_PARTICLES];
    float radius[MAX_PARTICLES];
    uint32_t count;

    Vec2 gravity;
    float bounds_width;
    float bounds_height;
} PhysicsWorld;

void physics_init(PhysicsWorld* w, float width, float height);
void physics_spawn(PhysicsWorld* w, Vec2 pos, Vec2 vel, float radius);
void physics_step(PhysicsWorld* w, float dt);

#endif
