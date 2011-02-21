
// ---------------------- Standard
#include <stdlib.h>
#define _USE_MATH_DEFINES 
#include <cmath>
#include <iostream>
#include <string>

// ----------------------- OpenGL & co.
#include "GL\glut.h"

// ----------------------- OpenMesh

#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
//#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/System/config.h>
#include <OpenMesh/Core/Mesh/Status.hh>

struct MyTraits : public OpenMesh::DefaultTraits
{
  VertexAttributes(OpenMesh::Attributes::Status);
  FaceAttributes(OpenMesh::Attributes::Status);
  EdgeAttributes(OpenMesh::Attributes::Status);
};

// ------------------------------------------------------------
//typedef OpenMesh::TriMesh_ArrayKernelT<> MyMesh;
typedef OpenMesh::Vec3d Point;
typedef OpenMesh::Vec3d Normal;
typedef OpenMesh::TriMesh_ArrayKernelT<MyTraits>  MyMesh;

// ------------------------------------------------------------

float valeurPropre(float a, float b, float c, float d);

int glut_window1;

MyMesh mesh;


/*
void buildTheFaces(MyMesh& _mesh, MyMesh::VertexHandle _hVert)
{
	//creer une face a partir de tous les vertex voisins du vertex que je supprime
	//retrouver cette face, la trianguler

	int i = 0;
	int nbv = 0;
	MyMesh::VertexFaceIter vf_it;
	MyMesh::FaceVertexIter fv_it;
	MyMesh::FaceHandle hF;

	for(vf_it = _mesh.vf_iter(_hVert); vf_it; ++vf_it ){
		hF = vf_it.handle();
		std::cout<<" Test i =  "<<i<<std::endl;
		i++;

		for(fv_it = _mesh.fv_iter(vf_it.handle()); fv_it; ++fv_it ){//parcours les vertex de la face
			nbv++;
		}
		std::cout<<" Nombre de vertex sur la face courante =  "<<nbv<<std::endl;
		nbv = 0;


		_mesh.triangulate(hF);
		
	}

	
}
*/

