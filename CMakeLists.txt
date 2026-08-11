cmake_minimum_required(VERSION 3.22)
project(GameJam C CXX)

set(CMAKE_CXX_STANDARD 20)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

add_subdirectory(libs/raylib EXCLUDE_FROM_ALL)
if (APPLE)
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE
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
    set_source_files_properties(assets PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources"
    )
    target_sources(${PROJECT_NAME} PRIVATE assets)

elseif(WIN32)
    add_executable(${PROJECT_NAME} WIN32
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
else()
    add_executable(${PROJECT_NAME}
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
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

target_include_directories(GameJam
    SYSTEM PRIVATE
    ${raylib_SOURCE_DIR}/src
)
