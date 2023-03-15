#ifndef _PLANE_
#define _PLANE_

#include "Vector.h"
#include <iostream>
#include "Color.h"

using namespace std;
namespace pba{
class Plane
{
    public:
        Plane(){}
        Plane(Vector bl, Vector tl, Vector tr, Vector br, Vector norm, int i, bool vis)
        {
            tri1 = Color(drand48(),drand48(),drand48(),0);
            tri2 = Color(drand48(),drand48(),drand48(),0);

            BL = bl;
            TL = tl;
            TR = tr;
            BR = br;

            normal = norm;

            id = i;

            isVisible = vis;
        }
        void Display();

        bool detectIntersection(Vector start, Vector end, double& location);

        int id = -1;
        Vector normal;
        Vector BL;
        Vector TL;
        Vector TR;
        Vector BR;
    private:
        Color tri1;
        Color tri2;


        bool isVisible;
};
}
#endif // _PLANE_
