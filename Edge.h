#ifndef EDGE_H
#define EDGE_H

#include <list>

#include "Vert.h"
#include "Face.h"

typedef struct Edge * ptrEdge;

class Edge
{
public:
    int id;

    Vert* head;
    Vert* tail;
    Edge* twin;

    std::list<Face*> faces;

    Edge();
    Edge(int _id, Vert* _tail, Vert* _head);
    ~Edge();
};

#endif // EDGE_H
