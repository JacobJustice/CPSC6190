#ifndef _SOLVERS_
#define _SOLVERS_

#include <vector>
#include <cmath>
#include <iostream>
#include "Forces.h"
#include "ParticleState.h"
#include "Box.h"
#include "Mesh.h"

using namespace std;
using namespace pba;

class Solver
{
    public:
        Solver(double dt, Box b, double& r) : deltaT{dt}, box{b}, restitution{r}
        {
        }
        virtual void solve(std::vector<ParticleState>& particles){};

        double deltaT{};
        Box box;
        double restitution;
};

class PositionSolver : public Solver
{
    public:
        PositionSolver(double dt, Box b, double& r) : Solver(dt, b, r)
        {}
        void solve(std::vector<ParticleState>& particles);
        void solveParticle(ParticleState& particle, double dT, int depth);
};

class VelocitySolver : public Solver
{
    public:
        VelocitySolver(double dt, Box b, double& r, Force* f) : Solver(dt, b, r), force{f}
        {}
        void solve(std::vector<ParticleState>& particles);
        Force* force{};

};

class LeapfrogSolver : public Solver
{
    public:
        LeapfrogSolver(double dt, Box b, double& r, Force* f) : Solver(dt, b, r),
        p_s1(dt/2, b, r), v_s(dt, b, r, f), p_s2(dt/2, b, r)
        {};
        void solve(std::vector<ParticleState>& particles);

    private:
        PositionSolver p_s1;
        VelocitySolver v_s;
        PositionSolver p_s2;
};

const double alpha = 1.0/(4.0-pow(4.0, 1.0/3.0));
const double beta = (1.0 - (2.0*alpha));
class SixthOrderSolver : public Solver
{
    public:
        SixthOrderSolver(double dt, Box b, double& r, Force* f) : 
            Solver(dt, b, r), l_s_alpha(alpha*dt, b, r, f),l_s_beta(beta*dt, b, r, f)
        {
        };
        void solve(std::vector<ParticleState>& particles);

    private:
        LeapfrogSolver l_s_alpha;
        LeapfrogSolver l_s_beta;
};
class MeshSolver : public Solver
{
    public:
        MeshSolver(double dt, Box b, double& r, Force* f) : Solver(dt, b, r), s_o_s(dt, b, r, f)
        {
        }
        void solve(Mesh& m);

        private:
            SixthOrderSolver s_o_s;
};

#endif // _SOLVERS_
