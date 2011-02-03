
// ---------------------- Standard
#include <stdlib.h>
#define _USE_MATH_DEFINES 
#include <cmath>
#include <iostream>
#include <string>

// ----------------------- OpenGL & co.
#include <GL/glut.h>

// ----------------------- OpenMesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

// ------------------------------------------------------------
typedef OpenMesh::TriMesh_ArrayKernelT<> MyMesh;

// ------------------------------------------------------------

int glut_window1;

MyMesh mesh;


void initGL()
{
    glClearColor(0.8, 0.8, 0.7, 1.0);

	try
	{
		std::cout << "Enter a valid file name : ";
		std::string filename;
		std::cin >> filename;
		if (!OpenMesh::IO::read_mesh(mesh, filename))
		{
			std::cerr << "Cannot read mesh from file '\filename'" << std::endl;
		}
	}
	catch (std::exception & x)
	{
		std::cerr << x.what() << std::endl;
	}
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
