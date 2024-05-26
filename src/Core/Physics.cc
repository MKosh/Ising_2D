#include "Physics.h"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <cstdlib>
#include <random>


auto PhysicsEngine::Apply(Texture& texture) -> void {
  std::uniform_real_distribution<float> energy_dist(0.0,1.0);
  std::uniform_int_distribution<uint32_t> position_dist(0, texture.Rows()*texture.Columns());

  int tries = 1;
  int r;
  int pos;

  for (std::size_t i = 0; i < tries; ++i) {
    r = energy_dist(m_generator);
    pos = position_dist(m_generator);
    if (r < 0.5) {
      if (texture.PixelData()[pos] == 0xFF) {
        texture.PixelData()[pos] = 0x00;
      } else {
        texture.PixelData()[pos] = 0xFF;
      }
    }
  }

}
