#include "raylib.h"
#include "physics.h"

int main(void) {
    const int width = 900;
    const int height = 650;

    InitWindow(width, height, "Unified C Physics Engine");
    SetTargetFPS(60);

    PhysicsWorld world;
    physics_init(&world, (float)width, (float)height);
    physics_spawn(&world, (Vec2){ 450.0f, 100.0f }, (Vec2){ 160.0f, 0.0f }, 12.0f);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if (dt > 0.033f) dt = 0.033f; // Prevent huge jumps if window is dragged

        // Hold left mouse button to spawn particles
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 m = GetMousePosition();
            physics_spawn(&world, (Vec2){ m.x, m.y }, (Vec2){ 0.0f, 0.0f }, 8.0f);
        }

        physics_step(&world, dt);

        BeginDrawing();
        ClearBackground((Color){ 16, 18, 24, 255 });

        for (uint32_t i = 0; i < world.count; i++) {
            DrawCircle((int)world.pos[i].x, (int)world.pos[i].y, world.radius[i], SKYBLUE);
        }

        DrawFPS(10, 10);
        DrawText(TextFormat("Particles: %u (Hold Left Click to Spawn)", world.count), 10, 35, 18, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
