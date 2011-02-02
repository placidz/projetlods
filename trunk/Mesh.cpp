#include "Mesh.h"


static int __MeshCounter__ = 0;
static int __VertCounter__ = 0;
static int __EdgeCounter__ = 0;
static int __FaceCounter__ = 0; 


Mesh::Mesh()
{
    this->id = __MeshCounter__++;
}

void Mesh::clear()
{
    this->verts.clear();
    this->edges.clear();
    this->faces.clear();

    __VertCounter__ = 0;
    __EdgeCounter__ = 0;
    __FaceCounter__ = 0;
}

void Mesh::edgeCollapse(Edge * _edgeToDelete)
{

}

int Mesh::load(const char * _path)
{
    char * extension;
    FILE * file;

    __VertCounter__ = 0;
    __EdgeCounter__ = 0;
    __FaceCounter__ = 0;

    if((extension = strrchr(_path, '.')) == NULL)
        return -1;

    if((file = fopen(_path, "rb")) == NULL)
        return -1;

    this->clear();

    if(strcasecmp(extension, ".obj") == 0)
    {
        if(loadOBJ(file) == 1)
        {
            fclose(file);

            this->clear();

            return -1;
        }

        fclose(file);
        return 0;
    }

    fclose(file);
    return -1;
}

int Mesh::loadOBJ(FILE *_file)
{
    char			buf[512], * c;
    int				/*i,*/ err, v, n, t;
    int 			nv, nf, nt;

    //hePtrList		edges;
    //hePtrListItem	it;
    //heList			face;
    std::list<Vert*> face;
    //hePtrVert *		currentV;
    ptrVert currentV;
    //hePtrFace *		currentF;
    ptrFace * currentF;
    //mlVec2 *		texes;
    Vec2d * texes;

    nv = 0;
    nf = 0;
    nt = 0;

    rewind(_file);
    while(fgets(buf, sizeof(buf), _file) != NULL)
    {
        if(buf[0] == 'v')
        {
            if(buf[1] == ' ' || buf[1] == '\t')
                ++nv;
            else if(buf[1] == 't')
                ++nt;
        }
        else if(buf[0] == 'f')
        {
            if(buf[1] == ' ' || buf[1] == '\t')
                ++nf;
        }
    }

    //_out->verts  = (hePtrVert *)malloc(sizeof(hePtrVert) * nv);
    //_out->faces  = (hePtrFace *)malloc(sizeof(hePtrFace) * nf);
    //texes		 = (mlVec2 *)malloc(sizeof(mlVec2) * nt);
    texes = new Vec2d[nt];
    //edges		 = heList_New();
    //_out->nVerts = nv;
    //_out->nFaces = nf;
    //currentV	 = _out->verts;
    //currentF	 = _out->faces;
    nt			 = 0;

    //heList_Init(&face);

    rewind(_file);
    while(fgets(buf, sizeof(buf), _file) != NULL)
    {
        if(buf[0] == 'v')
        {
            if(buf[1] == ' ' || buf[1] == '\t')
            {

                //*currentV = heVert_New(__heVertCounter__++);
                currentV = new Vert(__VertCounter__++);

                if(sscanf(buf + 1, "%lf %lf %lf", &(currentV)->pos.toArray()[0], &(currentV)->pos.toArray()[1], &(currentV)->pos.toArray()[2]) != 3)
                    return -1;

                //++currentV;
                verts.push_back(currentV);
            }
            else if(buf[1] == 't')
            {
                if(sscanf(buf + 2, "%lf %lf", &texes[nt].toArray()[0], &texes[nt].toArray()[1]) != 2)
                    return -1;

                ++nt;
            }
        }
        else if(buf[0] == 'f')
        {
            //heList_Clear(&face);
            face.clear();

            c = buf;
            err = 0;

            while(err == 0)
            {
                while(*c && *c != '\n' && !isspace(*c))
                    c++;

                while(*c && isspace(*c))
                    c++;

                err = 1;
                if(sscanf(c, " %d/%d", &v, &t) == 2 || sscanf(c, " %d/%d/%d", &v, &t, &n) == 3)
                {
                    err = 0;

                    if (v < 0)
                        //v += _out->nVerts;
                        v += this->verts.size();
                    else
                        --v;

                    //mlVec2_Copy(_out->verts[v]->tex, texes[t - 1]);
                    std::list<Vert*>::iterator itv = this->verts.begin();
                    std::advance(itv, v);
                    (*itv)->tex.set(texes[t - 1]);
                }
                else if(sscanf(c, " %d", &v) == 1 || sscanf(c, " %d//%d", &v, &n) == 2)
                {
                    err = 0;

                    if (v < 0)
                        //v += _out->nVerts;
                        v += this->verts.size();
                    else
                        --v;
                }

                if(err == 0)
                {
                    //heList_Push_Back(&face, _out->verts[v]);
                    std::list<Vert*>::iterator itv = this->verts.begin();
                    std::advance(itv, v);
                    face.push_back(*itv);
                }
            }

            if((*currentF = face_Build(face, edges)) == NULL)
                return -1;

            ++currentF;
        }
    }

    //_out->nEdges = edges->size;
    //_out->edges  = (hePtrEdge *)malloc(sizeof(hePtrEdge) * edges->size);
/*
    for(i = 0, it = edges->head; it != NULL; it = it->next, ++i)
        this->edges[i] = (hePtrEdge)it->data;

    free(texes);
    //heList_Free(&edges);
    edges.clear();
*/
    return 0;
}

