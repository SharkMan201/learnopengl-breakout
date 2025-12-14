#ifndef SHADER_H
#define SHADER_H
#include <glm/glm.hpp>
#include <string>

namespace core {
class Shader {
 public:
  Shader(const Shader&) = delete;
  Shader& operator=(const Shader&) = delete;

  unsigned int id;

  Shader() {}
  Shader& Use();
  void Compile(const char* vertext_source,
               const char* fragment_source,
               const char* geometry_source = nullptr);

  void SetFloat(const char* name, float value, bool use_shader = false);
  void SetInteger(const char* name, int value, bool use_shader = false);
  void SetVector2F(const char* name, float x, float y, bool use_shader = false);
  void SetVector2F(const char* name, glm::vec2 value, bool use_shader = false);
  void SetVector3F(const char* name,
                   float x,
                   float y,
                   float z,
                   bool use_shader = false);
  void SetVector3F(const char* name, glm::vec3 value, bool use_shader = false);
  void SetVector4F(const char* name,
                   float x,
                   float y,
                   float z,
                   float w,
                   bool use_shader = false);
  void SetVector4F(const char* name, glm::vec4 value, bool use_shader = false);
  void SetMatrix4(const char* name, glm::mat4& matrix, bool use_shader = false);

 private:
  void CheckCompileErrors(unsigned int object, std::string type);
};
}  // namespace core

#endif