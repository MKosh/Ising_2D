#include "Application.h"

#include <GLFW/glfw3.h>
#include <cstdint>
#include "Shader.h"
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

const uint32_t screen_width = 1200;
const uint32_t screen_height =1000;

auto Application::CreateScreenQuad() -> void {

  float vertices[] = {
    // x, y, z       texture coords
     1.0,  1.0, 0.0, 1.0, 1.0,
     1.0, -1.0, 0.0, 1.0, 0.0,
    -1.0, -1.0, 0.0, 0.0, 0.0,
    -1.0,  1.0, 0.0, 0.0, 1.0
  };

  uint32_t indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  uint32_t vbo, ebo;
  glCreateVertexArrays(1, &m_quad);
  glCreateBuffers(1, &vbo);
  glCreateBuffers(1, &ebo);

  glBindVertexArray(m_quad);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}


Application::Application(Texture& data, PhysicsEngine& physics) : m_grid(data),
                          m_physics(physics) {
  std::cout << "Starting application\n";
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(screen_width, screen_height, "Window", nullptr, nullptr);
  glfwSetWindowUserPointer(window, this);
  glfwSetKeyCallback(window, KeyCallback);
  glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
  glfwMakeContextCurrent(window);
  if (window == nullptr) {
    std::cout << "ERROR making window" << std::endl;
    glfwTerminate();
  }

  int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0) {
    std::cout << "ERROR loading GLAD" << std::endl;
  }

  glViewport(0, 0, screen_width, screen_height);

  std::cout << "OpenGL version " << glGetString(GL_VERSION) << '\n';

  // IMGUI_CHECKVERSION();
  // ImGui::CreateContext();
  // m_imgui_io = ImGui::GetIO();
  // m_imgui_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  // ImGui_ImplGlfw_InitForOpenGL(window, true);
  // ImGui_ImplOpenGL3_Init();

  CreateScreenQuad();
  m_grid.InitialTexture();

}

auto Application::Run() -> void {
  using namespace std::string_literals;


  Shader quad_shader{"resources/shaders/quad.vert"s, "resources/shaders/quad.frag"s};

  while(!glfwWindowShouldClose(window)) {

    // ImGui_ImplOpenGL3_NewFrame();
    // ImGui_ImplGlfw_NewFrame();
    // ImGui::NewFrame();
    // ImGui::ShowDemoWindow();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (m_physics_running) {
      ApplyPhysics();
    }


    // ImGui::Begin("Here's a window");
    // ImVec2 size = ImGui::GetWindowSize();
    // auto w = ImGui::GetContentRegionAvail().x;
    // auto h = ImGui::GetContentRegionAvail().y;
    // ImGui::Image((void*)(intptr_t)m_grid.ID(), ImVec2(w,h));
    // ImGui::End();

    // ImGui::Render();
    // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Bind framebuffer

    quad_shader.Use();
    glBindTexture(GL_TEXTURE_2D, TextureID());
    glBindVertexArray(m_quad);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // unbind framebuffer

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

Application::~Application() {
  glfwTerminate();
  // ImGui_ImplOpenGL3_Shutdown();
  // ImGui::DestroyContext();
}

auto Application::ApplyPhysics() -> void {
  m_physics.Apply(m_grid);
  m_grid.Update();
}

auto Application::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) -> void {
  Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
  app->OnKey(key, action);
}

auto Application::OnKey(int key, int action) -> void {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {

    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
      m_physics_running = !m_physics_running;
    }
}

auto Application::FrameBufferSizeCallback(GLFWwindow* window, int width, int height) -> void {
  Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
  app->WindowResize(width, height);
}

auto Application::WindowResize(int width, int height) -> void {
  glViewport(0, 0, width, height); 
}
