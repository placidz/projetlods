#include "Mesh.h"

/*
static int __MeshCounter__ = 0;
static int __VertCounter__ = 0;
static int __EdgeCounter__ = 0;
static int __FaceCounter__ = 0; 
*/

Mesh::Mesh()
{
}

Mesh::edgeCollapse(Edge * _edgeToDelete)
{

}

int Mesh::load(Mesh* _out, const char * _path){
        char * extension;
        FILE * file;

        __VertCounter__ = 0;
        __EdgeCounter__ = 0;
        __FaceCounter__ = 0;

        if((extension = strrchr(_path, '.')) == NULL)
                return -1;

        if((file = fopen(_path, "rb")) == NULL)
                return -1;

        /*heMesh_Clear(_out);*/
        _out->clear();

        if(strcasecmp(extension, ".obj") == 0)
        {
                if(loadOBJ(_out, file) == 1)
                {
                        fclose(file);

                        /*heMesh_Clear(_out);*/
                        _out->clear();
                        return -1;
                }

                fclose(file);
                return 0;
        }

        fclose(file);
        return -1;
}

int Mesh::loadOBJ(Mesh* _out, FILE * _file){
	char                    buf[512], * c;
    int                     i, err, v, n, t;
    int                     nv, nf, nt;
    /*hePtrList               edges;
    hePtrListItem   it;
    heList                  face;
    hePtrVert *             currentV;
    hePtrFace *             currentF;
    mlVec2 *                texes;*/
    list<edge*> lstEdge; // == edges
    list<edge*>::iterator it;
    list<face> lstFace;
    Vert* currentV;
    Face* currentF;
    Vec3d* texes;

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

    /*_out->verts  = (hePtrVert *)malloc(sizeof(hePtrVert) * nv);
    _out->faces  = (hePtrFace *)malloc(sizeof(hePtrFace) * nf);
    texes            = (mlVec2 *)malloc(sizeof(mlVec2) * nt);
    edges            = heList_New();
    */
    _out->verts = new Vert();
    _out->faces = new Face();
    texes = new Vec3d();
    //lstEdge => edges = heList_New();

    _out->nVerts = nv;
    _out->nFaces = nf;
    currentV = _out->verts;
    currentF = _out->faces;
    nt = 0;

    /*heList_Init(&face);*/ //pas besoin d'initialiser

    rewind(_file);
    while(fgets(buf, sizeof(buf), _file) != NULL)
    {
            if(buf[0] == 'v')
            {
                    if(buf[1] == ' ' || buf[1] == '\t')
                    {
                            *currentV = heVert_New(__VertCounter__++); //ou new Vert(__VertCounter__++) ?

                            if(sscanf(buf + 1, "%lf %lf %lf", &(*currentV)->pos[0], &(*currentV)->pos[1], &(*currentV)->pos[2]) != 3)
                                    return -1;

                            ++currentV; //Bizarre
                    }
                    else if(buf[1] == 't')
                    {
                            if(sscanf(buf + 2, "%lf %lf", &texes[nt][0], &texes[nt][1]) != 2)
                                    return -1;

                            ++nt;
                    }
            }
            else if(buf[0] == 'f')
            {
                    /*heList_Clear(&face);*/
                    lstFace.clear();


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
                                            v += _out->nVerts;
                                    else
                                            --v;

                                    /*mlVec2_Copy(_out->verts[v]->tex, texes[t - 1]);*/
                                    mlVec3d_Copy(_out->verts[v]->tex, texes[t - 1]);
                            }
                            else if(sscanf(c, " %d", &v) == 1 || sscanf(c, " %d//%d", &v, &n) == 2)
                            {
                                    err = 0;

                                    if (v < 0)
                                            v += _out->nVerts;
                                    else
                                            --v;
                            }

                            if(err == 0)
                                /*heList_Push_Back(&face, _out->verts[v]);*/
                                lstFace.push_back(_out->verts[v]);

                    }

                    /*if((*currentF = __heFace_Build__(&face, edges)) == NULL)*/
                    if((*currentF = face_Build(&lstFace, lstEdge)) == NULL)
                            return -1;

                    ++currentF;
            }
    }

    /*_out->nEdges = edges->size;*/
    _out->nEdges = (int)lstEdge.size();
    /*_out->edges  = (hePtrEdge *)malloc(sizeof(hePtrEdge) * edges->size);*/
    _out->Edges = new Edges();

    /*for(i = 0, it = edges->head; it != NULL; it = it->next, ++i)*/
    for(i = 0, it = lstEdges.begin(); it != lstEdges.end(); it++, ++i)
            /*_out->edges[i] = (hePtrEdge)it->data;*/
            _out->edges[i] = it;

    /*free(texes);*/
    //heList_Free(&edges);
    return 0;
}

