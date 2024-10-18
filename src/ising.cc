#include "ising.hh"

#include <cstdlib>
#include <iostream>
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

const int32_t g_winwidth = 800;
const int32_t g_winheight= 600;

auto FramebufferSizeCallback(GLFWwindow* window, int width, int height) -> void
{
  glViewport(0, 0, width, height);
}

auto KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) -> void
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

int main (int argc, char *argv[]) {
  #ifdef DEBUG
    std::cout << "DEBUG:: Starting ising simulation\n";
  #endif
  
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(g_winwidth, g_winheight, "Ising Model", nullptr, nullptr);
  glfwSetKeyCallback(window, KeyCallback);
  glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
  glfwMakeContextCurrent(window);

  if (window == nullptr) {
    std::cerr << "ERROR::Error creating window" << std::endl;
    glfwTerminate();
    return EXIT_FAILURE;
  }

  int version = gladLoadGL(glfwGetProcAddress);
  #ifdef DEBUG
    std::cout << "DEBUG::OpenGL version: " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;
  #endif

  if (version == 0) {
    std::cerr << "ERROR::Cannot load GLAD" << std::endl;
    return EXIT_FAILURE;
  }

  glViewport(0, 0, g_winwidth, g_winheight);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.Fonts->AddFontFromFileTTF("resources/fonts/JetBrainsMonoNLNerdFontMono-Regular.ttf", 20);
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 6.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();

  while(!glfwWindowShouldClose(window)) {

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

    ImGui::Begin("Here's a window");
    ImVec2 size = ImGui::GetWindowSize();
    auto w = ImGui::GetContentRegionAvail().x;
    auto h = ImGui::GetContentRegionAvail().y;
    // ImGui::Image((void*)(intptr_t)m_grid.ID(), ImVec2(w,h));
    ImGui::End();

    ImGui::Begin("Another window");
    ImGui::End();

    glClearColor(0.3f, 0.5f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
