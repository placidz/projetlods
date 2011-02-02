#ifndef VERT_H
#define VERT_H

#include <list>

#include <Vec2.h>
#include <Vec3.h>
#include <Edge.h>

typedef struct Vert * ptrVert;

class Edge;

class Vert
{
public:
    int id;

    Vec3d pos;
    Vec3d normal;
    Vec3d color;
    Vec2d tex;

    std::list<Edge*> edges;

    Vert();
    Vert(int _id);
    Vert(Vert* _v);
    ~Vert();

};

#endif // VERT_H
