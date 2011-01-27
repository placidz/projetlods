#include <stdlib.h>
#include <iostream>

#include <windows.h>
#include <GL/glut.h>

#include "Vec3.h"



int glut_window1;

void initGL()
{
    glClearColor(0.8, 0.8, 0.7, 1.0);
}

void callback_display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}

void callback_resize(int _width, int _height)
{

}

void callback_keyboard(unsigned char _key, int _x, int _y)
{

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    Vec3d vec1 = Vec3d(0.0, 0.0, 0.0);
    Vec3d vec2 = Vec3d(1.0, 1.0, 0.0);

    std::cout<<distance(vec1, vec2)<<std::endl;


    glutInitWindowSize(600, 600);
    glutInitWindowPosition(200, 100);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glut_window1 = glutCreateWindow("Renderer");
    glutDisplayFunc(callback_display);
    glutReshapeFunc(callback_resize);
    glutKeyboardFunc(callback_keyboard);

    initGL();

    glutMainLoop();

    return 0;
}
