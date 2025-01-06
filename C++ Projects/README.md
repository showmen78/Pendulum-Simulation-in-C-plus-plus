# Pendulum Simulation with Energy Graphs

This project simulates a pendulum's motion using simple physics principles and visualizes its potential energy, kinetic energy, and total energy over time through graphs. The simulation is implemented in C++ using the raylib graphics library.

---

## Features

- Realistic simulation of pendulum motion with damping.
- Graphical representation of potential energy, kinetic energy, and total energy.
- Adjustable parameters for experimentation with different pendulum setups.

---

## Physics Behind the Simulation

### Equations of Motion

1. **Angular Acceleration**:  
   angularAcc = -(gravity / length) * sin(angle)

2. **Angular Velocity Update**:  
   angularVel = angularVel + angularAcc

3. **Angle Update**:  
   angle = angle + angularVel

4. **Damping**:  
   angularVel = angularVel * 0.9999f

---

### Energy Calculations

1. **Potential Energy (PE)**:  
   height = length * (1.0f - cos(angle))  
   PE = gravity * height  
   (Assuming mass = 1)

2. **Kinetic Energy (KE)**:  
   velocity = length * angularVel  
   KE = 0.5f * velocity * velocity  

3. **Total Energy (TE)**:  
   TE = PE + KE  

---

## Parameters

The pendulum simulation uses the following parameters:

| Parameter       | Description                                               | Default Value |
|-----------------|-----------------------------------------------------------|---------------|
| `origin`        | The fixed point from which the pendulum hangs.            | Centered at (400, 100) |
| `length`        | The length of the pendulum rod in pixels.                 | 300.0         |
| `angle`         | The initial angle of the pendulum in radians.             | PI / 2 (90°)  |
| `angularVel`    | The initial angular velocity of the pendulum.             | 0.0           |
| `angularAcc`    | The initial angular acceleration of the pendulum.         | 0.0           |
| `bobRadius`     | The radius of the pendulum bob in pixels.                 | 20.0          |
| `gravity`       | The gravitational acceleration constant.                  | 0.5           |
| `damping_factor`| The damping factor applied to angular velocity.           | 0.0001        |

---

## Graph Representation

The simulation visualizes the following energy components:

- **Potential Energy** (Red): Represents the energy stored due to height.
- **Kinetic Energy** (Green): Represents the energy due to motion.
- **Total Energy** (Blue): The sum of potential and kinetic energy, indicating energy conservation.

Graphs are normalized for visualization purposes.

---

## Controls

- The simulation starts automatically when the application is launched.
- Close the simulation window to exit.

---

## Prerequisites

- **raylib library** installed on your system.
- A C++ compiler that supports C++11 or later.

### Installing raylib

Follow the official raylib installation guide for your platform:  
https://github.com/raysan5/raylib/wiki

---

## Compilation and Execution

1. Clone the repository or copy the source code.
2. Compile the code using the following command:

   g++ -o simple_pendulum.cpp -lraylib -lm

3. Run the executable:

   ./simple_pendulum

---


## License

This project is licensed under the MIT License.

---

## Acknowledgments

- raylib: Simple and easy-to-use library for videogame programming.
- Physics concepts for pendulum motion and energy calculation.
