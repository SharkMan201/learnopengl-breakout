#include "shader.h"
#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace core {
Shader& Shader::Use() {
  glUseProgram(id);
  return *this;
}

void Shader::Compile(const char* vertex_source,
                     const char* fragment_source,
                     const char* geometry_source) {
  unsigned int s_vertex, s_fragment, s_geometry;

  s_vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(s_vertex, 1, &vertex_source, nullptr);
  glCompileShader(s_vertex);
  CheckCompileErrors(s_vertex, "Vertex");

  s_fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(s_fragment, 1, &fragment_source, nullptr);
  glCompileShader(s_fragment);
  CheckCompileErrors(s_fragment, "Fragment");

  if (geometry_source != nullptr) {
    s_geometry = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(s_geometry, 1, &geometry_source, nullptr);
    glCompileShader(s_geometry);
    CheckCompileErrors(s_geometry, "Geometry");
  }

  id = glCreateProgram();
  glAttachShader(id, s_vertex);
  glAttachShader(id, s_fragment);
  if (geometry_source != nullptr)
    glAttachShader(id, s_geometry);

  glLinkProgram(id);
  CheckCompileErrors(id, "Program");
  glDeleteShader(s_vertex);
  glDeleteShader(s_fragment);
  if (geometry_source != nullptr)
    glDeleteShader(s_geometry);
}

void Shader::SetFloat(const char* name, float value, bool use_shader) {
  if (use_shader)
    Use();
  glUniform1f(glGetUniformLocation(id, name), value);
}

void Shader::SetInteger(const char* name, int value, bool use_shader) {
  if (use_shader)
    Use();
  glUniform1i(glGetUniformLocation(id, name), value);
}

void Shader::SetVector2F(const char* name, float x, float y, bool use_shader) {
  if (use_shader)
    Use();
  glUniform2f(glGetUniformLocation(id, name), x, y);
}

void Shader::SetVector2F(const char* name, glm::vec2 value, bool use_shader) {
  if (use_shader)
    Use();
  glUniform2f(glGetUniformLocation(id, name), value.x, value.y);
}

void Shader::SetVector3F(const char* name,
                         float x,
                         float y,
                         float z,
                         bool use_shader) {
  if (use_shader)
    Use();
  glUniform3f(glGetUniformLocation(id, name), x, y, z);
}

void Shader::SetVector3F(const char* name, glm::vec3 value, bool use_shader) {
  if (use_shader)
    Use();
  glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);
}

void Shader::SetVector4F(const char* name,
                         float x,
                         float y,
                         float z,
                         float w,
                         bool use_shader) {
  if (use_shader)
    Use();
  glUniform4f(glGetUniformLocation(id, name), x, y, z, w);
}

void Shader::SetVector4F(const char* name, glm::vec4 value, bool use_shader) {
  if (use_shader)
    Use();
  glUniform4f(glGetUniformLocation(id, name), value.x, value.y, value.z,
              value.w);
}

void Shader::SetMatrix4(const char* name, glm::mat4& matrix, bool use_shader) {
  if (use_shader)
    Use();
  glUniformMatrix4fv(glGetUniformLocation(id, name), 1, false,
                     glm::value_ptr(matrix));
}

void Shader::CheckCompileErrors(unsigned int object, std::string type) {
  int success;
  char info_log[1024];
  if (type != "Program") {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(object, 102, nullptr, info_log);
      std::cout
          << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
          << info_log
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
    }
  } else {
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(object, 1024, nullptr, info_log);
      std::cout
          << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
          << info_log
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
    }
  }
}
}  // namespace core