void Mesh::draw()
{

}


//A verifier
/*hePtrListItem heList_Find_Data(hePtrList _out, ptrVoid _data, int (*_compare)(ptrVoid _a, ptrVoid _b))*/
Edge* Mesh::list_Find_Data(std::list<Edge*> _out, Vert* _data)
{
    /*hePtrListItem it;*/
    std::list<Edge*>::iterator it;

    /*for(it = _out->head; it != NULL; it = it->next)*/
    for(it = _out.begin(); it != _out.end(); it++)
    {

        /*if((*_compare)(it->data, _data) == 0)*/
        if((*it)->head == _data)
            return (*it);
    }

    return NULL;
}



/*hePtrFace __heFace_Build__(hePtrList _verts, hePtrList _edges)*/
Face* Mesh::face_Build(std::list<Vert*> _lstVerts, std::list<Edge*> _lstEdges)
{
    /*hePtrFace         out;
        hePtrEdge         e;

        hePtrListItem it, itf;
        hePtrVert         vh, vt;*/
    Face* out;
    Edge* e;
    std::list<Vert*>::iterator it;
    //std::list<Edge*>::iterator itf;
    Edge* itf;
    Vert * vh;
    Vert * vt;

    if(_lstVerts.size() < 3)
        return NULL;

    //out = heFace_New(__heFaceCounter__++);
    out = new Face(__FaceCounter__++);

    /*heList_Init(&out->edges);*/
    //Rien
    //mlVec3_Zero(out->normal); //de base dans le constructeur


    /*for(it = _verts->head; it != NULL; it = it->next)*/
    for(it = _lstVerts.begin(); it != _lstVerts.end(); it++)
    {
        /*vt = (hePtrVert)it->data;*/
        vt = new Vert(*it); //copie les données de it dans vt

        /*if(it->next == NULL)*/
        //if(it == _lstVerts.end())
            /*vh = (hePtrVert)_verts->head->data;*/
            //vh->set(*it);
        //else
            /*vh = (hePtrVert)it->next->data;*/
            //vh = it->next->data;
            vh = new Vert(*it);

        /*itf = heList_Find_Data(&vt->edges, vh, __heEdge_Find_Edge__);*/
        itf = new Edge(list_Find_Data(vt->edges, vh));// suppose que &vt->edges est une list<Edges*>

        if(itf == NULL)
        {
            /*e  = heEdge_New(__heEdgeCounter__++, vh, vt);*/
            e  = new Edge(__EdgeCounter__++, vh, vt);
            /*heList_Push_Back(_edges, e);*/
            _lstEdges.push_back(e);
            /*heList_Push_Back(&vh->edges, e);*/
            vh->edges.push_back(e);

            e->twin = new Edge(__EdgeCounter__++, vt, vh);
            e->twin->twin = e;//semble ok
            e = e->twin;//semble ok

            /*heList_Push_Back(_edges, e);*/
            _lstEdges.push_back(e);
            /*heList_Push_Back(&vt->edges, e);*/
            vt->edges.push_back(e);
        }
        else
        {
            /*e = (hePtrEdge)itf->data;*/
            e  = new Edge(itf);
        }

        /*heList_Push_Back(&out->edges, e);
                heList_Push_Back(&e->faces, out);*/
        out->edges.push_back(e);
        e->faces.push_back(out);
    }

    return out;
}




