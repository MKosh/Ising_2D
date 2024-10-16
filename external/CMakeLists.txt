add_library(imgui 
  ${IMGUI_SRC}/imgui.cpp
  ${IMGUI_SRC}/imgui_demo.cpp
  ${IMGUI_SRC}/imgui_draw.cpp
  ${IMGUI_SRC}/imgui_tables.cpp
  ${IMGUI_SRC}/imgui_widgets.cpp
  ${IMGUI_SRC}/backends/imgui_impl_glfw.cpp
  ${IMGUI_SRC}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
  ${IMGUI_SRC}
  ${IMGUI_SRC}/backends
)

add_library(implot
  ${IMPLOT_SRC}/implot.cpp
  ${IMPLOT_SRC}/implot_items.cpp
  ${IMPLOT_SRC}/implot_demo.cpp
)

target_include_directories(implot PUBLIC
  ${IMPLOT_SRC}
  ${IMGUI_SRC}
  ${IMGUI_SRC}/backends
)

add_subdirectory(glad)
