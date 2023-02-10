#include <vector>
#include "Solver.h"
#include "PositionSolver.h"

using namespace std;
using namespace pba;

class LeapfrogSolver : public Solver
{
    public:
        LeapfrogSolver()
        {
            PositionSolver(deltaT)
        };
        void solve(std::vector<ParticleState>& particles);
};

