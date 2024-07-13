#pragma once

#include <unordered_map>
#include <cstdint>
#include <random>

#include "Texture.h"

class PhysicsEngine {
public:

  enum class Spin {
    Down = -1,
    Up = 1
  };

  std::unordered_map<int, int> spin_to_color;
  std::unordered_map<int, int> color_to_spin;

  PhysicsEngine() = default;
  PhysicsEngine(float temperature, Texture& texture);

  auto Apply(Texture& texture) -> void;
  auto SetMagnetization(int32_t mag) -> void { magnetization = mag; }
  auto CountSpins(Texture& texture) -> int32_t;

private:
  std::mt19937 m_generator{std::random_device{}()};
  std::unordered_map<int32_t, float> W;
  float temperature = 0.0;
  int32_t magnetization = 0;

  auto e4(float Temperature) -> float {
    return std::pow(-4,Temperature);
  }

  auto e8(float Temperature) -> float {
    return std::pow(-8,Temperature);
  }

};

