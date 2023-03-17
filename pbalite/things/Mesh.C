#include "Mesh.h"
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>



using namespace pba;
using namespace std;

void Mesh::Display()
{
    glPointSize(3.0);
	glBegin(GL_POINTS);
	for(size_t i=0; i<particles.size();i++)
	{
//    	if (i == 0)
//        	cout << "DISPLAY Y POSITION" << particles[i].position.Y() << "\n";
    	const Vector& P = particles[i].position;
    	const Color& ci = particles[i].color;
        glColor3f( ci.red(), ci.green(), ci.blue() );
        glVertex3f( P.X(), P.Y(), P.Z() );
	}
	glEnd();

	glBegin(GL_LINES);
	for(size_t i=0; i<edges.size();i++)
	{
    	//cout << "A:" << edges[i].a << "  B:"<<edges[i].b<<"\n";
    	const Vector& A = edges[i].a->position;
    	const Vector& B = edges[i].b->position;
    	const Color& ci = edges[i].color;
        glColor3f( ci.red(), ci.green(), ci.blue() );
        glVertex3f( A.X(), A.Y(), A.Z() );
        glVertex3f( B.X(), B.Y(), B.Z() );
	}
	glEnd();

}

struct TriangleIndices {
    // define indices of points into mesh.particles in a triangle
    size_t a, b, c;
};

void Mesh::LoadMesh(const char* model)
{
    //cout <<"loading model "<< model<< " ...\n";

    std::vector<unsigned int> vertexIndices;
    std::vector<TriangleIndices> triangles;
    std::vector<Vector> temp_vertices;

    FILE * file = fopen(model, "r");
    if (file == NULL){
        //cout << "CAN'T OPEN FILE\n";
        throw invalid_argument("Invalid filename for model\n");
    }

    while (true)
    {
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF){
            break;
        }
        else
        {
            if ( strcmp(lineHeader, "v") == 0){
                float x, y, z;
                if (fscanf(file, "%f %f %f\n", &x, &y, &z) == 0){
                    //cout << "matching failure\n";
                }
                else{
                    Vector vertex = Vector(x, y, z);
                    temp_vertices.push_back(vertex);
                }
            }
            if ( strcmp(lineHeader, "f") == 0){
                size_t vertexIndex[3];
                int matches = fscanf(file, "%ld %ld %ld\n", &vertexIndex[0],  &vertexIndex[1],  &vertexIndex[2]);
                if (matches < 3){
                    //cout << "matching failure\n";
                }
                triangles.push_back({--vertexIndex[0],--vertexIndex[1],--vertexIndex[2]});
            }
        }
    }

	particles.resize(particles.size()+temp_vertices.size());
	Vector v = Vector(0,0,0); 
//	Vector v = Vector(drand48(),drand48(),drand48());
//
    // update particle data
    //cout <<"storing particle data...\n";
    //cout << posOffset.X() << " "<< posOffset.Y() << " "<< posOffset.Z() << "\n";
    for (size_t i=0;i<particles.size();i++)
    {
        particles[i].position = temp_vertices[i] + posOffset;

        particles[i].color = Color(.5,.5,.5,0);
        particles[i].velocity = v;
        particles[i].assignID(i);
    }
    //cout <<"# of particles: "<<particles.size()<< "\n";
    //cout <<"loading edges...\n";
    for (size_t i=0; i<triangles.size();i++)
    {
        ////cout << "triangle a index:"<< triangles[i].a << "\n";
        Color triColor = Color(drand48(),drand48(),drand48(), 0);
        edges.push_back(Edge(&particles[triangles[i].a], &particles[triangles[i].b], triColor));
        edges.push_back(Edge(&particles[triangles[i].a], &particles[triangles[i].c], triColor));
        edges.push_back(Edge(&particles[triangles[i].b], &particles[triangles[i].c], triColor));
    }
    //cout <<"# of edges: "<<edges.size()<< "\n";

    // create softTriangle vector
    cout <<"loading softTriangles...\n";
    for (size_t i=0; i<triangles.size();i++)
    {
        softTris.push_back(SoftTriangle(&particles[triangles[i].a], &particles[triangles[i].b], &particles[triangles[i].c]));
    }
    cout <<"# of triangles: "<<softTris.size()<< "\n";
    // add connections to particles
    //cout <<"adding connections to particles...\n";
    int connections = 0;
    for (size_t i=0;i<particles.size();i++)
    {
        for (size_t j=0;j<edges.size();j++)
        {
            ////cout << i << "  " << edges[j].a->ID()<< ":" << edges[j].b->ID()<<"\n";
            if (edges[j].a->ID() == i)
            {
                particles[i].connections.push_back(&edges[j]);
                connections++;
            }
            else if (edges[j].b->ID() == i)
            {
                particles[i].connections.push_back(&edges[j]);
                connections++;
            }
        }
    }
    //cout << "# of connections: " <<connections<< "\n";
    int softtricount = 0;
    cout << "adding softTriangle pointers to particles...\n";
    for (size_t i=0;i<particles.size();i++)
    {
        for (size_t j=0;j<softTris.size();j++)
        {
            ////cout << i << "  " << softTris[j].a->ID()<< ":" << softTris[j].b->ID()<<"\n";
            if (softTris[j].a->ID() == i)
            {
                particles[i].softTris.push_back(&softTris[j]);
                softtricount++;
            }
            else if (softTris[j].b->ID() == i)
            {
                particles[i].softTris.push_back(&softTris[j]);
                softtricount++;
            }
            else if (softTris[j].c->ID() == i)
            {
                particles[i].softTris.push_back(&softTris[j]);
                softtricount++;
            }
        }
    }
    cout << "# of softtricount: " <<softtricount<< "\n";
    //cout << "loading complete\n";
}
