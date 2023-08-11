#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);


int main()
{
  glfwInit();
  //version 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //core profile 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  //create window
  GLFWwindow *window = glfwCreateWindow(800, 600, "learnopengl", NULL, NULL);
  if (window == nullptr) 
  {
    cout << "failed to create glfw window" << endl;
    glfwTerminate();
    return -1;
  }
  //通知GLFW将我们窗口的上下文设置为当前线程的主上下文
  glfwMakeContextCurrent(window);
  //初始化管理OpenGL的函数指针
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    cout << "create glad failed" << endl;
    return -1;
  }
  //设置视口
  glViewport(0, 0, 800, 600);
  // 注册窗口变化监听
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  while (!glfwWindowShouldClose(window))
  {
    processInput(window);
    //渲染指令
    glClearColor(25.0 / 255.0, 25.0 / 255.0, 25.0 / 255.0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    //交换颜色缓冲
    glfwSwapBuffers(window);
    //交换颜色缓冲
    glfwPollEvents();
  }
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
  {
    glfwSetWindowShouldClose(window, true);
  }
}