#include "physics.h"

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
    for (uint32_t i = 0; i < w->count; i++) {
        // Symplectic Euler integration
        w->vel[i] = vec2_add(w->vel[i], vec2_scale(w->gravity, dt));
        w->pos[i] = vec2_add(w->pos[i], vec2_scale(w->vel[i], dt));

        float r = w->radius[i];

        // Floor & ceiling bounce
        if (w->pos[i].y + r > w->bounds_height) {
            w->pos[i].y = w->bounds_height - r;
            w->vel[i].y *= -0.82f;
        } else if (w->pos[i].y - r < 0.0f) {
            w->pos[i].y = r;
            w->vel[i].y *= -0.82f;
        }

        // Left & right wall bounce
        if (w->pos[i].x + r > w->bounds_width) {
            w->pos[i].x = w->bounds_width - r;
            w->vel[i].x *= -0.82f;
        } else if (w->pos[i].x - r < 0.0f) {
            w->pos[i].x = r;
            w->vel[i].x *= -0.82f;
        }
    }
}
