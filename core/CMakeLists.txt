cmake_minimum_required(VERSION 3.23)

add_library(core)

add_subdirectory(shaders)
add_subdirectory(textures)

target_compile_definitions(core 
  PUBLIC 
  SHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/shaders"
  TEXTURE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/textures"
)

target_sources(core
  PRIVATE
    game.cc
    resource_manager.cc
    shader.cc
    sprite_renderer.cc
    texture.cc
)

target_link_libraries(core
  PRIVATE
    glm::glm 
    glad
    stbi
)