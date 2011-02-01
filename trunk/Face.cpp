#include "Face.h"

Face::Face()
{
}

Face::Face(int _id)
{
    this->id = _id;

    this->normal.setZero();
}

Face::~Face()
{
    edges.clear();
}
