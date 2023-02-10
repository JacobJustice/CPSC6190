#include "Solvers.h"
#include <iostream>

void VelocitySolver::solve(std::vector<ParticleState>& particles)
{
    //cout << "velocity ";
    for (ParticleState& p: particles)
    {
        p.velocity = p.velocity + (deltaT/p.mass) * force->computeForce(p.position, p.velocity);
    }
}

void PositionSolver::solve(std::vector<ParticleState>& particles)
{
    //cout << "position";
    for (ParticleState& p: particles)
    {
        p.position = p.position + (p.velocity*deltaT);
    }
}

void LeapfrogSolver::solve(std::vector<ParticleState>& particles)
{
    //cout << "leapfrog\n";
    p_s1.solve(particles);
    v_s.solve(particles);
    p_s2.solve(particles);
}
