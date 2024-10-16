add_library(Core Application.cc Shader.cc Texture.cc Physics.cc)

target_include_directories(Core PUBLIC
  ${CMAKE_SOURCE_DIR}/external
  ${CMAKE_SOURCE_DIR}/external/glad/include
  ${IMGUI_SRC}/
  ${IMGUI_SRC}/backends
)

target_link_libraries(Core PUBLIC
  glfw
  glad
  imgui
  implot
  OpenGL::OpenGL
)

# if(UNIX)
#   target_include_directories(Core 
#     PRIVATE 
#       ${CMAKE_SOURCE_DIR}/external/glad/include
#       ${CMAKE_SOURCE_DIR}/external
#       ${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/include
#   )
#   message(STATUS "Including vcpkg packages from directory:\n\t${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include")
#   # ${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/include")
#   target_link_libraries(Core
#     PRIVATE
#       glad
#       glfw3
#       imgui::imgui
#   )
# elseif(WIN32)
#   target_include_directories(Core
#     PRIVATE
#       ${CMAKE_SOURCE_DIR}/external/glad/include
#       ${CMAKE_SOURCE_DIR}/external
#       $ENV{VCPKG_ROOT}/packages/glfw3_x64-windows/include
#       ${CMAKE_SOURCE_DIR}/build/win/vcpkg_installed/x64-windows/include
#       ${CMAKE_SOURCE_DIR}/build/win/vcpkg_installed/x64-windows/include/GLFW
#   )
#   message(STATUS "$ENV{VCPKG_ROOT}/packages/glfw3_x64-windows/include")
#   target_link_libraries(Core
#     PRIVATE
#       glad
#       glfw
# )
# endif()

