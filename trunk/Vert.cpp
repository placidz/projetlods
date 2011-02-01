#include "Vert.h"

Vert::Vert()
{
}

Vert::Vert(int _id)
{
    this->id = _id;

    this->pos.setZero();
    this->color.setZero();
    this->normal.setZero();
    this->tex.setZero();
}

Vert::~Vert()
{
    edges.clear();
}
