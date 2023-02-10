#include "Vector.h"
#include <iostream>
#include "Color.h"

using namespace std;
namespace pba{
class Plane
{
    public:
        Plane(){}
        Plane(Vector bl, Vector tl, Vector tr, Vector br, int id, bool vis)
        {
            tri1 = Color(drand48(),drand48(),drand48(),0);
            tri2 = Color(drand48(),drand48(),drand48(),0);

            BL = bl;
            TL = tl;
            TR = tr;
            BR = br;

            isVisible = vis;
        }
        void Display();

        bool detectIntersection();
    private:
        Color tri1;
        Color tri2;
        Vector BL;
        Vector TL;
        Vector TR;
        Vector BR;

        bool isVisible;
};
}
