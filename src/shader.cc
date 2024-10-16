#include "shader.hh"
#include "utils.hh"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////
///
ShaderProgram::ShaderProgram(std::span<ShaderInfo>& shaders)
{
  ID = glCreateProgram();

  std::ifstream shader_file;
  std::string shader_contents;
  int success;
  char infoLog[512];

  for (auto& shader : shaders) {
    try {
      shader_contents = utils::ReadFile(shader.filename);
    } catch (const std::exception& e) {
      std::cerr << "ERROR: ShaderProgram constructor: " << e.what() << "\n";
    }
    shader.ID = glCreateShader(shader.type);
    const char* shader_code = shader_contents.c_str();
    glShaderSource(shader.ID, 1, &shader_code, nullptr);
    glCompileShader(shader.ID);

    glGetShaderiv(shader.ID, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader.ID, 512, nullptr, infoLog);
      std::cerr << "ERROR: ShaderProgram constructor: " << shader.type << " compilation failed\n" << infoLog << std::endl;
    }

    glAttachShader(ID, shader.ID);
  }

  glLinkProgram(ID);

  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(ID, 512, nullptr, infoLog);
    std::cout << "Error: Shader Program: Linking failed\n" << infoLog << std::endl;
  }

  for (const auto& shader : shaders) {
    glDeleteShader(shader.ID);
  }

}

////////////////////////////////////////////////////////////////////////////////
///
auto ShaderProgram::Use() -> void {
  glUseProgram(ID);
}

////////////////////////////////////////////////////////////////////////////////
///
auto ShaderProgram::SetBool(const std::string& name, bool value) -> void {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

////////////////////////////////////////////////////////////////////////////////
///
auto ShaderProgram::SetInt(const std::string& name, int value) -> void {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

////////////////////////////////////////////////////////////////////////////////
///
auto ShaderProgram::SetFloat(const std::string& name, float value) -> void {
  glUniform1f(GetUniformLocation(name), value);
}

////////////////////////////////////////////////////////////////////////////////
///
auto ShaderProgram::GetUniformLocation(const std::string& name) -> int32_t {
  if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
    return m_UniformLocationCache[name];
  }

  int32_t location = glGetUniformLocation(ID, name.c_str());
  if (location == -1) {
    std::cout << "Warning: uniform " << name << " doesn't exits!!\n";
    std::cout << "\tUniform: " << name << " with shader ID: " << ID << '\n';
  }

  // std::cout << "Setting uniform " << name << " to location " << location << '\n';
  m_UniformLocationCache[name] = location;
  return location;
}
