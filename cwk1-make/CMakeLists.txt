cmake_minimum_required(VERSION 3.21)
project(cwk1 C)

set(CMAKE_C_STANDARD 99)
    
add_executable(cwk1 main.c menu.c books.c user.c librarian.c users.txt books.txt)
