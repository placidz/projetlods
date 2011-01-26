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
    int id;
    std::list<Vert*> verts;
    std::list<Edge*> edges;
    std::list<Face*> faces;

    Mesh();

    void edgeCollapse(Edge* _edgeToDelete);
    void loadOBJ();
    void draw();
};

#endif // MESH_H
