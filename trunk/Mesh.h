#ifndef MESH_H
#define MESH_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <list>

#include <Edge.h>
#include <Vert.h>
#include <Face.h>

typedef struct Mesh * ptrMesh;

class Mesh
{
public:
    int id;
    std::list<Vert*> verts;
    std::list<Edge*> edges;
    std::list<Face*> faces;

    Mesh();

    void clear();
    void edgeCollapse(Edge* _edgeToDelete);
    int load(const char * _path);
    int loadOBJ(FILE * _file);
    Vert* list_Find_Data(std::list<Edge*> _out, Vert* _data);
    Face* face_Build(std::list<Vert*> _lstVerts, std::list<Edge*> _lstEdges);
    void draw();
};

#endif // MESH_H
