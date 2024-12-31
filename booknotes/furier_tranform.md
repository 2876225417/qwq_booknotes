
# 傅里叶变换


**时域**是惟一客观存在的域，**频域**是一种遵循特定规则的数学范畴。

任何周期函数都可以看作是不同振幅，不同相位**正弦波**的叠加。

傅里叶变换将**时域**和**频域**连接了起来。

用来绘制三角函数图像的函数(`glut` of `OpenGL`)：
```C++
#include <GL/glut.h>
#include <cmath>

#define X_begin  3.14f
#define X_end   -3.14f
#define Y_begin  1.f
#define Y_end   -1.f

void draw_axes() {
    glBegin(GL_LINES);
    glVertex2f(X_begin, 0.f);    
    glVertex2f(X_end, 0.f);     
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.f, Y_begin);      
    glVertex2f(0.f, Y_end);
    glEnd();
}

void draw_sine() {
    glBegin(GL_LINE_STRIP); 
    for (float x = -3.14f; x <= 3.14f; x += 0.01f) {
        float y = sin(x); 
        glVertex2f(x, y);  
    }
    glEnd();
}

// 初始化
void initOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    
    glClear(GL_COLOR_BUFFER_BIT);            
    glLoadIdentity();                        
    glMatrixMode(GL_PROJECTION);             
    glLoadIdentity();                        
    gluOrtho2D( X_begin
              , X_end
              , Y_begin
              , Y_end
              ); // 二维正交投影
}

// 渲染
void display() {
    glClear(GL_COLOR_BUFFER_BIT); 

    draw_axes();
    draw_sine();             
 
    glFlush();                    
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
    glutInitWindowSize(500, 500);               
    glutCreateWindow("Sine Wave");              
    initOpenGL();                               
    glutDisplayFunc(display);                   
    glutMainLoop();                             

    return 0;
}

```
$$
f(x) = sin(x)
$$
图像：
![alt text](image.png)

$$
f(x) = sin(x) + 0.333sin(3x)
$$

图像：
![alt text](image-2.png)

$$
f(x) = \frac{\sin(x)}{1} + \frac{\sin(3x)}{3} + \frac{sin(5x)}{5} 
$$

图像：
![alt text](image-3.png)

$$
f(x) = \frac{\sin(x)}{1} + \frac{\sin(3x)}{3} + \frac{\sin(5x)}{5} + \frac{\sin(7x)}{7}
$$

图像：
![alt text](image-4.png)

以此类推其他的正弦波叠加的情况：
$$
f(x) = \sum_{n=1}^{\infin} \frac{\sin(nx)}{n}
$$

其中

