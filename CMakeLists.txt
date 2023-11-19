cmake_minimum_required(VERSION 3.13)  # CMake version check

project(lo21-splendor-duel)               # Create project "simple_example"

set(CMAKE_CXX_STANDARD 17)            # Enable c++14 standard

# Add main.cpp file of the project root directory as a source file
set(SOURCE_FILES
        main.cpp
        classes/carte.cpp
        classes/pioche.cpp
        classes/tirage.cpp
)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(lo21-splendor-duel ${SOURCE_FILES})

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(lo21-splendor-duel PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(lo21-splendor-duel PRIVATE "C:/Users/ce pc/.vcpkg-clion/vcpkg/packages/nlohmann-json_x64-windows/include/nlohmann")
