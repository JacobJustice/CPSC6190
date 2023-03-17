#include "Forces.h"
#include <iostream>

Vector GravityForce::computeForce(ParticleState p)
{
    return gravity;
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
        springForce += springCoef * r_rmag * (r.magnitude() - e->length);

        // friction force
        Vector delta_vab = e->b->velocity - e->a->velocity;
        frictionForce += frictionCoef * (r_rmag * delta_vab) * r_rmag;
    }

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
        Vector e_ab = st->a->position - st->b->position;
        Vector e_bc = st->b->position - st->c->position;
        double area = (1/2)*(e_ab^e_bc).magnitude();
        Vector d;
        if (st->a->ID() == p.ID()){
            Vector e_ac = st->a->position - st->c->position;
            d = e_ab + e_ac;
            d /= 2;
        }
        else if (st->b->ID() == p.ID()){
            Vector e_ba = st->b->position - st->a->position;
            d = e_ba + e_bc;
            d /= 2;
        }
        else{ 
            Vector e_ac = st->a->position - st->c->position;
            d = e_ac + e_bc;
            d /= 2;
        }
        areaVector += areaCoef*d*((area/st->area) - 1);

        // compute friction force here so I don't have to compute d twice
        d.normalize();
        Vector delta_vabc = p.velocity - .5*(st->b->velocity+st->c->velocity);
        frictionVector += frictionCoef * (d * delta_vabc) * d;
    }

    return areaVector - frictionVector;
}

Vector SoftBodyForce::computeForce(ParticleState p)
{
    Vector outForce = gravityForce.computeForce(p) 
                        + springForce.computeForce(p)
                        + areaForce.computeForce(p);

    return outForce;
}

