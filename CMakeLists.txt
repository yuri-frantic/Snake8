cmake_minimum_required(VERSION 3.11)

project(SnakeGame)

set(CMAKE_CXX_STANDARD 11)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(SnakeGame main.cpp snake.cpp)
target_link_libraries(SnakeGame Qt5::Core Qt5::Gui Qt5::Widgets)

set_target_properties(SnakeGame PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
