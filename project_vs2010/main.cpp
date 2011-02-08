
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
typedef OpenMesh::Vec3d Point;
typedef OpenMesh::Vec3d Normal;

// ------------------------------------------------------------

int glut_window1;

MyMesh mesh;


void drawBase()
{
	glDisable(GL_LIGHTING);

	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(1.0, 0.0, 0.0);
	glEnd();

	glColor3ub(0, 255, 0);
	glBegin(GL_LINES);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 1.0, 0.0);
	glEnd();

	glColor3ub(0, 0, 255);
	glBegin(GL_LINES);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 1.0);
	glEnd();

	glEnable(GL_LIGHTING);
	glColor3ub(255, 255, 255);
}

void drawMesh(MyMesh _mesh)
{
	MyMesh::FaceIter f_it;
	MyMesh::FaceVertexIter fv_it;
	Point point;
	Point normal;
	//glPointSize(5.0);
	//glColor3ub(255, 0, 0);
	for (f_it = _mesh.faces_begin(); f_it != _mesh.faces_end(); ++f_it)
	{
		glBegin(GL_TRIANGLES);
		for (fv_it = _mesh.fv_begin(f_it.handle()); fv_it; ++fv_it)
		{		
			point = _mesh.point(fv_it);
			normal = _mesh.normal(fv_it);
			//glVertex3d(point[0], point[1], point[2]);
			glNormal3dv(normal.data());
			glVertex3dv(point.data());	
		}
		glEnd();
	}
}

void initGL()
{
    glClearColor(0.8, 0.8, 0.7, 1.0);
	GLfloat mat_specular   [4] = { 0.18, 0.18, 0.18, 0.18 };
    GLfloat mat_shininess  [ ] = { 128 };
    GLfloat global_ambient [ ] = { 0.02, 0.02, 0.05, 0.05 };
    GLfloat light0_ambient [ ] = { 0, 0, 0, 0 };
    GLfloat light0_diffuse [ ] = { 0.85, 0.85, 0.8, 0.85 };
    GLfloat light0_specular[ ] = { 0.85, 0.85, 0.15, 0.85 };

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);

	try
	{
		std::string filename = "bunny.obj";
		//std::cout << "Enter a valid file name : ";
		//std::cin >> filename;
		mesh.request_vertex_normals();
		mesh.request_face_normals();
		OpenMesh::IO::Options opt;
		if (!OpenMesh::IO::read_mesh(mesh, filename, opt))
		{
			std::cerr << "Cannot read mesh from file '<< filename <<'" << std::endl;
		}
		if (!opt.check(OpenMesh::IO::Options::VertexNormal) && mesh.has_face_normals() && mesh.has_vertex_normals())
		{
			mesh.update_normals();
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
	drawBase();
	drawMesh(mesh);
    glutSwapBuffers();
}

void callback_resize(int _width, int _height)
{
	glViewport(0, 0, _width, _height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)_width/(GLfloat)_height, 0.01, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.1, 0.0, 1.0, 0.0);

	glutPostRedisplay();
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

	return EXIT_SUCCESS;
}
