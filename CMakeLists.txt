cmake_minimum_required(VERSION 3.22)

project(AVLTree)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(AVLTree
        src/main.cpp
        src/AVL.cpp
        src/AVL.h
)