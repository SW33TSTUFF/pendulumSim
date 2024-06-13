#include <iostream>
#include <raylib.h>
#include <cmath>
#include <deque>

using namespace std;

float mew = 0.8f; // Damping coefficient

// Struct to store trail points
struct TrailPoint {
    Vector2 position;
    float timestamp;
};

// Pendulum class definition
struct Pendulum {
    float length;
    float mass;
    float angle;
    float angularVelocity;
    float angularAcceleration;
    Color bobColor;
    Vector2 origin;
    Vector2 bob;
    deque<TrailPoint> trail; // To store the trail positions
    float trailLifetime;

    Pendulum(float l, float m, float a, Vector2 o, float trailLife, Color Coloz) : length(l), mass(m), angle(a), origin(o), trailLifetime(trailLife), bobColor(Coloz) {
        angularVelocity = 0;
        angularAcceleration = 0;
        bob = { origin.x + length * sin(angle), origin.y + length * cos(angle) };
    }

    void update(float gravity, float deltaTime) {
        angularAcceleration = (-gravity / length) * sin(angle);
        angularVelocity += angularAcceleration * deltaTime;
        
        // Apply damping (friction)
        // angularVelocity *= (1 - mew * deltaTime);
        
        angle += angularVelocity * deltaTime;

        bob = { origin.x + length * sin(angle), origin.y + length * cos(angle) };

        // Add current bob position to trail
        trail.push_back({ bob, GetTime() });

        // Remove old trail points
        while (!trail.empty() && GetTime() - trail.front().timestamp > trailLifetime) {
            trail.pop_front();
        }
    }

    void draw() {
        // Draw the trail
        for (const auto& point : trail) {
            double age = GetTime() - point.timestamp;
            float alpha = 1.0f - age / trailLifetime;
            Color color = Fade(bobColor, alpha);
            DrawCircleV(point.position, mass * 0.1f, color); // Slightly smaller for the trail
        }

        // Draw the pendulum
        // DrawLineV(origin, bob, BLACK);
        // DrawCircleV(bob, mass, BLACK);
    }
};

int main() {
    const int screenWidth = 800;
    const int screenHeight = 800;

    cout << "Hello World" << endl;

    InitWindow(screenWidth, screenHeight, "Pendulum");
    // SetTargetFPS(60);

    Vector2 origin = { screenWidth / 2, screenHeight / 4 };
    float trailLifetime = 0.7f; // Trail will last for 2 seconds
    Pendulum pendulum1(200, 10, PI / 4, origin, trailLifetime, RED);
    Pendulum pendulum2(200, 10, PI / 4 + 0.1, origin, trailLifetime, ORANGE);
    Pendulum pendulum3(200, 10, PI / 4 + 0.2, origin, trailLifetime, YELLOW);
    Pendulum pendulum4(200, 10, PI / 4 + 0.3, origin, trailLifetime, GREEN);
    Pendulum pendulum5(200, 10, PI / 4 + 0.4, origin, trailLifetime, BLUE);
    Pendulum pendulum6(200, 10, PI / 4 + 0.5, origin, trailLifetime, PURPLE);
    Pendulum pendulum7(200, 10, PI / 4 + 0.6, origin, trailLifetime, VIOLET);
    const float gravity = 20.81f;
    const float timeStep = 1.0f / 60.0f; // Fixed time step for physics update


    float accumulator = 0.0f;
    double currentTime = GetTime();

    while (!WindowShouldClose()) {
        double newTime = GetTime();
        float frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;

        // Update physics with fixed time step
        while (accumulator >= timeStep) {
            pendulum1.update(gravity, timeStep);
            pendulum2.update(gravity, timeStep);
            pendulum3.update(gravity, timeStep);
            pendulum4.update(gravity, timeStep);
            pendulum5.update(gravity, timeStep);
            pendulum6.update(gravity, timeStep);
            pendulum7.update(gravity, timeStep);
            accumulator -= timeStep;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        pendulum1.draw();
        pendulum2.draw();
        pendulum3.draw();
        pendulum4.draw();
        pendulum5.draw();
        pendulum6.draw();
        pendulum7.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
