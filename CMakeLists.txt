cmake_minimum_required(VERSION 3.16)

project(TicTacToe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(TicTacToe
    main.cpp
)

target_link_libraries(TicTacToe
    PRIVATE Qt6::Widgets
)