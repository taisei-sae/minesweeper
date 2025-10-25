#ifndef RENDERER_H_
#define RENDERER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game_board.h"

class Renderer {
 public:
  Renderer();
  ~Renderer();

  // Initialize OpenGL resources (shaders, buffers)
  bool initialize();

  // Render the game board
  void render(const GameBoard& board);

  // Cleanup OpenGL resources
  void cleanup();

 private:
  unsigned int shader_program_;
  unsigned int vao_;
  unsigned int vbo_;

  // Compile and link shaders
  bool setup_shaders();

  // Get color based on cell state
  void get_cell_color(const Cell& cell, float& r, float& g, float& b) const;
};

#endif  // RENDERER_H_
