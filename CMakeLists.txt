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

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(lo21-splendor-duel ${SOURCE_FILES})

target_link_libraries(lo21-splendor-duel PRIVATE nlohmann_json::nlohmann_json)

