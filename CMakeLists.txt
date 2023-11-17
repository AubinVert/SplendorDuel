cmake_minimum_required(VERSION 3.13)  # CMake version check

project(lo21-splendor-duel)               # Create project "simple_example"

set(CMAKE_CXX_STANDARD 17)            # Enable c++14 standard

set(SOURCE_FILES
        main.cpp
        classes/carte.cpp
        classes/jetons.cpp
        classes/jeu.cpp
        classes/joueur.cpp
        classes/plateau.cpp
        classes/privilege.cpp
        classes/tirage.cpp
        classes/pioche.cpp
        classes/sac.cpp
)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(lo21-splendor-duel ${SOURCE_FILES})

target_link_libraries(lo21-splendor-duel PRIVATE nlohmann_json::nlohmann_json)
