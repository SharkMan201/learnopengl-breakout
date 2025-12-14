cmake_minimum_required(VERSION 3.23)

add_library(glad)

target_include_directories(glad PUBLIC include)

target_sources(glad
    PRIVATE
        src/glad.c
)
