cmake_minimum_required(VERSION 3.0)

# General informations about the project
project(project_programmation
        VERSION 1.0
        DESCRIPTION "Projet C++"
        LANGUAGES CXX)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
               PRIVATE
               src/plateform.cpp
               src/plateform.h
               main.cpp)

target_include_directories(${PROJECT_NAME}
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR})

#link sdl2
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)