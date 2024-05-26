#pragma once

#include "Texture.h"
#include "Physics.h"
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include <cstdint>
#include "imgui.h"
#include <vector>

auto ProcessInput(GLFWwindow* window) -> void;

class Application {
public:

  auto Run() -> void;
  auto ApplyPhysics() -> void;
  auto TextureID() -> std::uint32_t { return m_grid.ID(); }
  auto CreateScreenQuad() -> void;
  auto OnKey(int key, int action) -> void;
  auto WindowResize(int width, int height) -> void;
  Application();
  Application(Texture& data, PhysicsEngine& physics);
  Application(std::int32_t width, std::int32_t height);
  ~Application();

private:
  GLFWwindow* window;
  uint32_t m_quad;
  Texture& m_grid;
  PhysicsEngine& m_physics;
  bool m_physics_running = false;
  ImGuiIO m_imgui_io;
  
  static auto KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) -> void;
  static auto FrameBufferSizeCallback(GLFWwindow* window, int width, int height) -> void;
};
