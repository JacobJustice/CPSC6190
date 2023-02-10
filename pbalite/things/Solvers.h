#include <vector>
#include "Forces.h"
#include "ParticleState.h"

using namespace std;
using namespace pba;

class Solver
{
    public:
        Solver(double dt) : deltaT{dt}
        {}
        virtual void solve(std::vector<ParticleState>& particles){};

        double deltaT{};

};

class PositionSolver : public Solver
{
    public:
        PositionSolver(double dt) : Solver(dt)
        {}
        void solve(std::vector<ParticleState>& particles);
};

class VelocitySolver : public Solver
{
    public:
        VelocitySolver(double dt, Force* f) : Solver(dt), force{f}
        {}
        void solve(std::vector<ParticleState>& particles);
        Force* force{};

};

class LeapfrogSolver : public Solver
{
    public:
        LeapfrogSolver(double dt, Force* f) : Solver(dt),
        p_s1(dt/2), v_s(dt, f), p_s2(dt/2)
        {};
        void solve(std::vector<ParticleState>& particles);

    private:
        PositionSolver p_s1;
        VelocitySolver v_s;
        PositionSolver p_s2;
};

