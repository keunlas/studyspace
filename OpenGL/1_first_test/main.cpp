#ifndef __glad_h_
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

#include <iostream>

void processInput(GLFWwindow* window) {
  // 使用 GLFW 的 glfwGetKey 函数，它需要一个窗口以及一个按键作为输入
  // 这个函数将会返回这个按键是否正在被按下
  // 如果没有按下，glfwGetKey 将会返回 GLFW_RELEASE
  // 如果按下，glfwGetKey 将会返回 GLFW_PRESS
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    std::cout << "Key 'ESC' pressed!" << std::endl;

    // glfwSetWindowShouldClose 函数会通知 GLFW 该关闭了
    // WindowShouldClose 属性将被设置为 true 来关闭GLFW
    // 下一次循环的 glfwWindowShouldClose 函数将会返回 true
    glfwSetWindowShouldClose(window, true);
  }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  std::cout << "width: " << width << " height: " << height << std::endl;
  glViewport(0, 0, width, height);
}

int main() {
  // 初始化 glfw
  glfwInit();

  // 设置需要的 glfw 版本至少为 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // 设置 glfw 使用核心模式 core profile
  // 这意味着我们只能使用 OpenGL 功能的一个子集
  // 即不使用那些已经被废弃的向后兼容特性
  // “向后兼容特性”指的是那些为了兼容旧版本OpenGL而保留的特性
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // 如果你使用 MAC OS X 系统，需要加上下面这行代码
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // 创建一个窗口对象 前三个参数为窗口的宽高和标题
  GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // 将窗口的上下文设置为当前线程的主上下文
  glfwMakeContextCurrent(window);

  // 初始化 GLAD
  // GLAD 是用来管理 OpenGL 的函数指针的
  // 所以在调用任何 OpenGL 的函数之前我们需要初始化 GLAD
  // 给 GLAD 传入了用来加载系统相关的 OpenGL 函数指针地址的函数
  // GLFW 给我们的是 glfwGetProcAddress 函数
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // 调用 glViewport 函数来设置视口的尺寸
  // 前两个参数控制窗口左下角的位置
  // 第三个和第四个参数控制渲染窗口的宽度和高度（像素）
  glViewport(0, 0, 800, 600);

  // 注册一个回调函数，当窗口大小改变时调用
  // 这个帧缓冲大小函数需要一个GLFWwindow作为它的第一个参数
  // 以及两个整数表示窗口的新尺寸
  // 每当窗口改变大小，GLFW 会调用这个函数并填充相应的参数
  // 通过 glfwSetFramebufferSizeCallback 注册这个函数
  // 告诉 GLFW 我们希望每当窗口调整大小的时候调用这个函数
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // 渲染循环
  // glfwWindowShouldClose 函数在我们每次循环的开始前
  // 检查一次GLFW是否被要求退出，如果是的话，该函数返回true
  while (!glfwWindowShouldClose(window)) {
    // 创建一个 processInput 函数来处理输入
    // 让所有的输入代码保持整洁
    processInput(window);

    // 渲染指令
    // 我们可以通过调用 glClear 函数来清空屏幕的颜色缓冲
    // 它接受一个缓冲位 (Bit) 来指定要清空的缓冲
    // 可能的缓冲位有
    // GL_COLOR_BUFFER_BIT
    // GL_DEPTH_BUFFER_BIT
    // GL_STENCIL_BUFFER_BIT
    // 由于现在我们只关心颜色值，所以我们只清空颜色缓冲
    // 清空颜色缓冲后，整个颜色缓冲都会被填充为 glClearColor 里所设置的颜色
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // glfwSwapBuffers 函数会交换颜色缓冲
    // 它是一个储存着GLFW窗口每一个像素颜色值的大缓冲
    // 它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
    glfwSwapBuffers(window);

    // glfwPollEvents 函数检查有没有触发什么事件 (键盘输入、鼠标移动等)
    // 更新窗口状态并调用对应的回调函数 (可以通过回调方法手动设置)
    glfwPollEvents();
  }

  // 调用 glfwTerminate 函数
  // 释放或者删除之前的分配的所有资源
  glfwTerminate();
  return 0;
}
