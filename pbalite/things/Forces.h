#ifndef _FORCES_
#define _FORCES_

#include "Vector.h"
#include "Mesh.h"
#include "ParticleState.h"
#include <random>
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

class AvoidanceForce : public Force
{
    public:
        AvoidanceForce(double& a) : avoidanceCoef{a}
        {}
        Vector computeForce(ParticleState p, vector<ParticleState> particles);
        double& avoidanceCoef;
};

class VelocityMatchingForce : public Force
{
    public:
        VelocityMatchingForce(double& vm) : velocityMatchingCoef{vm}
        {}
        Vector computeForce(ParticleState p, vector<ParticleState> particles);
        double& velocityMatchingCoef;
};

class CenteringForce : public Force
{
    public:
        CenteringForce(double& c) : centeringCoef{c}
        {}
        Vector computeForce(ParticleState p, vector<ParticleState> particles);
        double& centeringCoef;
};

class BoidForce : public Force
{
        public:
            BoidForce(double& c, double& vm, double& a, double& mf, vector<ParticleState>& p) : 
            cForce(c),
            vmForce(vm),
            aForce(a),
            maxForce(mf),
            particles{p}
            {}
            static double k_d(Vector x_i, Vector x_j)
            {
                double r1 = 0.5; 
                double r2 = 1.3; 
                Vector diff = x_j - x_i;
                double magnitude = diff.magnitude();
                if (magnitude <= r1)
                {
                    return 1;
                }
                else if (magnitude > r2)
                {
                    return 0;
                }
                else
                {
                    return (r2 - magnitude)/(r2-r1);
                }
            }
            static double k_theta(ParticleState p_i, ParticleState p_j)
            {
                double pi = 3.14159;
                Vector diff = p_i.position - p_j.position;
                double dist = diff.magnitude();
                if (dist == 0) return 0;

                double theta1 = pi;
                double cos_theta1 = std::cos(theta1/2);
                double cos_ij = (diff*p_i.velocity)/(p_i.velocity.magnitude()*dist);

                if (cos_ij > cos_theta1)
                {
                    return 1;
                }
                double theta2 = 2*pi;
                double cos_theta2 = std::cos(theta2/2);
                if (cos_ij < cos_theta2)
                    return 0;
                else
                    return (cos_theta2 - cos_ij)/(cos_theta2-cos_theta1);
            }

        private:
            Vector computeForce(ParticleState p);
            CenteringForce cForce;
            VelocityMatchingForce vmForce;
            AvoidanceForce aForce;
            double maxForce;
            vector<ParticleState>& particles;

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
