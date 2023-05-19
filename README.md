# Mobile Wireless Mesh Network

## CI/CD Solution

**Description**:

`Clang-format` was used in order to maintain a uniform programming convention. Through this standardized formatting, the code is more readable and consistent.

`Clang-tidy` was used to statically analyze the code for performance issues and bugs.

`Clang Static Analyzer` was used for a similar purpose of statically analyzing the code, but with more of a focus on bug detection and security vulnerabilities. It, therefore, helps to identify memory leaks and null pointer deferencing.

These were all run through a docker file.

**Last Run**: 

Link to the last pipeline ran:

https://github.com/TrymNOHG/wireless-mesh-network/actions/runs/5025551063

Link to all workflows:

https://github.com/TrymNOHG/wireless-mesh-network/actions/workflows/main.yml

## Problem Introduction

This repository contains the work done in accordance with the optional project for the IDATT2104 Network Programming course at NTNU. The assignment focused on the various applications of **Mobile Wireless Mesh Networks**.

In order to accomplish something tangible within the project period, this project specifically focuses on addressing the decisive communication challenges encountered during search and rescue missions, particularly situations where terrain and weather prohibit access. Through this exploration of mobile wireless mesh networks, we aim to challenge others to further explore possible solutions and to provide a potential solution to strengthen coordination and communication in life-threatening situations.

Reliable and efficient communication during rescue missions are vital for recovering people, coordinating efforts, and guaranteeing overall safety of. Previously, problems with communication have caused hardships and risks to human lives.

By leveraging the intrinsic properties of mobile wireless mesh networks, we hope to propose a mode for setting up reliable and efficient communication. As mobile wireless mesh networks are decentralized, they are independent of existing infrastructure and as such gain a degree of freedom and flexibility. Furthermore, this flexibility lends itself to a few special traits: self-configuration and self-healing. Since each node in a wireless mesh network is connected to other nodes, there is less of an effect when a node fails. Instead, the other nodes in the mesh can readjust to avoid the failure.

This repository contains the work done by Leon Egeberg Hesthaug and Trym Hamer Gudvangen in an attempt to simulate the possibility of using a mobile wireless mesh network for rescue missions such as the cave incident. Specifically, the repository demonstrates and simulates an optimal drone formation for maximum area coverage with regards to number of drones and risk of drone failure. This could be used in a search and rescue operation where search area is expansive and drone coverage is therefore paramount. Connectiveness between drones in the mesh can also be adjusted to account for increased risk factors such as weather and other sources of drone loss.


The hope of this project is to contribute to the general public’s interest in Mobile Wireless Mesh Networks. Through this solution, we hope more research is done leading to more efficient relief when it comes to critical situations such as rescue missions.


## Considerations
There were two main considerations when developing this simulation.

1.)	The first one was how to create a graph so that each drone had the required number of connections specified by the user but not to many such as to limit the drone coverage.

2.)	The second one revolved around optimally placing the nodes in the graph so that the area covered was maximized. This proved harder than anticipated since this problem can be reduced to the facility location problem and further to the independent set problem which is NP-hard. As an exact solution to this would be very time consuming for the program, we opted for approximations which would for all intents and purposes not be a significant downgrade compared to the exact solution.

How these were solved technically in the program is outlined in the Implementation Details section.

## Implementation Details

The program implements the Boost graph library as well as Graphviz. These are further outlined in the External Dependencies section.

A graph represents drones as verticies and edges as connections.

Consideration 1:
To create a graph with only the necessary edges the program starts by creating a complete graph with n nodes. By using a priority queue it keeps track of each vertex and the number of edges connected to it. The vertices at the front of this queue then lose one edge and are put back in the queue. This repeats until all vertices have lost the previously computed number of edges based on the connectiveness percentage required by the user. This leaves a graph were edges are equally distributed and each vertex only has the necessary amount of connections.

Consideration 2:
Since computing an exact solution to this problem cannot be done in polynomial time, it is therefore best to use a algorithm that approximates the optimal solution. This program uses Force-directed graph drawing
and specifically Fruchterman–Reingold algorithm. The algorithm relies on a physical model. Points on a plane are used to depict nodes, and they possess electrical charges that create repulsive forces when interacting with each other. These points are connected by edges, which mimic the effect of springs, attracting neighboring nodes. Through successive iterations, the model calculates the resulting forces exerted on the nodes and attempts to bring them closer to a balanced state, where all forces cancel out, ensuring the nodes' positions remain steady.

