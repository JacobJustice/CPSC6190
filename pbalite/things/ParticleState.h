#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector.h"
#include "Color.h"
#include <vector>


namespace pba{

class SoftTriangle;
class Edge;

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
        mass(1.0),
        assignedID{false}
        {};
       ~ParticleState(){};	   

       Vector position;
       Vector velocity;
       Color color;
       float mass;
       //which edges is this particle a part of?
       std::vector<Edge*> connections;
       //which triangles is this particle a part of?
       std::vector<SoftTriangle*> softTris;

   private:
       size_t id;
       bool assignedID;

   public:
       void assignID(size_t newID)
       {
           id = newID;
           assignedID= true;
       }
       bool idAssigned() {return assignedID;}
       size_t ID() {return id;}



};
}
#endif
