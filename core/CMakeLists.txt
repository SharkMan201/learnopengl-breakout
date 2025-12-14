add_library(core)

add_subdirectory(shaders)
add_subdirectory(textures)

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