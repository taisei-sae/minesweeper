#include "ui_manager.h"

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/imgui.h>

#include <cstdio>

#include "game_settings.h"

UIManager::UIManager(GLFWwindow* window)
    : window_(window), initialized_(false), large_font_(nullptr) {}

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

  // Load default font first (for UI console)
  io.Fonts->AddFontDefault();

  // Load custom font with larger size for game overlay
  // DejaVu Sans Bold is a high-quality font available on Ubuntu
  const char* font_path =
      "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf";
  large_font_ = io.Fonts->AddFontFromFileTTF(
      font_path, 48.0f);  // Load at 48pt for high quality
  io.Fonts->Build();

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

  // Overlay numbers and symbols on game board cells
  render_game_overlay(board, display_w, display_h);

  // Rendering
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::render_game_overlay(const GameBoard& board, int display_w,
                                    int display_h) {
  // Create an invisible overlay window that covers the game board area
  ImGui::SetNextWindowPos(ImVec2(0, UIConfig::kConsoleBarHeight));
  ImGui::SetNextWindowSize(
      ImVec2((float)display_w, display_h - UIConfig::kConsoleBarHeight));
  ImGui::Begin("GameOverlay", nullptr,
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                   ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                   ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoInputs);

  unsigned int rows = board.get_rows();
  unsigned int cols = board.get_columns();

  float board_height = display_h - UIConfig::kConsoleBarHeight;
  float cell_width = (float)display_w / cols;
  float cell_height = board_height / rows;

  ImDrawList* draw_list = ImGui::GetWindowDrawList();

  // Use custom loaded font for numbers - scale based on cell size
  ImFont* font = large_font_ ? large_font_ : ImGui::GetFont();
  float font_size = cell_height * 0.6f;  // Use 60% of cell height for font size

  for (unsigned int row = 0; row < rows; ++row) {
    for (unsigned int col = 0; col < cols; ++col) {
      const Cell& cell = board.get_cell(row, col);

      // Only draw on opened cells
      if (!cell.is_open()) {
        continue;
      }

      float x = col * cell_width + cell_width / 2.0f;
      float y =
          UIConfig::kConsoleBarHeight + row * cell_height + cell_height / 2.0f;

      if (cell.has_bomb()) {
        // Draw bomb symbol with larger font
        draw_list->AddText(font, font_size,
                           ImVec2(x - font_size * 0.3f, y - font_size * 0.5f),
                           IM_COL32(255, 0, 0, 255), "B");
      } else if (cell.get_bomb_count() > 0) {
        // Draw number
        char num_str[2];
        snprintf(num_str, sizeof(num_str), "%d", cell.get_bomb_count());

        // Color based on count
        ImU32 color;
        switch (cell.get_bomb_count()) {
          case 1:
            color = IM_COL32(0, 0, 255, 255);  // Blue
            break;
          case 2:
            color = IM_COL32(0, 128, 0, 255);  // Green
            break;
          case 3:
            color = IM_COL32(255, 0, 0, 255);  // Red
            break;
          case 4:
            color = IM_COL32(0, 0, 128, 255);  // Dark blue
            break;
          case 5:
            color = IM_COL32(128, 0, 0, 255);  // Dark red
            break;
          case 6:
            color = IM_COL32(0, 128, 128, 255);  // Cyan
            break;
          case 7:
            color = IM_COL32(0, 0, 0, 255);  // Black
            break;
          case 8:
            color = IM_COL32(128, 128, 128, 255);  // Gray
            break;
          default:
            color = IM_COL32(0, 0, 0, 255);
        }

        draw_list->AddText(font, font_size,
                           ImVec2(x - font_size * 0.3f, y - font_size * 0.5f),
                           color, num_str);
      }
    }
  }

  ImGui::End();
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
