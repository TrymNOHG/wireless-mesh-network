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
    python3-pip \
    libboost-all-dev

# Set up a workspace directory
WORKDIR /workspace

# Copy your project files into the container
COPY . .

# Copy the script into the container
COPY script.sh .

# Make the script executable
RUN chmod +x script.sh

# Set the default command to run the script
CMD ["./script.sh"]