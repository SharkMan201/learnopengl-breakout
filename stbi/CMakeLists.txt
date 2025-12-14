cmake_minimum_required(VERSION 3.23)

project(stbi)

add_library(stbi INTERFACE)

target_compile_definitions(stbi
    INTERFACE
        STB_IMAGE_IMPLEMENTATION
)

target_include_directories(stbi INTERFACE include)