cmake_minimum_required(VERSION 3.10)

project(SpaceGame)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(SOURCES
    main.cpp
    scr/player.cpp
    scr/renderer.cpp
    scr/asteroid.cpp
    scr/math.cpp
    scr/menu.cpp
    scr/bullet.cpp
    scr/game.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf)


#
# For game goes brrrrrrrrrrrrrr
#
# do cmake -DCMAKE_BUILD_TYPE=Release
#