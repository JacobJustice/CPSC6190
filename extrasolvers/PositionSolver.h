#include <vector>
#include "Solver.h"

using namespace std;
using namespace pba;

class PositionSolver : public Solver
{
    public:
        void solve(std::vector<ParticleState>& particles);
};
