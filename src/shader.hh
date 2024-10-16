#pragma once

#include <cstdint>
#include <filesystem>
#include "glad/gl.h"

#include <span>
#include <vector>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;

class ShaderProgram;

////////////////////////////////////////////////////////////////////////////////
/// \brief ShaderInfo class
class ShaderInfo {
  GLenum type;
  fs::path filename;
  uint32_t ID;
  friend ShaderProgram;
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

  //////////////////////////////////////////////////////////////////////////////
  /// \brief
  ShaderProgram() = default;

  //////////////////////////////////////////////////////////////////////////////
  /// \brief
  ShaderProgram(std::vector<ShaderInfo>& shaders);

  //////////////////////////////////////////////////////////////////////////////
  /// \brief
  ShaderProgram(std::span<ShaderInfo>& shaders);

  //////////////////////////////////////////////////////////////////////////////
  /// \brief Load Shaders
  auto LoadShaders(std::span<ShaderInfo> shaders) -> void;

  auto Use() -> void;
  auto SetBool(const std::string& name, bool value) -> void;
  auto SetInt(const std::string& name, int value) -> void;
  auto SetFloat(const std::string& name, float value) -> void;

};

