#!/bin/bash

# Perform clang-format, clang-tidy, compile, and scan-build
find . -name '*.cpp' -o -name '*.hpp' | xargs clang-format -i
find . -name '*.cpp' -o -name '*.hpp' | xargs clang-tidy -p build
find . -name '*.cpp' | xargs clang++ -o mesh-ci-image
find . -name '*.cpp' | xargs scan-build clang++ -o mesh-ci-image