void removeThePoint(MyMesh* _mesh, MyMesh::VertexHandle _hVert)
{
	MyMesh::VertexVertexIter vv_it;
	std::vector<MyMesh::VertexHandle> lstVh;
	std::vector<MyMesh::EdgeHandle> lstEh;//liste des aretes a supprimer
	std::vector<MyMesh::VertexHandle> lstVertexSave;//liste des vertex a partir des quels on va reconstruire les faces
	MyMesh::FaceHandle hFace;
	MyMesh::VertexHandle hVertex;
	MyMesh::VertexIHalfedgeIter vhe_it;
	bool ajouter = true;
	bool vertexOk = false;


	//test
	MyMesh::FaceIter f_it;
	int nbf = 0;

	for (f_it = _mesh->faces_begin(); f_it != _mesh->faces_end(); ++f_it)
		nbf++;

	std::cout<<"Nombre de faces : "<<nbf<<std::endl;

	//Récupere le handle de tous les vertex voisins
	for(vv_it = _mesh->vv_iter(_hVert); vv_it; ++vv_it){
		lstVh.push_back(vv_it.handle());
	}

	
	//recupere l'arete entre tous les anciens voisins du point a supprimer
	for(int i = 0; i < (int)lstVh.size(); i++){
		for(vhe_it = _mesh->vih_iter(lstVh[i]); vhe_it; ++vhe_it){
			hVertex = _mesh->from_vertex_handle(vhe_it);
			for(int j = 0; j < (int)lstVh.size(); j++){
				if(i != j){//pour ne pas comparer le handle avec lui meme
					if(hVertex == lstVh[j]){
						for(int k = 0; k < (int)lstEh.size(); k++){
							if(lstEh[k] == _mesh->edge_handle(vhe_it))
								ajouter = false;
						}
						if(ajouter){
							lstEh.push_back( _mesh->edge_handle(vhe_it) );

						}
						ajouter = true;
					}
				}
			}
		}
	}


	/*
	for(int i = 0; i < (int)lstVh.size(); i++){
		for(vhe_it = _mesh->vih_iter(lstVh[i]); vhe_it; ++vhe_it){//parcours les demi aretes du vertex
			MyMesh::FaceHandle hFtmp = _mesh->face_handle(vhe_it.handle() );//recup le handle de la face a laquelle il appartient
			for(MyMesh::FaceVertexIter fv_it = _mesh->fv_iter(hFtmp); fv_it; ++fv_it){//parcours les vertex de la face
				if(fv_it.handle() == _hVert){//si le vertex a supprimer fait partie de cette face, on recupere le handle de la face opposee
					for(MyMesh::FaceVertexIter fv_it2 = _mesh->fv_iter(_mesh->opposite_face_handle(vhe_it)); fv_it2; ++fv_it2){
						bool doublon = false;
						for(int j = 0; j < (int)lstVh.size(); j++){
							if(lstVh[j] == fv_it2.handle())
								vertexOk = false;
						}
						if(vertexOk == true){
							for(int j = 0; j < (int)lstVertexSave.size(); j++){
								if(lstVertexSave[j] == fv_it2.handle())
									doublon = true;
							}
							if(doublon == false)
								lstVertexSave.push_back(fv_it2.handle() );

						}
						vertexOk = true;
					}
				}
			}
			
		}
	}
	
	for(int i = 0; i < (int)lstVh.size(); i++){
		for(MyMesh::VertexEdgeIter ve_it = _mesh->ve_iter(lstVh[i]); ve_it; ++ve_it){
			MyMesh::FaceHandle fh0(_mesh->face_handle(_mesh->halfedge_handle(ve_it.handle(), 0)));
			MyMesh::FaceHandle fh1(_mesh->face_handle(_mesh->halfedge_handle(ve_it.handle(), 1)));

			for(MyMesh::FaceVertexIter fv_it = _mesh->fv_iter(fh0); fv_it; ++fv_it){
				if(fv_it.handle() == _hVert){// si le vertex a supprimer appartient a cette face, on traite l'autre face
					for(MyMesh::FaceVertexIter fv_it2 = _mesh->fv_iter(fh1); fv_it2; ++fv_it2){//parcours la face ou on veut recuperer le vertex oppose
						bool isOk = true;

						for(int j = 0; j < (int)lstVh.size(); j++){
							if(lstVh[j] == fv_it2.handle() || _hVert == fv_it2.handle())
								isOk = false;
						}
						if(isOk == true){
							bool doublon = false;
							for(int j = 0; j < (int)lstVertexSave.size(); j++){
								if(lstVertexSave[j] == fv_it2.handle())
									doublon = true;
							}
							if(doublon == false)
								lstVertexSave.push_back(fv_it2.handle() );
						}
					}
				}
			}
			for(MyMesh::FaceVertexIter fv_it = _mesh->fv_iter(fh1); fv_it; ++fv_it){
				if(fv_it.handle() == _hVert){// si le vertex a supprimer appartient a cette face, on traite l'autre face
					for(MyMesh::FaceVertexIter fv_it2 = _mesh->fv_iter(fh0); fv_it2; ++fv_it2){//parcours la face ou on veut recuperer le vertex oppose
						bool isOk = true;

						for(int j = 0; j < (int)lstVh.size(); j++){
							if(lstVh[j] == fv_it2.handle() || _hVert == fv_it2.handle())
								isOk = false;
						}
						if(isOk == true){
							bool doublon = false;
							for(int j = 0; j < (int)lstVertexSave.size(); j++){
								if(lstVertexSave[j] == fv_it2.handle())
									doublon = true;
							}
							if(doublon == false)
								lstVertexSave.push_back(fv_it2.handle() );
						}
					}
				}
			}
		}
	}


	std::cout<<"Taille du vector = "<<lstVertexSave.size()<<std::endl;
	
	//Stocke les demi arretes des faces sauvegardees
	for(int i = 0; i < (int)lstVertexSave.size(); i++){
		std::cout<<"Valeur du vector = "<<lstVertexSave[i]<<std::endl;
	}
	

	MyMesh::Face p; 
	MyMesh::FaceHandle fh = _mesh->new_face(p);
	std::cout<<"Handle de la face = "<<fh<<std::endl;
	_mesh->set_halfedge_handle(fh, (MyMesh::HalfedgeHandle)2);
	_mesh->set_halfedge_handle(fh, (MyMesh::HalfedgeHandle)3);
	_mesh->set_halfedge_handle(fh, (MyMesh::HalfedgeHandle)4);
*/
	
	//_mesh->new_face();

	for(int i = 0; i < (int)lstEh.size(); i++)
		_mesh->delete_edge(lstEh[i]);

	
	_mesh->delete_vertex( _hVert, false );
	_mesh->garbage_collection();
	nbf = 0;
	for (f_it = _mesh->faces_begin(); f_it != _mesh->faces_end(); ++f_it)
		nbf++;
	std::cout<<"Nombre de faces avant d ajouter la nouvelle face  : "<<nbf<<std::endl;


	hFace = _mesh->add_face(lstVh);
	
	if(_mesh->is_valid_handle(hFace) )
		std::cout<<"Le handle est valide : "<<hFace<<std::endl;
	else
		std::cout<<"Le handle n est pas valide : "<<hFace<<std::endl;

	nbf = 0;
	for (f_it = _mesh->faces_begin(); f_it != _mesh->faces_end(); ++f_it)
		nbf++;
	std::cout<<"Nombre de faces apres ajout de la face, triangulée automatiquement : "<<nbf<<std::endl<<std::endl;;




	//system("PAUSE");

}



