cmake_minimum_required(VERSION 3.31)
project(game)
set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")
set(DCMAKE_BUILD_TYPE Release)
add_definitions(-DSFML_STATIC)

include_directories(SFML/include)
link_directories(SFML/lib)
add_executable(game main.cpp)

target_link_libraries(game PRIVATE sfml-graphics-s sfml-window-s sfml-system-s sfml-audio-s opengl32 winmm gdi32 freetype)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})