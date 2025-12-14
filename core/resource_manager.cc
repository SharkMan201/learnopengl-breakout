#include "resource_manager.h"
#include <glad/glad.h>
#include <stb_image.h>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include "shader.h"
#include "texture.h"

namespace core {
std::map<std::string, std::unique_ptr<Shader>> ResourceManager::shaders;
std::map<std::string, std::unique_ptr<Texture2D>> ResourceManager::textures;

Shader* ResourceManager::LoadShader(const char* v_shader_file,
                                    const char* f_shader_file,
                                    const char* g_shader_file,
                                    std::string name) {
  shaders[name] =
      LoadShaderFromFile(v_shader_file, f_shader_file, g_shader_file);

  return shaders[name].get();
}

Shader* ResourceManager::GetShader(std::string name) {
  return shaders[name].get();
}

Texture2D* ResourceManager::LoadTexture(const char* file,
                                        bool alpha,
                                        std::string name) {
  textures[name] = LoadTextureFromFile(file, alpha);
  return textures[name].get();
}

Texture2D* ResourceManager::GetTexture(std::string name) {
  return textures[name].get();
}

void ResourceManager::Clear() {
  for (auto& iter : shaders) {
    glDeleteProgram(iter.second->id);
  }

  for (auto& iter : textures) {
    glDeleteTextures(1, &iter.second->id);
  }
}

std::unique_ptr<Shader> ResourceManager::LoadShaderFromFile(
    const char* v_shader_file,
    const char* f_shader_file,
    const char* g_shader_file) {
  std::string vertex_code;
  std::string fragment_code;
  std::string geometry_code;

  try {
    std::ifstream vertex_shader_file(v_shader_file);
    std::ifstream fragment_shader_file(f_shader_file);
    std::stringstream v_shader_stream, f_shader_stream;

    v_shader_stream << vertex_shader_file.rdbuf();
    f_shader_stream << fragment_shader_file.rdbuf();

    vertex_shader_file.close();
    fragment_shader_file.close();

    vertex_code = v_shader_stream.str();
    fragment_code = f_shader_stream.str();

    if (g_shader_file != nullptr) {
      std::ifstream geometry_shader_file(g_shader_file);
      std::stringstream g_shader_stream;
      g_shader_stream << geometry_shader_file.rdbuf();
      geometry_shader_file.close();
      geometry_code = g_shader_stream.str();
    }
  } catch (std::exception e) {
    std::cout << "ERROR::SHADER: Failed to read shader files\n";
  }

  const char* v_shader_code = vertex_code.c_str();
  const char* f_shader_code = fragment_code.c_str();
  const char* g_shader_code = geometry_code.c_str();

  auto shader = std::make_unique<Shader>();
  shader->Compile(v_shader_code, f_shader_code,
                  g_shader_file != nullptr ? g_shader_code : nullptr);

  return shader;
}

std::unique_ptr<Texture2D> ResourceManager::LoadTextureFromFile(
    const char* file,
    bool alpha) {
  auto texture = std::make_unique<Texture2D>();

  if (alpha) {
    texture->internal_format = GL_RGBA;
    texture->image_format = GL_RGBA;
  }

  int width, height, nr_channels;
  unsigned char* data = stbi_load(file, &width, &height, &nr_channels, 0);

  texture->Generate(width, height, data);
  stbi_image_free(data);

  return texture;
}
}  // namespace core