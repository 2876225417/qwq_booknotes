#include <GL/glut.h>
#include <cmath>

// 绘制正弦函数图像
void drawSineWave() {
    glBegin(GL_LINE_STRIP); // 使用 GL_LINE_STRIP 来绘制一系列连接的线段
    for (float x = -3.14f; x <= 3.14f; x += 0.01f) {
        float y = sin(x); // 计算正弦值
        glVertex2f(x, y);  // 设置顶点 (x, y)
    }
    glEnd();
}

// 初始化 OpenGL 设置
void initOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // 设置背景色为黑色
    glClear(GL_COLOR_BUFFER_BIT);            // 清除颜色缓存
    glLoadIdentity();                        // 重置模型视图矩阵
    glMatrixMode(GL_PROJECTION);             // 设置投影矩阵
    glLoadIdentity();                        // 重置投影矩阵
    gluOrtho2D(-3.14, 3.14, -1.5, 1.5);      // 设置二维正交投影
}

// 渲染函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // 清除颜色缓存
    drawSineWave();               // 绘制正弦波
    glFlush();                    // 强制执行所有 OpenGL 命令
    glutSwapBuffers();            // 交换前后缓冲区，进行双缓冲显示
}

// 主函数
int main(int argc, char** argv) {
    glutInit(&argc, argv);                     // 初始化 GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // 设置显示模式为双缓冲和 RGB
    glutInitWindowSize(500, 500);               // 设置窗口大小
    glutCreateWindow("Sine Wave");              // 创建窗口
    initOpenGL();                               // 初始化 OpenGL 设置
    glutDisplayFunc(display);                   // 设置渲染回调函数
    glutMainLoop();                             // 进入 GLUT 主循环
    return 0;
}
