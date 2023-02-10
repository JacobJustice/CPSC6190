#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector.h"
#include "Color.h"

namespace pba{

////////////////////////////////////////////////
//
//      PARTICLE STATE
//
// The state of a particle is characterized by
// (1) particle positions
// (2) particle velocities
// (3) particle masses
// (4) particle colors - useful for display
class ParticleState
{
  public:
    ParticleState() :
        position(Vector(0,0,0)),
        velocity(Vector(0,0,0)),
        color(Color(1,1,1,1)),
        mass(1.0)
    {};
   ~ParticleState(){};	   

   Vector position;
   Vector velocity;
   Color color;
   float mass;
};
}
#endif
