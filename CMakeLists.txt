cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

if(UNIX) 
  set(CMAKE_TOOLCHAIN_FILE /home/markm/packages/vcpkg/scripts/buildsystems/vcpkg.cmake)
  set(CMAKE_CXX_COMPILER /usr/bin/clang++)
elseif(WIN32)
  set(CMAKE_TOOLCHAIN_FILE c:/packages/vcpkg/scripts/buildsystems/vcpkg.cmake)
endif()

set(CMAKE_CXX_STANDARD 23)

project(ising LANGUAGES C CXX)

find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)

add_executable(ising ising.cc)

add_subdirectory(src)
add_subdirectory(external)

if(UNIX)
  target_include_directories(ising
    PRIVATE
      ${CMAKE_SOURCE_DIR}/src
      ${CMAKE_SOURCE_DIR}/external/glad/include
      ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include
  )
elseif(WIN32)
  target_include_directories(ising
    PRIVATE
      ${CMAKE_SOURCE_DIR}/src
      ${CMAKE_SOURCE_DIR}/external/glad/include
      ${CMAKE_SOURCE_DIR}/build/win/vcpkg_installed/x64-windows/include
  )
  target_link_directories(ising
    PRIVATE
      ${CMAKE_SOURCE_DIR}/build/win/vcpkg_installed/x64-windows/lib)
endif()

target_link_libraries(ising
  PRIVATE
    Core
)