Mesh::draw()
{

}
 

//A verifier
/*hePtrListItem heList_Find_Data(hePtrList _out, ptrVoid _data, int (*_compare)(ptrVoid _a, ptrVoid _b))*/
Vert* Mesh::list_Find_Data(list<Edges*> _out, Vert* _data){
    /*hePtrListItem it;*/
	list<Edges*>::iterator it;
        
    /*for(it = _out->head; it != NULL; it = it->next)*/
	for(it = _out.begin(); it != _out.end(); it++)
    {
        /*if((*_compare)(it->data, _data) == 0)*/
		if(it->data == _data)//suppose que it->data pointe sur un vertex
                return it;
    }
        
    return NULL;
}



/*hePtrFace __heFace_Build__(hePtrList _verts, hePtrList _edges)*/
Face* Mesh::face_Build(list<Vert*> _lstVerts, list<Edge*> _lstEdges){
        /*hePtrFace         out;
        hePtrEdge         e;

        hePtrListItem it, itf;
        hePtrVert         vh, vt;*/
        Face* out;
        Edge* e;
        list<Edge*>::iterator it;
        list<Face*>::iterator itf;
        Vert* vh, vt;

        if(_lstVerts->size < 3)
                return NULL;

        out = heFace_New(__heFaceCounter__++);

        /*heList_Init(&out->edges);*/
		//Rien
        mlVec3_Zero(out->normal);
		

        /*for(it = _verts->head; it != NULL; it = it->next)*/
        for(it = _lstVerts->begin(); it != _lstVerts->end(); it++)
        {
                /*vt = (hePtrVert)it->data;*/
                vt = it->data; //ou juste it ?

                /*if(it->next == NULL)*/
                if(it == _lstVerts->end())
                        /*vh = (hePtrVert)_verts->head->data;*/
                        vh = _lstVerts->head->data;
                else
                        /*vh = (hePtrVert)it->next->data;*/
                        vh = it->next->data;

                /*itf = heList_Find_Data(&vt->edges, vh, __heEdge_Find_Edge__);*/
				itf = list_Find_Data(&vt->edges, vh);// suppose que &vt->edges est une list<Edges*>

                if(itf == NULL)
                {
                        /*e  = heEdge_New(__heEdgeCounter__++, vh, vt);*/
						e  = new Edge(__heEdgeCounter__++, vh, vt);
                        /*heList_Push_Back(_edges, e);*/
                        lstEdges.push_back(e);
                        /*heList_Push_Back(&vh->edges, e);*/
                        &vh->edges.push_back(e);

                        e->twin = new Edge(__heEdgeCounter__++, vt, vh);
                        e->twin->twin = e;//semble ok
                        e = e->twin;//semble ok

                        /*heList_Push_Back(_edges, e);*/
                        lstEdges.push_back(e);
                        /*heList_Push_Back(&vt->edges, e);*/
                        &vt->edges.push_back(e);
                }
                else
                {
                        /*e = (hePtrEdge)itf->data;*/
                        e = itf->data;// ou juste itf?
                }

                /*heList_Push_Back(&out->edges, e);
                heList_Push_Back(&e->faces, out);*/
                &out->edges.push_back(e);
                &e->faces.push_back(out);
        }

        return out;
}




