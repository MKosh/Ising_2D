#include <cstdlib>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>

#include "Core/Application.h"
#include "Core/Physics.h"

int main(int argc, char* argv[]) {
    try {
      Texture grid{32, 32, Texture::GridType::Random};
      PhysicsEngine ising_model(3.0f, grid);
      Application app{grid, ising_model};
      app.Run();
    } catch (std::exception& e) {
      std::cout << "Error!! " << e.what() << std::endl;
    }
  return 0;
}
