cmake_minimum_required(VERSION 3.0)

project(project_programmation
        VERSION 1.0
        DESCRIPTION "Projet C++"
        LANGUAGES CXX)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_image)
