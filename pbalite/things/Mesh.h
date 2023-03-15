#ifndef MESH_H
#define MESH_H

#include "Vector.h"
#include "Color.h"

namespace pba{

class Edge
{
    public:
        int a, b; // indices into mesh.particles defining to particles that make one edge
};
class SoftTriangle
{
    public:
        int a, b, c; // indices into mesh.particles defining 3 vertices of a triangle
};
class Mesh
{
    public:
        Mesh()
        {
        }
        Mesh(vector<ParticleState> p, vector<Edge> e, vector<SoftTriangle> st)
        {
            particles = p;
            edges = e;
            softtris = st;
        }

        vector<ParticleState> particles;
        vector<Edge> edges;
        vector<SoftTriangle> softtris;
};
}
#endif // MESH_H

