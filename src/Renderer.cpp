#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Vertex shader source code
const char *vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourColor = aColor;
}
)";

// Fragment shader source code
const char *fragmentShaderSource = R"(
# version 330 core
out vec4 FragColor;
in vec3 ourColor;

void main() {
    FragColor = vec4(ourColor, 1.0f);
}
)";

int main() {
  // 1. Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }
  // Configure GLFW to use OpenGL 3.3 in the window
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // use core profile to avoid deprecated functions
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // 2. Create a window
  GLFWwindow *window = glfwCreateWindow(800, 600, "MineSweeper", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  // activate an GLFW context of the created window in this thread
  glfwMakeContextCurrent(window);

  // 3. Initialize GLEW
  glewExperimental = GL_TRUE;
  // glewInit() detects OpenGL's version that the system supports
  // and available extensions.
  // Also this function assigns addresses of functions into function pointers.
  // New functions like `glCreateShader` below are function pointer,
  // because the implementations are dependant on GPU drivers.
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  // 4. Build and compile our shader program
  // Vertex shader
  // Create shader object
  unsigned int vertexShader =
      glCreateShader(GL_VERTEX_SHADER);  // <- funtion pointer!
  // Attach source code
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  // Compile
  glCompileShader(vertexShader);
  // Error check
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // Fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // Link shaders
  unsigned int shaderProgram = glCreateProgram();
  // Attach shaders to a program object
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  // Create an executable on GPU
  glLinkProgram(shaderProgram);
  // Error check
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::PROGRAM::LINKING::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
  // free the memory
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // 5. Define vertex data for a triangle
  float vertices[] = {
      // (x, y, z) + (R, G, B)
      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left (red)
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right (green)
      0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f   // top (blue)
  };

  // 6. Create Vertex Buffer Object and Vertex Array Object
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);  // the metadata of VBO, like data format
  glGenBuffers(1, &VBO);       // store vertice info on GPU memory

  // Activate
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // Send data to GPU memory
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Position attribute
  // store position data format
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // Color attribute
  // store color data format after position data
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);

  // free the memory
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // 7. Render loop
  while (!glfwWindowShouldClose(window)) {
    // Rendering commands
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  // set the background color
    glClear(GL_COLOR_BUFFER_BIT);          // clear the buffer

    // Draw the triangle
    glUseProgram(shaderProgram);  // use ShaderProgram
    glBindVertexArray(VAO);       // use VAO when read the buffer
    glDrawArrays(GL_TRIANGLES, 0,
                 3);  // Read the points in the buffer as a triangle

    // Swap the front buffer and the back buffer (double buffering).
    // Front buffer stores the image displayed now.
    // Back buffer stores the next image.
    // `glDrawArrays()` drew a triangle on the back buffer.
    glfwSwapBuffers(window);

    // Process window event (like key inputs) here
    glfwPollEvents();
  }

  // 8. Clean up
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);
  glfwTerminate();
}
