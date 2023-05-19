cmake_minimum_required(VERSION 3.22)
project(wireless_mesh_network)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(RELATIVE_PATH CMAKE_BUILD_DIR "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}")
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/compile_commands.json")
    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_BUILD_DIR}/compile_commands.json
            ${CMAKE_SOURCE_DIR}/compile_commands.json
            )
endif()

find_package(Boost 1.74.0 REQUIRED COMPONENTS regex date_time system filesystem thread graph program_options)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()
find_package(Boost REQUIRED COMPONENTS regex date_time system filesystem thread graph program_options)
add_executable(wireless_mesh_network main.cpp PriorityQueue.cpp)
target_link_libraries(wireless_mesh_network Boost::regex Boost::date_time Boost::system Boost::filesystem Boost::thread Boost::graph Boost::program_options)
