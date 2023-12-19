cmake_minimum_required(VERSION 3.5)

project(Qt_cmake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup()

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(Qt_cmake
    main.cpp
    main.cpp mainwindow.cpp mainwindow.h qt_plateau.cpp qt_plateau.h qt_tirages.cpp qt_tirages.h vuepartie.h
    ../classes/carte.cpp
    ../classes/carte.h
    ../classes/Exception.h
    ../classes/jetons.cpp
    ../classes/jetons.h
    ../classes/jeu.cpp
    ../classes/jeu.h
    ../classes/joueur.cpp
    ../classes/joueur.h
    ../classes/pioche.cpp
    ../classes/pioche.h
    ../classes/plateau.cpp
    ../classes/plateau.h
    ../classes/privilege.cpp
    ../classes/privilege.h
    ../classes/sac.cpp
    ../classes/sac.h
    ../classes/tirage.cpp
    ../classes/tirage.h
    ../classes/json.cpp
    ../classes/json.h
    qt_jetons_main.h
    qt_jetons_main.cpp
    qt_labelclick.h
    qt_labelclick.cpp
    qt_vue_jeton.h
    qt_vue_carte.h
    qt_vue_carte.cpp
    qt_vue_jeton.cpp
    qt_cards_main.h
    qt_cards_main.cpp
    popup_text.h
    popup_text.cpp
    main.h
    qt_choicepopup.h
    qt_popup_yesno.h
    qt_popup_info.h
    qt_popup_tirageoupioche.h


)

include(GNUInstallDirs)


# Specify the C++ source files
set(SOURCES
    ../classes/carte.cpp
    ../classes/jetons.cpp
    ../classes/jeu.cpp
    ../classes/joueur.cpp
    ../classes/pioche.cpp
    ../classes/plateau.cpp
    ../classes/privilege.cpp
    ../classes/sac.cpp
    ../classes/tirage.cpp
    ../main.cpp
    main_old.cpp
    mainwindow.cpp
    plateau.cpp
    tirages.cpp
)

# Specify the header files
set(HEADERS
    ../classes/Exception.h
    ../classes/carte.h
    ../classes/jetons.h
    ../classes/jeu.h
    ../classes/joueur.h
    ../classes/pioche.h
    ../classes/plateau.h
    ../classes/privilege.h
    ../classes/sac.h
    ../classes/tirage.h
    ../main.h
    plateau.h
    tirages.h
)

target_link_libraries(Qt_cmake PRIVATE Qt6::Widgets Qt6::Core)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(Qt_cmake PRIVATE nlohmann_json::nlohmann_json)

