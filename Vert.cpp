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

void Vert::Vert(Vert* _v){
    this->id = _v->id;
    this->pos = _v->pos;
    this->color = _v->color;
    this->normal = _v->normal;
    this->tex = _v->tex;
}