What this in effect does for our graph is that it ensures that connected vertices stay close and any single connection(edge) is never to long for the drones connection range. The drone layout can therefore spread out more while still maintaining connection to each other.

It should also be mentioned that edge length is not show since this only depends on the connection range of the individual drone. This does not change the layout of the graph however and it can be scaled up or down for any connection range.


## Future Work

In the future some possible alterations might come to the two main algorithms used for consideration 1 and 2. There might be other algorithms not yet considered that provide better results and optimization.


## External Dependencies

Boost graph library (https://www.boost.org/doc/libs/1_80_0/libs/graph/doc/index.html): Large graph library used for in this program for representing and manipulating graphs. Removes the need to write own graph framework.

Graphviz (https://graphviz.org/): Graph visualization library. By converting our graph to a .dot file graphviz can vizulise it as a png with the correct layout. Here sfdp(Scalable Force-Directed Placement) is used for vertex placement.


# Installation Guide

This guide will walk you through the steps required to set up and install the wireless_mesh_network project on your computer.

## Prerequisites

Before you begin the installation, please ensure you have the following software installed:

- Boost Library (version 1.74.0 or above)
- Graphviz
- Docker

These can be installed using your package manager.

For MacOS users with Homebrew installed:

`brew install boost`

`brew install graphviz`

`brew install --cask docker`

For Ubuntu/Debian Linux users:

`sudo apt-get install libboost-all-dev`

`sudo apt-get install graphviz`

`sudo apt-get install docker.io`

For Fedora Linux users:

`sudo dnf install boost-devel`

`sudo dnf install graphviz`

`sudo dnf install docker`

Ensure that Docker is running on your system after installation. For MacOS and Windows users, you may have to start it manually using the Docker Desktop application. For Linux users, you can start it with the following command:

`sudo systemctl start docker`

Also, remember to add your user to the docker group to avoid having to use 'sudo' every time you run a Docker command:

`sudo usermod -aG docker $USER`

Remember to log out and back in for this to take effect.


## Installation Steps

1. **Clone the repository**

   Clone the wireless_mesh_network repository to your local machine.

   git clone [https://github.com/your-username/wireless_mesh_network.git](https://github.com/TrymNOHG/wireless-mesh-network.git)

2. **Navigate to the project directory**


Change to the `wireless_mesh_network` directory.

`cd wireless_mesh_network`


3. **Build the Docker Image**

Build the Docker image using the provided Dockerfile.

`docker build -t mesh-ci-image .`


4. **Running the Application**

   You have two options to run the application: using the built-in IDE or running it with Docker.

   **Option 1: Built-in IDE (Preferred)**

   The preferred method is to run the application using the built-in IDE. Follow these steps:

    1. Open the wireless_mesh_network project in your preferred IDE.
    2. Configure the necessary project settings and dependencies as per the IDE's guidelines.
    3. Build and run the application from within the IDE.

   By utilizing the built-in IDE, you can take advantage of its integrated development environment and easily manage the project.

   **Option 2: Docker (Coming Soon)**

   If you prefer to use Docker for running the application, follow these steps:

    1. Ensure Docker is installed on your system.
    2. Open a terminal or command prompt.
    3. Navigate to the root directory of the project (`wireless_mesh_network`).
    4. Execute the following command:

       ```
       docker run --rm -v "$(pwd):/workspace" mesh-ci-image
       ```

       This command runs the Docker image you just built and mounts the current directory (`wireless_mesh_network`) inside the container at the `/workspace` location.

   Running the application with Docker provides an alternative option for execution, enabling a consistent and isolated runtime environment.

   Congratulations! You have successfully installed and set up the wireless_mesh_network project. Choose the option that best suits your requirements and proceed with running the application accordingly.


## Troubleshooting

If you encounter any issues during the installation, please check the following:

- Ensure that you have all the required software (Boost, Graphviz, and Docker) installed on your machine.
- Ensure that Docker is running.
- If you get a "Could not find boost!" error, make sure that the Boost library is installed and the version is 1.74.0 or higher.

If you still encounter issues, please open an issue on the GitHub repository.


## Usage

When running the program you will be prompted to input how many drones to use.
After this you will be asked to “Enter the percentage of other drones any given drone has connection to”.

In this case a value of 100 will mean that every single drone has a direct connection to every other drone. Usually this level of failsafe is not necessary and it limits drone spread greatly but this is up to the user to decide depending on their risk tolerance.
