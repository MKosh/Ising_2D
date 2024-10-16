add_executable(ising ising.cc shader.cc utils.cc)

target_link_libraries(ising PUBLIC
  glfw
  glad
  imgui
  # implot
  OpenGL::OpenGL
)

target_include_directories(ising PUBLIC
  ${CMAKE_SOURCE_DIR}/external
  ${CMAKE_SOURCE_DIR}/external/glad/include
  ${IMGUI_SRC}
  ${IMGUI_SRC}/backends
)
# add_subdirectory(Core)
