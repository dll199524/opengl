#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const char *vertexShaderSource = 
  "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);"
  "gl_PointSize = 20.0f;"
  "}\n";

const char *fragmentShaderSource1 = 
  "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{"
  "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
  "}";

const char *fragmentShaderSource2 = 
  "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{"
  "FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);"
  "}";

/**
添加更多顶点到数据中，使用glDrawArrays，尝试绘制两个彼此相连的三角形
创建相同的两个三角形，但对它们的数据使用不同的VAO和VBO
创建两个着色器程序，第二个程序使用一个不同的片段着色器，输出黄色；再次绘制这两个三角形，让其中一个输出为黄色
 */
int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "learnopengl", nullptr, nullptr);
  if (window == nullptr)
  {
    cout << "failed to create window" << endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    cout << "failed to initialize glad" << endl;
    return -1;
  }
  glViewport(0, 0, 800, 600);
  glEnable(GL_PROGRAM_POINT_SIZE);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // 定义顶点数组
  float vertices[] = {
      // 第一个三角形
      -0.5f, 0.5f, 0.0f,
      -0.75, -0.5, 0.0f,
      -0.25, -0.5, 0.0f,

      // 第二个三角形
      0.5f, 0.5f, 0.0f,
      0.75, -0.5, 0.0f,
      0.25, -0.5, 0.0f,
  };
  unsigned int VAOS[2], VBOS[2];
  glGenVertexArrays(2, VAOS);
  glGenBuffers(2, VBOS);

  glBindVertexArray(VAOS[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOS[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAOS[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOS[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(9 * sizeof(float)));
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  unsigned int vertexShader, fragmentShader1, fragmentShader2;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
  fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);
  glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, nullptr);
  glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, nullptr);
  glCompileShader(fragmentShader1);
  glCompileShader(fragmentShader2);
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) 
  {
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    cout << "ERROR SHADER VERTEX COMPILE_FAILED\n" << endl;
  }
  glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader1, 512, nullptr, infoLog);
    cout << "ERROR SHADER FRAGMENT1 COMPILE_FAILED\n" << endl;
  }
  glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
  if (!success) 
  {
    glGetShaderInfoLog(fragmentShader2, 512, nullptr, infoLog);
    cout << "ERROR SHADER FRAGMENT2 COMPILE_FAILED\n" << endl;
  }
  unsigned int shaderProgram1, shaderProgram2;
  shaderProgram1 = glCreateProgram();
  shaderProgram2 = glCreateProgram();
  glAttachShader(shaderProgram1, vertexShader);
  glAttachShader(shaderProgram1, fragmentShader1);
  glAttachShader(shaderProgram2, fragmentShader2);
  glLinkProgram(shaderProgram1);
  glLinkProgram(shaderProgram2);
  glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shaderProgram1, 512, nullptr, infoLog);
    cout << "ERROR SHADER LINK1 PROGRAM_FAILED" << endl;
  }
  glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shaderProgram2, 512, nullptr, infoLog);
    cout << "ERROR SHADER LINK2 PROGRAM_FAILED" << endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader1);
  glDeleteShader(fragmentShader2);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  while (!glfwWindowShouldClose(window))
  {
    processInput(window);
    glClearColor(25.0 / 255.0, 25.0 / 255.0, 25.0 / 255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram1);
    glBindVertexArray(VAOS[0]);
    glDrawArrays(GL_POINTS, 0, 3);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shaderProgram2);
    glBindVertexArray(VAOS[1]);
    glDrawArrays(GL_POINTS, 0, 3);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(2, VAOS);
  glDeleteBuffers(2, VBOS);
  glDeleteProgram(shaderProgram1);
  glDeleteProgram(shaderProgram2);
  glfwTerminate();
  return 0;
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}