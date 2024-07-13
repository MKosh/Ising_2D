cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
#set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
#set(CMAKE_C_COMPILER_WORKS)

if(UNIX) 
  # set(CMAKE_TOOLCHAIN_FILE /home/markm/packages/vcpkg/scripts/buildsystems/vcpkg.cmake)
  # message(STATUS "VCPKG: $ENV{VCPKG_BUILDSYSTEMS}")
  # set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_BUILDSYSTEMS}/vcpkg.cmake)
  # set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT}/share/scripts/buildsystems/vcpkg.cmake)
  set(CMAKE_CXX_COMPILER clang++)
  set(CMAKE_C_COMPILER clang)
  # set(CMAKE_GENERATOR make)
  # set(CMAKE_MAKE_PROGRAM $ENV{MAKE_LOCATION}/make)
elseif(WIN32)
  set(CMAKE_TOOLCHAIN_FILE c:/packages/vcpkg/scripts/buildsystems/vcpkg.cmake)
endif()

set(CMAKE_CXX_STANDARD 23)

project(ising LANGUAGES C CXX)

find_package(glfw3 REQUIRED)
# find_package(imgui REQUIRED)


add_executable(ising ising.cc)

add_subdirectory(src)
add_subdirectory(external)

if(UNIX)
  target_include_directories(ising
    PRIVATE
      ${CMAKE_SOURCE_DIR}/src
      ${CMAKE_SOURCE_DIR}/external/glad/include
      $ENV{IMGUI}/include/imgui
      # ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include
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
