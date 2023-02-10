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

            planes[0] = Plane(Vector(a,b,c), Vector(a,e,c), Vector(d,e,c), Vector(d,b,c), 0, false);
            planes[1] = Plane(Vector(a,b,c), Vector(a,b,f), Vector(d,b,f), Vector(d,b,c), 1, true);
            planes[2] = Plane(Vector(d,b,c), Vector(d,e,c), Vector(d,e,f), Vector(d,b,f), 2, true);
            planes[3] = Plane(Vector(a,b,c), Vector(a,e,c), Vector(a,e,f), Vector(a,b,f), 3, true);
            planes[4] = Plane(Vector(a,e,c), Vector(a,e,f), Vector(d,e,f), Vector(d,e,c), 4, true);
            planes[5] = Plane(Vector(a,b,f), Vector(a,e,f), Vector(d,e,f), Vector(d,b,f), 5, true);
        }

        void Display();

        bool detectIntersection(Vector start, Vector end, double location, int plane_ind);

    private:
        Vector LLC;
        Vector URC;
        Plane planes[6];
};
}
