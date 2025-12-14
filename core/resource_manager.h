#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <map>
#include <memory>
#include <string>
#include "shader.h"
#include "texture.h"

namespace core {
class ResourceManager {
 public:
  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;

  static std::map<std::string, std::unique_ptr<Shader>> shaders;
  static std::map<std::string, std::unique_ptr<Texture2D>> textures;
  static Shader* LoadShader(const char* v_shader_file,
                            const char* f_shader_file,
                            const char* g_shader_file,
                            std::string name);
  static Shader* GetShader(std::string name);
  static Texture2D* LoadTexture(const char* file, bool alpha, std::string name);
  static Texture2D* GetTexture(std::string name);
  static void Clear();

 private:
  ResourceManager() = default;
  static std::unique_ptr<Shader> LoadShaderFromFile(
      const char* v_shader_file,
      const char* f_shader_file,
      const char* g_shader_file = nullptr);
  static std::unique_ptr<Texture2D> LoadTextureFromFile(const char* file,
                                                        bool alpha);
};
}  // namespace core
#endif