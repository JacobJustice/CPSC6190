#include "Solvers.h"
#include <iostream>

void VelocitySolver::solve(std::vector<ParticleState>& particles)
{
    for (ParticleState& p: particles)
    {
//        cout << p.velocity.X() << "\n";
//        cout << "p.velocity:" << p.velocity.X() << ',' << p.velocity.Y() << ',' << p.velocity.Z() << '\n';
//        cout << (deltaT/p.mass) <<"   " << force->computeForce(p.position, p.velocity).magnitude() << "\n";
          p.velocity = p.velocity + (deltaT/p.mass) * force->computeForce(p);
//        cout << "POSTp.velocity:" << p.velocity.X() << ',' << p.velocity.Y() << ',' << p.velocity.Z() << '\n';
    }
}

void PositionSolver::solve(std::vector<ParticleState>& particles)
{
    //cout << "position";
    for (ParticleState& p: particles)
    {
        solveParticle(p, deltaT, 0);
    }
    
}

/*
 * particle: the particle being advanced
 * deltaT: the amount of time this particle needs to move forward
 * depth: keeps track of depth (if used properly)
 */
void PositionSolver::solveParticle(ParticleState& particle, double dT, int depth)
{
    if (!(dT < 1e-6) && depth < 5){
        Vector endPosition = particle.position + (particle.velocity*dT);
        // add check that there is no collision between p.position and endPosition
        double location = dT;
        int plane_ind = -1;
        if (box.detectIntersection(particle.position, endPosition, location, plane_ind))
        {
            //cout << "intersection " << depth << "\tlocation:" << location << "\tplane_ind:" << plane_ind;
            //cout << "\tdT: "<< dT << '\n';
            // scaled direction
            Vector dir = particle.velocity*location;
            Vector intersectionPoint = particle.position + dir;
            Vector planeNorm = box.planes[plane_ind].normal;
            dir.normalize();
            dir = dir*particle.velocity.magnitude();
            Vector reflection = dir - 2*(dir*planeNorm) * planeNorm;
            //cout << "reflection:" << reflection.X() << ',' << reflection.Y() << ',' << reflection.Z() << ":" <<  particle.velocity.magnitude() << "   " << reflection.magnitude() << '\n';
            //cout << "intersectionPoint:" << intersectionPoint.X() << ',' << intersectionPoint.Y() << ',' << intersectionPoint.Z() << '\n';
            //cout << "\n";

            //particle.position = intersectionPoint;
            particle.velocity = *restitution*reflection;
            solveParticle(particle, dT-location, depth+1);
        }
        else{
            particle.position = endPosition;
        }
    }
}

void MeshSolver::solve(Mesh& m)
{
    s_o_s.solve(m.particles);
}

void SixthOrderSolver::solve(std::vector<ParticleState>& particles)
{
    //cout << "SixthOrderSolver " << alpha << " " << beta << " " << deltaT << "\n";
    l_s_alpha.solve(particles);
    l_s_beta.solve(particles);
    l_s_alpha.solve(particles);
}

void LeapfrogSolver::solve(std::vector<ParticleState>& particles)
{
    //cout << "leapfrog\n";
    p_s1.solve(particles);
    //cout << particles[0].velocity.X() << " "<< particles[0].velocity.Y() << " "<< particles[0].velocity.Z() << "\n";
    v_s.solve(particles);
    //cout << particles[0].velocity.X() << " "<< particles[0].velocity.Y() << " "<< particles[0].velocity.Z() << "\n";
    //cout << deltaT << "\n";
    p_s2.solve(particles);
}
