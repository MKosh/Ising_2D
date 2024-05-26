#pragma once

#include <random>

#include "Texture.h"

class PhysicsEngine {
public:
  PhysicsEngine() = default;

  auto Apply(Texture& texture) -> void;

private:
  std::mt19937 m_generator{std::random_device{}()};

};

