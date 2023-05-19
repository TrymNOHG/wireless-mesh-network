#!/bin/bash

#Run Cmake and generate compile_commands.json
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .

#ls -la /workspace

# Perform clang-tidy on main.cpp
clang-tidy main.cpp --

# Perform clang-format
find . -name '*.cpp' -o -name '*.hpp' | xargs clang-format -i

# Run clang-tidy again with a build path
find . -name '*.cpp' -o -name '*.hpp' | xargs clang-tidy -p .

# Compile with clang++
clang++ -o mesh-ci-image main.cpp PriorityQueue.cpp

# Run scan-build
scan-build clang++ -o mesh-ci-image main.cpp PriorityQueue.cpp

# If you want to run the program as a script, it needs to take in arguments in main.
# Build the project
#g++ -std=c++17 main.cpp PriorityQueue.cpp -o main
#
## Run the main program
#./main 5 10