#ifndef MESH_H
#define MESH_H
/*
 * stores classes relevant to Mesh objects
 */


#include "Vector.h"
#include "Color.h"
#include "ParticleState.h"
#include <vector>
#include <cmath>
using namespace std;
namespace pba{

class Edge
{
    public:
        Edge(ParticleState* A, ParticleState* B, Color c){
            a = A;
            b = B;
            color = c;
            length = sqrt(pow(a->position.X() - b->position.X(),2) 
                        + pow(a->position.Y() - b->position.Y(),2)
                        + pow(a->position.Z() - b->position.Z(),2));
        }
        ParticleState* a;
        ParticleState* b;
        Color color;
        double length;
};

class SoftTriangle
{
    public:
        SoftTriangle(ParticleState* A, ParticleState* B, ParticleState* C){
            a = A;
            b = B;
            c = C;
            Vector e_ab = a->position - b->position;
            Vector e_bc = b->position - c->position;
            area = (.5)*(e_ab^e_bc).magnitude();
        }
        // defining 3 vertices of a triangle
        ParticleState* a;
        ParticleState* b;
        ParticleState* c; 
        double area;
};

class Mesh
{
    private:
        void LoadMesh(const char* fn);
        Vector posOffset;

    public:
        Mesh()
        {}

        Mesh(const char* fn, Vector pO)
        {
            posOffset = pO;
            LoadMesh(fn);
        }
        void Display();

        std::vector<ParticleState> particles;
        std::vector<Edge> edges;
        std::vector<SoftTriangle> softTris;
};
}
#endif // MESH_H

