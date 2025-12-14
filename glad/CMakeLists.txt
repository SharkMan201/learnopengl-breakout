cmake_minimum_required(VERSION 3.23)

project(glad)

add_library(glad)

target_include_directories(glad PUBLIC include)

target_sources(glad
    PRIVATE
        src/glad.c
)
