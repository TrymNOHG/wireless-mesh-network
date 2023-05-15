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

## Installation

[Provide step-by-step instructions for installing and setting up your project. Include any prerequisites, software versions, or configuration steps.]

## Usage

[Provide instructions on how to use your solution. Describe the necessary inputs, expected outputs, and any specific usage guidelines or conventions.]

## Running Tests

[Explain how to run the tests included in your project. Provide any necessary commands or instructions for executing the test suite.]

## API Documentation

[If applicable, include a link to the API documentation or provide instructions on accessing the documentation if it's generated as part of the project.]
