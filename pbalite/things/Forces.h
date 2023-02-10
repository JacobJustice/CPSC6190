#include "Vector.h"
#include <iostream>

using namespace std;
using namespace pba;

class Force
{
    public:
        virtual Vector computeForce(Vector position, Vector velocity)
        {cout << "virtual force\n";return Vector(0,0,0);};
};

class GravityForce : public Force
{
    public: 
        GravityForce(Vector g) : gravity(g)
        {}
        Vector computeForce(Vector position, Vector velocity);

        Vector gravity;
};
