#ifndef BOX_H
#define BOX_H

#include "Vector.h"
#include "Color.h"
#include "Plane.h"
#include <iostream>


using namespace std;
namespace pba{
class Box
{
    public:
        Box(Vector llc, Vector urc)
        {
            LLC = llc;
            URC = urc;
            double a = llc.X();
            double b = llc.Y();
            double c = llc.Z();
            double d = urc.X();
            double e = urc.Y();
            double f = urc.Z();

            planes[0] = Plane(Vector(a,b,c), Vector(a,e,c), Vector(d,e,c), Vector(d,b,c), Vector( 0, 0, 1), 0, false);
            planes[1] = Plane(Vector(a,b,c), Vector(a,b,f), Vector(d,b,f), Vector(d,b,c), Vector( 0,-1, 0), 1, true);
            planes[2] = Plane(Vector(d,b,c), Vector(d,e,c), Vector(d,e,f), Vector(d,b,f), Vector( 1, 0, 0), 2, true);
            planes[3] = Plane(Vector(a,b,c), Vector(a,e,c), Vector(a,e,f), Vector(a,b,f), Vector(-1, 0, 0), 3, true);
            planes[4] = Plane(Vector(a,e,c), Vector(a,e,f), Vector(d,e,f), Vector(d,e,c), Vector( 0, 1, 0), 4, true);
            planes[5] = Plane(Vector(a,b,f), Vector(a,e,f), Vector(d,e,f), Vector(d,b,f), Vector( 0, 0,-1), 5, true);
        }

        void Display();

        bool detectIntersection(Vector start, Vector end, double& location, int& plane_ind);

        Plane planes[6];

    private:
        Vector LLC;
        Vector URC;
};
}
#endif
