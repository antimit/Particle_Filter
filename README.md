Particle Filter
Overview
The Particle Filter is a probabilistic algorithm used for estimating the state of a system that changes over time. In this implementation, a particle filter is used to track the position of a plane in a 2D environment based on noisy measurements. The particles represent possible positions of the plane, and their weights are updated based on the likelihood of each position.

This program visualizes the particle filter in action using SFML, a graphics library for C++. It simulates the movement of a plane and updates particle positions and weights accordingly.

Requirements
Ensure you have the following:

g++ (C++ compiler)
SFML library (for graphics and window handling)
Install SFML if needed:

bash
Copy code
sudo apt-get install libsfml-dev
Compilation
To compile the program, use the provided Makefile. Run the following command:

bash
Copy code
make
This will generate an executable named myProgram in the current directory.

Launching
Run the program using:

bash
Copy code
./myProgram
The program opens a window visualizing:

The ground (green line)
The particles (red dots)
The plane (red square)
The particles update based on the plane's movement and measurement updates.

Cleaning Up
To remove the compiled files, use:

bash
Copy code
make clean
For a full cleanup, including the executable:

bash
Copy code
make fclean
Files
main.cpp: The main application loop and SFML window setup.
ParticleFilter.cpp: Implementation of the Particle Filter algorithm.
Particle.h: Header file defining the Particle Filter class.
Controls
Close the window to exit the program.
