#include "raylib.h"
#include <cmath>
#include <vector>

#define BUFFER_SIZE 500 // Number of points in the graph buffer

// Pendulum structure to manage properties
struct Pendulum {
    Vector2 origin;      // Origin point of the pendulum
    float length;        // Length of the pendulum rod
    float angle;         // Current angle of the pendulum
    float angularVel;    // Angular velocity
    float angularAcc;    // Angular acceleration
    float bobRadius;     // Radius of the pendulum bob
    float gravity;       // Gravitational constant

    // Function to update the pendulum state with time step
    void Update() {
        angularAcc = -(gravity / length) * sin(angle); // Angular acceleration
        angularVel += angularAcc; // Angular velocity
        angle += angularVel;     // Angle

        angularVel *= 0.9999f; // Damping (air resistance)
    }

    // Calculate Potential Energy
    float CalculatePotentialEnergy() const {
        float height = length * (1.0f - cos(angle)); // Height from equilibrium
        return gravity * height; // Assuming mass = 1
    }

    // Calculate Kinetic Energy
    float CalculateKineticEnergy() const {
        float velocity = length * angularVel; // Linear velocity of the bob
        return 0.5f * velocity * velocity;    // KE = 0.5 * m * v^2 (mass = 1)
    }

    // Function to get the position of the pendulum bob
    Vector2 GetBobPosition() const {
        return { origin.x + length * sin(angle), origin.y + length * cos(angle) };
    }

    // Function to draw the pendulum
    void Draw() const {
        Vector2 bobPosition = GetBobPosition();
        DrawLineV(origin, bobPosition, DARKGRAY);  // Draw the rod
        DrawCircleV(bobPosition, bobRadius, RED); // Draw the bob
    }
};

// Function to draw energy graphs
void DrawGraph(const std::vector<float>& buffer, int x, int y, int width, int height, Color color) {
    int size = buffer.size();
    for (int i = 1; i < size; i++) {
        float x1 = x + (i - 1) * (width / (float)BUFFER_SIZE);
        float y1 = y + height - (buffer[i - 1] * height); // Scale to graph height
        float x2 = x + i * (width / (float)BUFFER_SIZE);
        float y2 = y + height - (buffer[i] * height);
        DrawLine((int)x1, (int)y1, (int)x2, (int)y2, color);
    }
}

int main() {
    // Screen dimensions
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Pendulum Simulation with Energy Graphs");

    Pendulum pendulum = {
        {screenWidth / 2.0f, 100.0f}, // Origin point
        300.0f,                       // Length of the rod
        PI / 2,                       // Initial angle (45 degrees)
        0.0f,                         // Initial angular velocity
        0.0f,                         // Initial angular acceleration
        20.0f,                        // Bob radius
        0.5f                          // Gravitational constant
    };

    SetTargetFPS(60);

    // Buffers for energy values
    std::vector<float> potentialEnergy(BUFFER_SIZE, 0.0f);
    std::vector<float> kineticEnergy(BUFFER_SIZE, 0.0f);
    std::vector<float> totalEnergy(BUFFER_SIZE, 0.0f);



    while (!WindowShouldClose()) {
  

        // Update pendulum state
        pendulum.Update();

        // Calculate energies
        float pe = pendulum.CalculatePotentialEnergy();
        float ke = pendulum.CalculateKineticEnergy();
        float te = pe + ke;

        // Update energy buffers
        potentialEnergy.push_back(pe / 50.0f); // Normalize for graph
        kineticEnergy.push_back(ke / 50.0f);
        totalEnergy.push_back(te / 50.0f);
        if (potentialEnergy.size() > BUFFER_SIZE) potentialEnergy.erase(potentialEnergy.begin());
        if (kineticEnergy.size() > BUFFER_SIZE) kineticEnergy.erase(kineticEnergy.begin());
        if (totalEnergy.size() > BUFFER_SIZE) totalEnergy.erase(totalEnergy.begin());

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the pendulum
        pendulum.Draw();

        // Draw energy graphs
        DrawText("Potential Energy (RED)", 10, 420, 20, RED);
        DrawText("Kinetic Energy (GREEN)", 10, 450, 20, GREEN);
        DrawText("Total Energy (BLUE)", 10, 480, 20, BLUE);

        DrawGraph(potentialEnergy, 50, 500, 700, 80, RED);
        DrawGraph(kineticEnergy, 50, 500, 700, 80, GREEN);
        DrawGraph(totalEnergy, 50, 500, 700, 80, BLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
