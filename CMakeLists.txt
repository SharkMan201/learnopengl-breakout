cmake_minimum_required(VERSION 3.23)

project(breakout)

add_executable(breakout)

target_sources(breakout
    PRIVATE
        main.cc
)

# external deps
find_package(glfw3 3.4 REQUIRED)
find_package(glm 1.0.2 REQUIRED)
add_subdirectory(glad)
add_subdirectory(stbi)

# internal deps
add_subdirectory(core)

target_compile_definitions(breakout
    PRIVATE
        GLFW_INCLUDE_NONE
)

target_link_libraries(breakout
    PRIVATE
        glad
        glfw
        glm::glm
        core
)