void computeSchroeder(MyMesh * _mesh)
{
	MyMesh::VertexIter v_it;
	MyMesh::VertexIHalfedgeIter vh_it;
	MyMesh::VertexFaceIter vf_it;
	bool readyToDelete = true;
	int i = 0; 


	for (v_it = _mesh->vertices_begin(); v_it != _mesh->vertices_end(); ++v_it)
	{
		//verifier que les arretes par lequelles il est relié a ses voisins ont bien toutes une twin
		// Get the vertex-face circulator of vertex _vh
		for(vh_it = _mesh->vih_iter(v_it.handle()); vh_it; ++vh_it )
		{
			if(_mesh->is_boundary(vh_it) ==  true)//si demi arrete est une bordure (pas de twin / bord du mesh)
				readyToDelete = false;
		}

		for(vf_it = _mesh->vf_iter(v_it.handle()); vf_it; ++vf_it )
		{
			i++;
		}
		std::cout<<" Nombre de faces voisines =  "<<i<<std::endl;
		i = 0;
		
		if(readyToDelete)
		{
			//for(vf_it = _mesh.vf_iter( v_it.handle() ); vf_it; ++vf_it)
				//removeTheFace(_mesh, vf_it.handle() );
			
			//faire une fonction pour verifier la distance du vertex par rapport au plan moyen
			removeThePoint(_mesh, v_it.handle() );
			
		}
		readyToDelete = true;
		

	}

}

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
	switch(_key){
	case'm':
		computeSchroeder(&mesh);
		break;
	}
	glutPostRedisplay();
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


float valeurPropre(float a, float b, float c, float d){
	
	double w, e, f, g, p, q, k, x, t, s1, s2, s3, s4, s5, s6;
	double	a = 3, 
			b = 3, 
			c = 2, 
			d = -5;

	e = b / (3 * a);
	f = c / a;
	g = d / a;
	p = f - 3 * e * e;
	q = 2 * e * e * e - e * f + g;
	k = 4 * p * p * p / 27 + q * q;
	if (abs(k) < 0.000000001)
		k = 0;
	if (k < 0){
		x = 3 * q / (2 * p) * sqrt(-3 / p);
		t = (atan(-x / sqrt(-x * x + 1)) + PI / 2) / 3;
		s1 = sqrt(-4 * p / 3) * cos(t) - e;
		s2 = sqrt(-4 * p / 3) * cos(t + 2 * PI / 3) - e;
		s3 = sqrt(-4 * p / 3) * cos(t + 4 * PI / 3) - e;
		std::cout<< " Les trois solutions sont : " << s1 << ", " << s2 << " et " << s3 << std::endl;
	}
	else if( k == 0 ){
		s4 = -e - pow( (4 * q), 1.0/3.0);
		s5 = -e + pow( (q / 2), 1.0/3.0);
		std::cout << " Les deux solutions sont : " << s4 << " et " << s5 << std::endl;
	}
	else{
		s6 = -e + pow( ((sqrt(k) - q) / 2), 1.0/3.0 ) - pow( ((sqrt(k) + q) / 2), 1.0/3.0 );
		std::cout << " La solution est : " << s6 << std::endl;
	} 
}