#include "renderer.h"

#include <iostream>
#include <vector>

// Vertex shader source code
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    ourColor = aColor;
}
)";

// Fragment shader source code
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
in vec3 ourColor;

void main() {
    FragColor = vec4(ourColor, 1.0f);
}
)";

Renderer::Renderer(GLFWwindow* window)
    : window_(window), shader_program_(0), vao_(0), vbo_(0) {}

Renderer::~Renderer() { cleanup(); }

bool Renderer::initialize() {
  if (!setup_shaders()) {
    return false;
  }

  // Create VAO and VBO
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);

  return true;
}

bool Renderer::setup_shaders() {
  // Compile vertex shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
    return false;
  }

  // Compile fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
    glDeleteShader(vertexShader);
    return false;
  }

  // Link shaders
  shader_program_ = glCreateProgram();
  glAttachShader(shader_program_, vertexShader);
  glAttachShader(shader_program_, fragmentShader);
  glLinkProgram(shader_program_);
  glGetProgramiv(shader_program_, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program_, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return false;
  }

  // Clean up
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return true;
}

void Renderer::get_cell_color(const Cell& cell, float& r, float& g,
                              float& b) const {
  // If cell is not open
  if (!cell.is_open()) {
    // Show flag as orange if flagged
    if (cell.has_flag()) {
      r = 1.0f;
      g = 0.6f;
      b = 0.0f;
    } else {
      // Dark gray for unopened cells
      r = 0.3f;
      g = 0.3f;
      b = 0.3f;
    }
    return;
  }

  // Cell is open - show its content
  if (cell.has_bomb()) {
    // Red for bombs
    r = 1.0f;
    g = 0.0f;
    b = 0.0f;
  } else {
    unsigned int count = cell.get_bomb_count();
    if (count == 0) {
      // Light gray for zero
      r = 0.9f;
      g = 0.9f;
      b = 0.9f;
    } else {
      // Color gradient based on bomb count (1-8)
      // Blue (1) -> Green (2-3) -> Yellow (4-5) -> Orange (6-7) -> Red (8)
      float intensity = count / 8.0f;
      r = intensity;
      g = 1.0f - intensity;
      b = 0.3f;
    }
  }
}

void Renderer::render(const GameBoard& board) {
  // Clear screen
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // Get window dimensions to calculate console bar offset
  int display_w, display_h;
  glfwGetFramebufferSize(window_, &display_w, &display_h);
  const float console_height = 60.0f;  // Same as UIManager console bar height

  // Calculate the vertical offset in normalized coordinates
  // The game board should start below the console bar
  float console_height_ndc = (console_height / display_h) * 2.0f;  // Convert to NDC (-1 to 1 range)
  float board_vertical_size = 2.0f - console_height_ndc;  // Remaining vertical space for board

  // Generate vertices for all cells
  std::vector<float> vertices;
  unsigned int rows = board.get_rows();
  unsigned int cols = board.get_columns();

  float cell_width = 2.0f / cols;  // Normalized device coordinates (-1 to 1)
  float cell_height = board_vertical_size / rows;  // Use only the remaining vertical space
  float padding = 0.02f;  // Small gap between cells

  for (unsigned int row = 0; row < rows; ++row) {
    for (unsigned int col = 0; col < cols; ++col) {
      const Cell& cell = board.get_cell(row, col);

      // Get color for this cell
      float r, g, b;
      get_cell_color(cell, r, g, b);

      // Calculate cell position (top-left origin, y increases downward)
      // Start from below the console bar (1.0 - console_height_ndc)
      float x1 = -1.0f + col * cell_width + padding;
      float y1 = 1.0f - console_height_ndc - row * cell_height - padding;
      float x2 = x1 + cell_width - 2 * padding;
      float y2 = y1 - cell_height + 2 * padding;

      // We don't use Triangle Strips for simplicity
      //
      // Two triangles to make a rectangle
      // Triangle 1: Top-left -> Top-right -> Bottom-left
      vertices.push_back(x1);
      vertices.push_back(y1);  // Top-left
      vertices.push_back(r);
      vertices.push_back(g);
      vertices.push_back(b);

      vertices.push_back(x2);
      vertices.push_back(y1);  // Top-right
      vertices.push_back(r);
      vertices.push_back(g);
      vertices.push_back(b);

      vertices.push_back(x1);
      vertices.push_back(y2);  // Bottom-left
      vertices.push_back(r);
      vertices.push_back(g);
      vertices.push_back(b);

      // Triangle 2: Top-right -> Bottom-right -> Bottom-left
      vertices.push_back(x2);
      vertices.push_back(y1);  // Top-right
      vertices.push_back(r);
      vertices.push_back(g);
      vertices.push_back(b);

      vertices.push_back(x2);
      vertices.push_back(y2);  // Bottom-right
      vertices.push_back(r);
      vertices.push_back(g);
      vertices.push_back(b);

      vertices.push_back(x1);
      vertices.push_back(y2);  // Bottom-left
      vertices.push_back(r);
      vertices.push_back(g);
      vertices.push_back(b);
    }
  }

  // Upload vertex data
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
               vertices.data(), GL_DYNAMIC_DRAW);

  // Position attribute (2 floats)
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Color attribute (3 floats)
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void*)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Draw
  glUseProgram(shader_program_);
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 5);
}

void Renderer::cleanup() {
  if (vao_ != 0) {
    glDeleteVertexArrays(1, &vao_);
    vao_ = 0;
  }
  if (vbo_ != 0) {
    glDeleteBuffers(1, &vbo_);
    vbo_ = 0;
  }
  if (shader_program_ != 0) {
    glDeleteProgram(shader_program_);
    shader_program_ = 0;
  }
}
