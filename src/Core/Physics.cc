#include "Physics.h"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <cstdlib>
#include <random>
#include <iostream>


PhysicsEngine::PhysicsEngine(float temperature, Texture& texture) {
  W[4] = e8(temperature);
  W[-4] = e8(temperature);
  W[2] = e4(temperature);
  W[-2] = e4(temperature);

  spin_to_color[-1] = 0x00;
  spin_to_color[1] = 0xFF;

  color_to_spin[0x00] = -1;
  color_to_spin[0xFF] = 1;

  magnetization = CountSpins(texture);
  std::cout << "Initial magnetization = " << magnetization << '\n';
}

auto PhysicsEngine::CountSpins(Texture& texture) -> int32_t {
  std::cout << "MAG: " << magnetization << '\n';
  for (size_t elem = 0; elem < texture.Columns()*texture.Rows(); ++elem) {
    magnetization += color_to_spin[texture.PixelData()[elem]]; 
  }
  return magnetization;
}

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
      if (texture.PixelData()[pos] == spin_to_color[1]) {
        texture.PixelData()[pos] = spin_to_color[-1];
      } else {
        texture.PixelData()[pos] = spin_to_color[1];
      }
      magnetization += color_to_spin[texture.PixelData()[pos]];
      // if (texture.PixelData()[pos] == 0xFF) {
      //   texture.PixelData()[pos] = 0x00;
      // } else {
      //   texture.PixelData()[pos] = 0xFF;
      // }
    }
  }

  std::cout << "M = " << magnetization << '\n';

}
