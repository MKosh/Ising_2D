cmake_minimum_required(VERSION 3.24)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)

include(FetchContent)

project(ising LANGUAGES C CXX)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(imgui QUIET)

if (NOT TARGET imgui::imgui)
  message(STATUS "--- IMGUI not found on system. Fetching content")
  FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.0-docking
  )
  FetchContent_MakeAvailable(imgui)
  set(IMGUI_SRC "${CMAKE_BINARY_DIR}/_deps/imgui-src")
endif()

if (NOT TARGET implot::implot)
  message(STATUS "--- IMPLOT not found on system. Fetching content")
  FetchContent_Declare(
    implot
    GIT_REPOSITORY https://github.com/epezent/implot
    GIT_TAG f156599faefe316f7dd20fe6c783bf87c8bb6fd9
  )
  FetchContent_MakeAvailable(implot)
  set(IMPLOT_SRC "${CMAKE_BINARY_DIR}/_deps/implot-src")
endif()

# add_executable(ising ising.cc)
add_subdirectory(src)
add_subdirectory(external)

# target_include_directories(ising PRIVATE
#   src
#   ${CMAKE_SOURCE_DIR}/external/glad/include
# )

# target_link_libraries(ising PUBLIC
#   Core
#   glfw
#   glad
#   imgui
#   implot
#   OpenGL::OpenGL
# )

