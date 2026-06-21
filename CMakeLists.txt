cmake_minimum_required(VERSION 3.20)
project(Pong)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(pong
    src/main.cpp
    src/ball.cpp
    src/paddle.cpp
)

target_link_libraries(pong PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)