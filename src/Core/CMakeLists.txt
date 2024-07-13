set(IMGUI_SOURCES 
  $ENV{IMGUI}/include/imgui/imgui.cpp
  $ENV{IMGUI}/include/imgui/imgui_draw.cpp
  $ENV{IMGUI}/include/imgui/imgui_tables.cpp
  $ENV{IMGUI}/include/imgui/imgui_widgets.cpp
  $ENV{IMGUI}/include/imgui/backends/imgui_impl_opengl3.cpp
  $ENV{IMGUI}/include/imgui/backends/imgui_impl_glfw.cpp
  $ENV{IMGUI}/include/imgui/imgui_demo.cpp
)

set(IMGUI_HEADERS
  $ENV{IMGUI}/include/imgui
  $ENV{IMGUI}/include/imgui/backends
)

add_library(Core Application.cc Shader.cc Texture.cc Physics.cc ${IMGUI_SOURCES})

if(UNIX)
  target_include_directories(Core 
    PRIVATE 
      ${CMAKE_SOURCE_DIR}/external/glad/include
      ${CMAKE_SOURCE_DIR}/external
      ${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/include
      ${IMGUI_HEADERS}
  )
  message(STATUS "Imgui include dir:${IMGUI_HEADERS}")
  # message(STATUS "Including vcpkg packages from directory:\n\t${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include")
  target_link_libraries(Core
    PRIVATE
      glad
      glfw
  )
elseif(WIN32)
  target_include_directories(Core
    PRIVATE
      ${CMAKE_SOURCE_DIR}/external/glad/include
      ${CMAKE_SOURCE_DIR}/external
      $ENV{VCPKG_ROOT}/packages/glfw3_x64-windows/include
      ${CMAKE_SOURCE_DIR}/build/win/vcpkg_installed/x64-windows/include
      ${CMAKE_SOURCE_DIR}/build/win/vcpkg_installed/x64-windows/include/GLFW
  )
  message(STATUS "$ENV{VCPKG_ROOT}/packages/glfw3_x64-windows/include")
  target_link_libraries(Core
    PRIVATE
      glad
      glfw
)
endif()

