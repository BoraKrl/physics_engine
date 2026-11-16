/*
    16-Nov-2026
    Bora Kirli
*/

#include "collision.h"

void collision_solve_particles(PhysicsWorld* w) {
    const float restitution = 0.75f;

    for (uint32_t i = 0; i < w->count; i++) {
        for (uint32_t j = i; j < w->count; j++) {
            Vec2 delta = vec2_sub(w->pos[j], w->pos[i]);
            float dist_sq = vec2_len_sq(delta);
            float min_dist = w->radius[i] + w->radius[j];

            if (dist_sq >= min_dist * min_dist) continue;

            float dist = sqrtf(dist_sq);
            Vec2 normal;

            if (dist > 0.0001f) {
                normal = vec2_scale(delta, 1.0f / dist);
            } else {
                normal = (Vec2){ 0.0f, -1.0f };
                dist = 0.0f;
            }

            // positional projection
            float overlap = min_dist - dist;
            Vec2 correction = vec2_scale(normal, overlap * 0.5f);
            w->pos[i] = vec2_sub(w->pos[i], correction);
            w->pos[j] = vec2_add(w->pos[j], correction);

            // impulse bounce resolution
            Vec2 rel_vel = vec2_sub(w->vel[j], w->vel[i]);
            float vel_along_normal = vec2_dot(rel_vel, normal);

            if (vel_along_normal > 0.0f) continue;

            float impulse_mag = -(1.0f + restitution) * vel_along_normal * 0.5f;
            Vec2 impulse = vec2_scale(normal, impulse_mag);
            
            w->vel[i] = vec2_sub(w->vel[i], impulse);
            w->vel[j] = vec2_add(w->vel[j], impulse);
        }
    }
}

void collision_solve_bounds(PhysicsWorld* w) {
    for (uint32_t i = 0; i < w->count; i++) {
        float r = w->radius[i];

        if (w->pos[i].y + r > w->bounds_height) {
            w->pos[i].y = w->bounds_height - r;
            w->vel[i].y *= -0.82f;
        } else if (w->pos[i].y - r < 0.0f) {
            w->pos[i].y = r;
            w->vel[i].y *= -0.82f;
        }

        if (w->pos[i].x + r > w->bounds_width) {
            w->pos[i].x = w->bounds_width - r;
            w->vel[i].x *= -0.82f;
        } else if (w->pos[i].x - r < 0.0f) {
            w->pos[i].x = r;
            w->vel[i].x *= -0.82f;
        }
    }
}
