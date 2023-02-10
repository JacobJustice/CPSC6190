#include <vector>
#include "ParticleState.h"

using namespace std;
using namespace pba;

class Solver
{
    public:
        Solver(double dt)
        {
            deltaT = dt;
        }

        void solve(std::vector<ParticleState>& particles);

    private:
        double deltaT;
};

