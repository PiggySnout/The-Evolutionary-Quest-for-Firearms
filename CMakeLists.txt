cmake_minimum_required(VERSION 3.22)
project(GameJam C CXX)

set(CMAKE_CXX_STANDARD 20)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

add_subdirectory(libs/raylib EXCLUDE_FROM_ALL)

add_executable(${PROJECT_NAME} #WIN32
    src/main.cpp
    src/Player.cpp
    src/ui.cpp
    src/Button.cpp
    src/Game.cpp
    src/Bullet.cpp
    src/Camera.cpp
    src/Weapon.cpp
    src/Npc.cpp
    src/Level.cpp
    src/MainMenu.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_compile_definitions(${PROJECT_NAME} PUBLIC DATA_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/data/")
target_compile_definitions(${PROJECT_NAME} PUBLIC SOUND_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/sound/")
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/textures/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets/") # Set the asset path macro in release mode
target_include_directories(GameJam
    SYSTEM PRIVATE
    ${raylib_SOURCE_DIR}/src
)