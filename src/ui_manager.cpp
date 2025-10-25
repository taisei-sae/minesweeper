#include "ui_manager.h"

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/imgui.h>

#include "game_settings.h"

UIManager::UIManager(GLFWwindow* window)
    : window_(window), initialized_(false) {}

UIManager::~UIManager() { cleanup(); }

bool UIManager::initialize() {
  if (initialized_) {
    return true;  // Already initialized
  }

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window_, true);
  ImGui_ImplOpenGL3_Init("#version 330");

  initialized_ = true;
  return true;
}

void UIManager::render(const GameBoard& board) {
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // Get window size
  int display_w, display_h;
  glfwGetFramebufferSize(window_, &display_w, &display_h);

  // Create console bar at the top (full width, fixed height)
  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::SetNextWindowSize(
      ImVec2((float)display_w, UIConfig::kConsoleBarHeight));
  ImGui::Begin("Console", nullptr,
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                   ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

  // Display game status message
  GameState state = board.get_game_state();

  // Display difficulty information
  Difficulty difficulty = board.get_difficulty();
  const char* diff_name = "Unknown";
  if (difficulty == Difficulty::Easy) {
    diff_name = "Easy";
  } else if (difficulty == Difficulty::Normal) {
    diff_name = "Normal";
  } else if (difficulty == Difficulty::Hard) {
    diff_name = "Hard";
  }

  ImGui::Text("Difficulty: %s | 1: Easy | 2: Normal | 3: Hard", diff_name);

  if (state == GameState::Playing) {
    ImGui::Text("Press 'R' to restart | Left Click: Open | Right Click: Flag");
  } else if (state == GameState::GameOver) {
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f),
                       "GAME OVER! You hit a bomb!");
    ImGui::SameLine();
    ImGui::Text("| Press 'R' to restart");
  } else if (state == GameState::Cleared) {
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f),
                       "CLEARED! Congratulations!");
    ImGui::SameLine();
    ImGui::Text("| Press 'R' to restart");
  }

  ImGui::End();

  // Rendering
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::cleanup() {
  if (!initialized_) {
    return;  // Already cleaned up or never initialized
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  initialized_ = false;
}
