#include "utils.hh"

// #include <exception>
#include <fstream>
#include <filesystem>

// namespace fs = std::filesystem;

namespace utils {

auto ReadFile(fs::path path) -> std::string
{
  std::ifstream in_file;
  
  in_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  in_file.open(path);
  if (!in_file.good()) {
    throw std::ios_base::failure("Cannot open file: " + path.string());
  }

  const auto file_size = fs::file_size(path);
  std::string contents(file_size, '\0');

  in_file.read(contents.data(), file_size);

  if (contents.length() == 0) {
    throw "Empty file";
  }
  return contents;
}

}
