# Use a base image with the necessary dependencies installed
FROM ubuntu:latest

# Install Clang, g++, python3, python3-pip, clang tools, and clang format
RUN apt-get update && apt-get install -y \
    clang \
    clang-tidy \
    clang-tools \
    clang-format \
    g++ \
    python3 \
    python3-pip

# Set up a workspace directory
WORKDIR /workspace

# Copy your project files into the container
COPY . .

# Set the default command to run Clang-Format, Clang-Tidy, and Clang Static Analyzer on the project
CMD ["bash", "-c", "clang-format -i $(find . -name '*.cpp' -o -name '*.hpp') && \
                      clang-tidy -p build -- $(find . -name '*.cpp' -o -name '*.hpp') && \
                      clang++ -o myapp $(find . -name '*.cpp') && \
                      scan-build clang++ -o myapp $(find . -name '*.cpp')"]
