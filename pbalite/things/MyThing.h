#ifndef _MYTHING_
#define _MYTHING_
//-------------------------------------------------------
//
//  MyThing.h
//
//  PbaThing for a collection of particles
//  each doing a random walk.
//
//  Copyright (c) 2017 Jerry Tessendorf
//
//
//--------------------------------------------------------


#include "Vector.h"
#include "Color.h"
#include "PbaThing.h"
#include "ParticleState.h"
#include "Mesh.h"
#include "Box.h"
#include "Solvers.h"



using namespace std;

namespace pba{


class MyThing: public PbaThingyDingy
{
  public:

    // Feel free to customize the name of this thing.
    MyThing(const std::string nam = "Lecture_01_thing");
   ~MyThing();

    //! Initialization, including GLUT initialization.
    //! Called once at the beginning.  Could be used
    //! to set up things once.
    void Init( const std::vector<std::string>& args );
   
    /////////////////////////////////////////////////////////////// 
    // CASCADING CALLBACK FUNCTIONS 
    // The methods below are called as part of a bigger set
    // of similar calls.  Most of the other calls take place
    // in the viewer portion of this project.
    ///////////////////////////////////////////////////////////////

    //! Implements a display event
    //! This is where you code the opengl calls to display 
    //! your system.
    void Display();

    //! Implements responses to keyboard events 
    //! This is called when you hit a key
    void Keyboard( unsigned char key, int x, int y );

    //! Implements simulator updates during an idle period
    //! This is where the update process is coded
    //! for your dynamics problem.
    void solve();

    //! Implements reseting parameters and/or state
    //! This is called when you hit the 'r' key
    void Reset();

    //! Displays usage information on stdout
    //! If you set up actions with the Keyboard()
    //! callback, you should include a statement 
    //! here as to what the keyboard option is.
    void Usage();

  private:
	// controls gravity
    double gravity;

    // spring coefficient for soft body
    double spring;

    // edge friction coefficient for soft body
    double friction; 

    // area force coefficient for soft body
    double area;

    //  friction coefficient for soft body
    double areaFriction; 

    // coefficient of restitution
    double restitution;

    // flag for whether to create more particles
    bool emit;

    Vector llc = Vector(-1,-1,-1);
    Vector urc = Vector(1,1,1);
    Box box = Box(llc, urc);
    Mesh mesh;
    SoftBodyForce* force = new SoftBodyForce(&gravity, &spring, &friction, &area, &areaFriction);
    MeshSolver solver = MeshSolver(dt, box, &restitution, force);


    // This is all of the particles in the system
    std::vector<ParticleState> particles;
    //
    //
    //////////////////////////////////////////////// 

};

// This function constructs the MyThing and wraps it in a 
// smart pointer called a PbaThing. 
// You need not alter this.
pba::PbaThing CreateMyThing();

}

#endif // _MYTHING_
