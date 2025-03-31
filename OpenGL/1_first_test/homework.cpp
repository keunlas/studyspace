#ifndef __glad_h_
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

#include <iostream>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

void process_input(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void init_glfw();
void init_glad();
GLFWwindow* init_main_window(int width, int height, const char* title);
void clear_screen();
unsigned int init_shader_program(float r, float g, float b, float a);

int main() {
  // Init
  init_glfw();
  GLFWwindow* window = init_main_window(WIDTH, HEIGHT, "Homework");
  init_glad();

  // Creat shader program
  unsigned int orange_shader_program =
      init_shader_program(1.0f, 0.5f, 0.2f, 1.0f);
  unsigned int yellow_shader_program =
      init_shader_program(1.0f, 1.0f, 0.0f, 1.0f);

  // ================================
  // ===========  顶点对象  ===========
  // ================================
  float orange_vertices[] = {
      0.5f,  0.5f,  0.0f,  // 右上角
      0.5f,  -0.5f, 0.0f,  // 右下角
      -0.5f, 0.5f,  0.0f   // 左上角
  };

  unsigned int orange_VBO, orange_VAO;
  glGenVertexArrays(1, &orange_VAO);
  glGenBuffers(1, &orange_VBO);

  glBindVertexArray(orange_VAO);

  glBindBuffer(GL_ARRAY_BUFFER, orange_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(orange_vertices), orange_vertices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  float yellow_vertices[] = {
      0.5f,  -0.5f, 0.0f,  // 右下角
      -0.5f, -0.5f, 0.0f,  // 左下角
      -0.5f, 0.5f,  0.0f   // 左上角
  };

  unsigned int yellow_VBO, yellow_VAO;
  glGenVertexArrays(1, &yellow_VAO);
  glGenBuffers(1, &yellow_VBO);

  glBindVertexArray(yellow_VAO);

  glBindBuffer(GL_ARRAY_BUFFER, yellow_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(yellow_vertices), yellow_vertices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  float yellow_vertices2[] = {
      0.5f, -0.5f, 0.0f,  // 右下角
      1.0f, -0.5f, 0.0f,  // 左下角
      1.0f, 0.5f,  0.0f   // 左上角
  };

  unsigned int yellow_VBO2, yellow_VAO2;
  glGenVertexArrays(1, &yellow_VAO2);
  glGenBuffers(1, &yellow_VBO2);

  glBindVertexArray(yellow_VAO2);

  glBindBuffer(GL_ARRAY_BUFFER, yellow_VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(yellow_vertices2), yellow_vertices2,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // Loop
  while (!glfwWindowShouldClose(window)) {
    process_input(window);
    clear_screen();

    // Begin Draw
    glBindVertexArray(orange_VAO);
    glUseProgram(orange_shader_program);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(yellow_VAO);
    glUseProgram(yellow_shader_program);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(yellow_VAO2);
    glUseProgram(yellow_shader_program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // End Draw

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Exit
  glfwTerminate();
  return 0;
}

unsigned int init_vertex_shader() {
  const char* vertexShaderSource =
      "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
    glfwTerminate();
    exit(-1);
  }

  return vertexShader;
}

unsigned int init_fragment_shader(float r, float g, float b, float a) {
  char* fragmentShaderSource = new char[512];
  sprintf(fragmentShaderSource,
          "#version 330 core\n"
          "out vec4 FragColor;\n"
          "void main()\n"
          "{\n"
          "  FragColor = vec4(%ff, %ff, %ff, %ff);\n"
          "}\0",
          r, g, b, a);

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  int success;
  char infoLog[512];
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
    glfwTerminate();
    exit(-1);
  }

  delete[] fragmentShaderSource;
  return fragmentShader;
}

unsigned int init_shader_program(float r, float g, float b, float a) {
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  unsigned int vertexShader = init_vertex_shader();
  unsigned int fragmentShader = init_fragment_shader(r, g, b, a);

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
    glfwTerminate();
    exit(-1);
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}

void clear_screen() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

GLFWwindow* init_main_window(int width, int height, const char* title) {
  GLFWwindow* window;
  window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!window) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(-1);
  }
  glfwMakeContextCurrent(window);
  // glViewport(0, 0, width, height);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  return window;
}

void init_glfw() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void init_glad() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwTerminate();
    exit(-1);
  }
}

void process_input(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    std::cout << "Key 'ESC' pressed!" << std::endl;
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    std::cout << "Key 'W' pressed!" << std::endl;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    std::cout << "Key 'S' pressed!" << std::endl;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    std::cout << "Key 'A' pressed!" << std::endl;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    std::cout << "Key 'D' pressed!" << std::endl;
  }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  printf("window resized: (%d, %d)\n", width, height);
  glViewport(0, 0, width, height);
}