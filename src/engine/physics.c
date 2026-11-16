#include "physics.h"
#include "collision.h"

void physics_init(PhysicsWorld* w, float width, float height) {
    w->count = 0;
    w->gravity = (Vec2){ 0.0f, 980.0f };
    w->bounds_width = width;
    w->bounds_height = height;
}

void physics_spawn(PhysicsWorld* w, Vec2 pos, Vec2 vel, float radius) {
    if (w->count >= MAX_PARTICLES) return;
    uint32_t i = w->count++;
    w->pos[i] = pos;
    w->vel[i] = vel;
    w->radius[i] = radius;
}

void physics_step(PhysicsWorld* w, float dt) {
    const int substeps = 8;
    float sub_dt = dt / (float)substeps;

    for (int step = 0; step < substeps; step++) {
        for (uint32_t i = 0; i < w->count; i++) {
            w->vel[i] = vec2_add(w->vel[i], vec2_scale(w->gravity, sub_dt));
            w->pos[i] = vec2_add(w->pos[i], vec2_scale(w->vel[i], sub_dt));
        }

        collision_solve_particles(w);
        collision_solve_bounds(w);
    }
}
