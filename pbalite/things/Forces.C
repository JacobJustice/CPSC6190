#include "Forces.h"
#include <cstdlib>
#include <iostream>

Vector BoidForce::computeForce(ParticleState p)
{
    if (p.ID() == 0)
    {
        return Vector(drand48()-0.5,drand48()-0.5,drand48()-0.5);
    }
    Vector forceSum = Vector(0,0,0);
    double residual = 0;
    Vector av = aForce.computeForce(p, particles);
    Vector vm = Vector(0,0,0);
    Vector c = Vector(0,0,0);

    double av_mag = av.magnitude();
    if (av_mag >= maxForce)
    {
        av = (av/av_mag)*maxForce;
    }
    else
    {
        residual = maxForce - av_mag;
        vm = vmForce.computeForce(p, particles);
        double vm_mag = vm.magnitude();
        if (vm_mag >= residual)
        {
            vm = (vm/vm_mag) * residual;
        }
        else
        {
            residual = residual - vm_mag;
            c = cForce.computeForce(p, particles);
            double c_mag = c.magnitude();
            if (c_mag >= residual)
            {
                c = (c/c_mag)*residual; 
            }
        }
    }
    forceSum = av + vm + c;
    return forceSum;
}

Vector AvoidanceForce::computeForce(ParticleState p, std::vector<ParticleState> particles)
{
    Vector out = Vector(0,0,0);
    for (ParticleState p_j : particles)
    {
        if (p_j.ID() != p.ID())
        {
            Vector diff = (p_j.position - p.position);
            double magnitude = diff.magnitude();
            Vector av = -1*diff/(magnitude*magnitude);
            out = out + ((avoidanceCoef)*av)*BoidForce::k_d(p.position, p_j.position)*BoidForce::k_theta(p, p_j);
        }
    }
//    cout << "average_magnitude == " << magnitude/particles.size() << "\n";
//    if (p.ID() == 19)
//    {
//        cout << p.ID() << " ";
//    	cout << "avoidanceCoef " << avoidanceCoef <<  " ";
//        cout<< "avoidanceForce:" << out.X() << " "<< out.Y() << " "<< out.Z() << "\n";
//    }
    return out;
}

Vector VelocityMatchingForce::computeForce(ParticleState p, std::vector<ParticleState> particles)
{
    Vector out = Vector(0,0,0);
    for (ParticleState p_j : particles)
    {
        if (p_j.ID() != p.ID())
        {
            Vector diff = (p_j.velocity - p.velocity);
            out = out + (velocityMatchingCoef * diff)*BoidForce::k_d(p.position, p_j.position)*BoidForce::k_theta(p, p_j);
        }
    }
    return out; 
}

Vector CenteringForce::computeForce(ParticleState p, std::vector<ParticleState> particles)
{
    Vector out = Vector(0,0,0);
    for (ParticleState p_j : particles)
    {
        if (p_j.ID() != p.ID())
        {
            Vector diff = (p_j.position - p.position);
            out = out + (centeringCoef * diff)*BoidForce::k_d(p.position, p_j.position)*BoidForce::k_theta(p, p_j);
        }
    }
    return out; 
}


Vector GravityForce::computeForce(ParticleState p)
{
    return Vector (0, *gravity*-1, 0);
}

Vector SpringForce::computeForce(ParticleState p)
{
    Vector springForce = Vector(0,0,0);
    Vector frictionForce = Vector(0,0,0);
    for (Edge* e: p.connections)
    {
        // spring force
        ParticleState* p_j;
        if (e->a->ID() == p.ID()){
            p_j = e->b;
        } else{
            p_j = e->a;
        }

        Vector r = p_j->position - p.position;
        Vector r_rmag = r/r.magnitude();
        springForce += *springCoef * r_rmag * (r.magnitude() - e->length);

        // friction force
        Vector delta_vab = e->b->velocity - e->a->velocity;
        r.normalize();
        frictionForce += *frictionCoef * (r * delta_vab) * r;
    }
    //cout<< "springForce" << springForce.X() << " "<< springForce.Y() << " "<< springForce.Z() << "\n";
    //cout<< "frictionForce" << frictionForce.X() << " "<< frictionForce.Y() << " "<< frictionForce.Z() << "\n";
    //return Vector(0,0,0);

    return springForce - frictionForce;
}

    //cout <<"springForce:"<< p.ID() << ":"<< springForce.X()<< springForce.Y()<< springForce.Z() << "\n";

Vector AreaForce::computeForce(ParticleState p)
{
    Vector areaVector = Vector(0,0,0);
    Vector frictionVector = Vector(0,0,0);
    for (SoftTriangle* st: p.softTris)
    {
        // area force
        //// cout << st << "\n";
        //cout << st->a->position.X() << " "<< st->a->position.Y() << " "<< st->a->position.Z() << "\n";
        //cout << st->b->position.X() << " "<< st->b->position.Y() << " "<< st->b->position.Z() << "\n";
        //cout << st->c->position.X() << " "<< st->c->position.Y() << " "<< st->c->position.Z() << "\n";
        //cout << "st->area:" <<st->area << "\n";
        Vector e_ab = st->a->position - st->b->position;
        //cout << e_ab.X() << " "<< e_ab.Y() << " "<< e_ab.Z() << "\n";

        Vector e_bc = st->b->position - st->c->position;
        //cout << e_bc.X() << " "<< e_bc.Y() << " "<< e_bc.Z() << "\n";
        Vector abcrossbc = e_ab^e_bc;
        //cout << abcrossbc.X() << " "<< abcrossbc.Y() << " "<< abcrossbc.Z() << "\n";
        //cout << abcrossbc.magnitude() << "\n";
        double area = (.5)*(e_ab^e_bc).magnitude();
        //cout << "area:"<<area<<"\n";
        Vector d;
        if (st->a->ID() == p.ID()){
            Vector e_ac = st->a->position - st->c->position;
            d = .5*(e_ab + e_ac);
        }
        else if (st->b->ID() == p.ID()){
            Vector e_ba = st->b->position - st->a->position;
            d = .5*(e_ba + e_bc);
        }
        else{ 
            Vector e_ac = st->a->position - st->c->position;
            d = .5*(e_ac + e_bc);
        }
        //cout << d.X() << " "<< d.Y() << " "<< d.Z() << "\n";
        //cout << *areaCoef << "\n\n";
        areaVector += *areaCoef*d*((area/st->area) - 1);

        // compute friction force here so I don't have to compute d twice
        d.normalize();
        Vector delta_vabc = p.velocity - .5*(st->b->velocity+st->c->velocity);
        //cout << *frictionCoef<< "\n\n";
        frictionVector += *frictionCoef * (d * delta_vabc) * d;
    }
    //cout<< "areaVector" << areaVector.X() << " "<< areaVector.Y() << " "<< areaVector.Z() << "\n";
    //cout<< "frictionVector" << frictionVector.X() << " "<< frictionVector.Y() << " "<< frictionVector.Z() << "\n";

    return areaVector - frictionVector;
}

Vector SoftBodyForce::computeForce(ParticleState p)
{
    Vector outForce = gravityForce.computeForce(p) 
                        + springForce.computeForce(p)
                        + areaForce.computeForce(p);

    return outForce;
}

