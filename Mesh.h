#ifndef MESH_H
#define MESH_H

#include <list>
#include "Vec3.h"

typedef struct _Vert    Vert;
typedef struct _Vert *  ptrVert;

typedef struct _Edge    Edge;
typedef struct _Edge *  ptrEdge;

typedef struct _Face    Face;
typedef struct _Face *  ptrFace;

struct _Vert
{
    int id;

    Vec3d pos;
    Vec3d normal;
    Vec3d color;

    std::list<Edge*> edges;
};

struct _Edge
{
    int id;

    Vert* head;
    Vert* tail;
    Edge* twin;

    std::list<Face*> faces;
};

struct _Face
{
    int id;

    Vec3d normal;

    std::list<Edge*> edges;
};

class Mesh
{
	

public:
	static int __MeshCounter__ = 0;
	static int __VertCounter__ = 0;
	static int __EdgeCounter__ = 0;
	static int __FaceCounter__ = 0;

    int id;
    std::list<Vert*> verts;
    std::list<Edge*> edges;
    std::list<Face*> faces;

    Mesh();

    void edgeCollapse(Edge* _edgeToDelete);
	int load(Mesh* _out, const char * _path);
    void loadOBJ(Mesh* _out, FILE * _file);
	Vert* list_Find_Data(list<Edges*> _out, Vert* _data);
	Face* face_Build(list<Vert*> _lstVerts, list<Edge*> _lstEdges);
    void draw();
};

#endif // MESH_H
