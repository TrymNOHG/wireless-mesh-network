# Mobile Wireless Mesh Network

## CI/CD Solution

**Description**: 

`Clang-format` was used in order to maintain a uniform programming convention. Through this standardized formatting, the code is more readable and consistent.

`Clang-tidy` was used to statically analyze the code for performance issues and bugs.

`Clang Static Analyzer` was used for a similar purpose of statically analyzing the code, but with more of a focus on bug detection and security vulnerabilities. It, therefore, helps to identify memory leaks and null pointer deferencing.

These were all run through a docker file.

**Last Run**: [Insert link to the latest CI/CD run or build status badge]

## Problem Introduction

This repository contains the work done in accordance with the optional project for the IDATT2104 Network Programming course at NTNU. The assignment focused on the various applications of **Mobile Wireless Mesh Networks**.

In order to accomplish something tangible within the project period, this project specifically focuses on addressing the decisive communication challenges encountered during search and rescue missions, particularly with scenarios similar to the Tham Luang cave incident. Through this exploration of mobile wireless mesh networks, we aim to challenge others to further explore possible solutions and to provide a potential solution to strengthen coordination and communication in life-threatening situations.  

Reliable and efficient communication during rescue missions are vital for recovering people, coordinating efforts, and guaranteeing overall safety of. Previously, problems with communication have caused hardships and risks to human lives.

One of the motivations for narrowing the project to rescue missions came from such an instance. In 2018, a youth soccer team was trapped inside a cave due to flooding. During the Tham Luang cave rescue, law enforcements and volunteers labored to first locate and second establish communications with the team. The poor conditions of darkness and murky water caused great difficulties. The problems faced with setting up communication efficiently exacerbated the risks, especially when the well-being of the soccer team was unknown. Although the rescue was successful, it can be beneficial to look at the operation critically in order to reduce the risk if a similar scenario occurs again.

By leveraging the intrinsic properties of mobile wireless mesh networks, we hope to propose a mode for setting up reliable and efficient communication. As mobile wireless mesh networks are decentralized, they are independent of existing infrastructure and as such gain a degree of freedom and flexibility. Furthermore, this flexibility lends itself to a few special traits: self-configuration and self-healing. Since each node in a wireless mesh network is connected to other nodes, there is less of an effect when a node fails. Instead, the other nodes in the mesh can readjust to avoid the failure.

This repository contains the work done by Leon Egeberg Hesthaug and Trym Hamer Gudvangen in an attempt to simulate the possibility of using a mobile wireless mesh network for rescue missions such as the cave incident. Specifically, the repository demonstrates
an implementation of the dynamic source routing protocol when used on a weighted graph.

Furthermore, this project specifically demonstrates an implementation of the dynamic source routing (DRS) protocol when used on a weighted graph. DRS is an implementation of a MANET. 


The hope of this project is to contribute to the general public’s interest in Mobile Wireless Mesh Networks. Through this solution, we hope more research is done leading to more efficient relief when it comes to critical situations such as rescue missions.


## Considerations

With the background knowledge from Algorithms and Datastructures, our minds instantly went to "How can we leverage a shortest-path algorithm such as Dijkstra's, Bellman-ford, or A* search algorithm?". 
In considerations: discuss why we chose DRS over AODV.


[Discuss the factors and considerations that influenced your choice of solution or approach. Highlight any specific requirements, constraints, or trade-offs that were taken into account.]

## Implementation Details

[Provide an overview of the implementation details and functionality of your solution. Explain the key components, algorithms, or methodologies employed.]

## Future Work

[Discuss potential future developments, improvements, or enhancements for your project. Identify weaknesses or faults in the current implementation that could be addressed in future iterations.]

## External Dependencies

[Describe any external dependencies used in your project. Include a brief description of each dependency and how it was utilized.]

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

   **Option 2: Docker**

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

[Provide instructions on how to use your solution. Describe the necessary inputs, expected outputs, and any specific usage guidelines or conventions.]

## Running Tests

[Explain how to run the tests included in your project. Provide any necessary commands or instructions for executing the test suite.]

## API Documentation

[If applicable, include a link to the API documentation or provide instructions on accessing the documentation if it's generated as part of the project.]
