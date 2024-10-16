#pragma once

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

namespace utils {

auto ReadFile(fs::path path) -> std::string;

}
