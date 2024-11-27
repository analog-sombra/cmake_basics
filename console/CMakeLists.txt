cmake_minimum_required(VERSION 3.31.1)
project(console)

set(ProjectType STATIC) # Options are SHARED or STATIC

set (SourceFiles
    src/city.c
    src/name.c
)

include_directories(include)
add_library(${PROJECT_NAME} ${ProjectType} ${SourceFiles})