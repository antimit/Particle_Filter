🌀 Particle Filter
A simple C++ implementation of a Particle Filter using SFML for real-time visualization. The program tracks a plane's position using particles and updates them based on noisy measurements.

📦 Requirements
C++ Compiler (g++)
SFML Library (sudo apt install libsfml-dev)
⚙️ Build
bash
Copy code
make
This compiles the project and creates myProgram executable.

🚀 Run
bash
Copy code
./myProgram
Controls
Close the window to exit.
🗑️ Clean Up
bash
Copy code
make clean   # Remove object files
make fclean  # Full cleanup, including executable
📂 Files
main.cpp: Entry point, handles SFML window.
ParticleFilter.cpp: Core algorithm.
Particle.h: Class definition.
🖼️ Preview
The window displays:

Green Line: Ground
Red Dots: Particles
Red Square: Plane
