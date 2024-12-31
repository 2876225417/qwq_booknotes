#include <GL/glut.h>
#include <cmath>

#define X_begin  3.14f * 8
#define X_end   -3.14f * 8
#define Y_begin  1.f   * 8
#define Y_end   -1.f   * 8

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
    for (float x = -12.56f; x <= 12.56f; x += 0.01f) {
        float y = sin(51 * x) / 51;
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
