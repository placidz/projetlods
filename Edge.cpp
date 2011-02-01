#include "Edge.h"

Edge::Edge()
{
}

Edge::Edge(int _id, Vert *_tail, Vert *_head)
{
    this->id = _id;

    this->tail = _tail;
    this->head = _head;
    this->twin = NULL;
}

Edge::~Edge()
{
    faces.clear();
}
