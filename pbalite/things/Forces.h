#ifndef _FORCES_
#define _FORCES_

#include "Vector.h"
#include "Mesh.h"
#include "ParticleState.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace pba;

// need to figure out best way to pass in all relevant parameters

class Force
{
    public:
        virtual Vector computeForce(ParticleState p)
        {cout << "virtual force\n";return Vector(0,0,0);};
};

class GravityForce : public Force
{
    public: 
        GravityForce(double* g) : gravity(g)
        {}
        Vector computeForce(ParticleState p);

        double* gravity;
};
class SpringForce : public Force
{
    public:
        SpringForce(double* s, double* f) : springCoef{s}, frictionCoef{f}
        {}
        Vector computeForce(ParticleState p);

        double* springCoef;
        double* frictionCoef;
};

class AreaForce : public Force
{
    public:
        AreaForce(double* s, double* f) : areaCoef{s}, frictionCoef{f}
        {}
        Vector computeForce(ParticleState p);

        double* areaCoef;
        double* frictionCoef;
};


class SoftBodyForce : public Force
{
    public:
        SoftBodyForce(double* gravity, double* springCoef, double* frictionCoef, double* areaCoef, double* areaFrictionCoef) : 
            gravityForce(gravity),
            springForce(springCoef, frictionCoef),
            areaForce(areaCoef, areaFrictionCoef)
        {
        }
        Vector computeForce(ParticleState p);

    private:
        Vector computeForce();
        GravityForce gravityForce;
        SpringForce springForce;
        AreaForce areaForce;
};

#endif // _FORCES_
