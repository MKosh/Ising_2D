#pragma once

#include <cstdint>
#include <filesystem>
#include "glad/gl.h"

#include <span>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;

class Shader {
private:
  uint32_t ID;
  std::unordered_map<std::string, int32_t> m_UniformLocationCache;
  auto GetUniformLocation(const std::string& name) -> int32_t;

public:
  Shader(const std::string& vertex_path, const std::string& fragment_path);
  Shader(const char* vertexSource, const char* fragmentSource);

  auto Use() -> void;
  auto SetBool(const std::string& name, bool value) -> void;
  auto SetInt(const std::string& name, int value) -> void;
  auto SetFloat(const std::string& name, float value) -> void;
};

////////////////////////////////////////////////////////////////////////////////
/// \brief ShaderInfo class
class ShaderInfo {
  GLenum type;
  fs::path filename;
};

////////////////////////////////////////////////////////////////////////////////
/// \brief ShaderProgram class
class ShaderProgram {
private:
  uint32_t ID;
  std::unordered_map<std::string, int32_t> m_UniformLocationCache;
  auto GetUniformLocation(const std::string& name) -> int32_t;

public:
  // ShaderProgram(const std::string& vertex_path, const std::string& fragment_path);
  // ShaderProgram(const char* vertexSource, const char* fragmentSource);

  auto LoadShaders(std::span<ShaderInfo> shaders) -> void;

  auto Use() -> void;
  auto SetBool(const std::string& name, bool value) -> void;
  auto SetInt(const std::string& name, int value) -> void;
  auto SetFloat(const std::string& name, float value) -> void;
};

