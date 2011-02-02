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

Edge::Edge(Edge* _e){
    this->id = _e->id;

    this->tail = _e->tail;
    this->head = _e->head;
    this->twin = _e->twin;
}

Edge::~Edge()
{
    faces.clear();
}
