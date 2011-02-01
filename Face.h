#ifndef FACE_H
#define FACE_H

#include <list>

#include <Vec3.h>
#include <Edge.h>

typedef struct Face * ptrFace;

class Edge;

class Face
{
public:
    int id;

    Vec3d normal;

    std::list<Edge*> edges;

    Face();
    Face(int _id);
    ~Face();
};

#endif // FACE_H
