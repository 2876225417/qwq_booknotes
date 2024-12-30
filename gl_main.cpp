#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <boost/asio.hpp>

void initOpenGL()
{
    // 打印当前 OpenGL 版本
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "OpenGL Version: " << version << std::endl;
}

int main()
{
    // 初始化 GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    // 创建窗口并设置 OpenGL 上下文
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Test", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 设置当前 OpenGL 上下文
    glfwMakeContextCurrent(window);

    // 初始化 GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW!" << std::endl;
        return -1;
    }

    // 初始化 OpenGL
    initOpenGL();

    // 使用 Boost 测试异步 IO（简单示例）
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve("www.google.com", "http");
    std::cout << "Boost ASIO resolver resolved endpoints for Google: " << std::endl;
    for (const auto& endpoint : endpoints) {
        std::cout << endpoint.endpoint() << std::endl;
    }

    // 主渲染循环
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // 交换缓冲区并轮询事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 清理并关闭窗口
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
