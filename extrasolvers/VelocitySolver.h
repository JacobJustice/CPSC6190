#include <vector>
#include "Solver.h"

using namespace std;
using namespace pba;

class VelocitySolver : Solver
{
    public:
        void solve(std::vector<ParticleState>& particles);
};
