//-------------------------------------------------------
//
//  MyThing.C
//
//
//--------------------------------------------------------

#include "MyThing.h"
#include <cstdlib>
#include <cstring>
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.
#include <iostream>


using namespace std;

using namespace pba;

MyThing::MyThing(const std::string nam) :
 PbaThingyDingy 	(nam), 
 gravity			(1.0),
 spring				(1.0),
 friction			(0.0),
 area				(1.0),
 areaFriction		(0.1),
 restitution		(1.0),
 avoidance			(0.010),
 velocityMatching	(0.2),
 centering			(0.065),
 maxForce			(2.0),
 emit       		(false)
{
    Reset();
    std::cout << name << " constructed\n";
}

MyThing::~MyThing(){}

void MyThing::Init( const std::vector<std::string>& args ) 
{ 
}
    
void MyThing::Display() 
{
    glPointSize(5.0);
   glBegin(GL_POINTS);
   for( size_t i=0;i<particles.size();i++ )
   {
      const Vector& P = particles[i].position;
      const Color& ci = particles[i].color;
        if (i == 0)
        {
            glColor3f( 1, 0, 0);
            glVertex3f( P.X(), P.Y(), P.Z() );
        }
        else
        {
            glColor3f( 0, ci.green(), ci.blue() );
            glVertex3f( P.X(), P.Y(), P.Z() );
        }
   }
   glEnd();
   box.Display();
}

void MyThing::Keyboard( unsigned char key, int x, int y )
{
        PbaThingyDingy::Keyboard(key,x,y);
        //cout << key<< '\n';
        if( key == 'e' ){ emit = !emit; }

//        if( key == 'g' )
//        { 
//            gravity -= .1; 
//            cout << "gravity: " << gravity << '\n';
//        }
//        if( key == 'G' )
//        { 
//            gravity += .1; 
//            cout << "gravity: " << gravity << '\n';
//        }
//
//        if( key == 'k' )
//        { 
//            spring -= .1; 
//            cout << "spring: " << spring << '\n';
//        }
//        if( key == 'K' )
//        { 
//            spring += .1; 
//            cout << "spring: " << spring << '\n';
//        }
        if( key == 'a' )
        { 
            avoidance -= .001; 
            cout << "avoidance: " << avoidance << '\n';
        }
        if( key == 'A' )
        { 
            avoidance += .001; 
            cout << "avoidance: " << avoidance << '\n';
        }
        if (key == 'v')
        {
            velocityMatching -= .001;
            cout << "velocityMatching: " << velocityMatching << '\n';
        }
        if (key == 'V')
        {
            velocityMatching += .001;
            cout << "velocityMatching: " << velocityMatching << '\n';
        }
        if (key == 'c')
        {
            centering -= .001;
            cout << "centering: " << centering << '\n';
        }
        if (key == 'C')
        {
            centering += .001;
            cout << "centering: " << centering << '\n';
        }
//        if( key == 's' )
//        { 
//            areaFriction -= .1; 
//            cout << "areaFriction: " << areaFriction << '\n';
//        }
//        if( key == 'S' )
//        { 
//            areaFriction += .1; 
//            cout << "areaFriction: " << areaFriction << '\n';
//        }
        if( key == 'm' )
        { 
            maxForce -= .1; 
            cout << "maxForce: " << maxForce << '\n';
        }
        if( key == 'M' )
        { 
            maxForce += .1; 
            cout << "maxForce: " << maxForce << '\n';
        }
//        if( key == 'r' )
//        { 
//            restitution -= .1; 
//            cout << "coefficent of restitution: " << restitution << '\n';
//        }
//        if( key == 'R' )
//        { 
//            restitution += .1;
//            cout << "coefficent of restitution: " << restitution << '\n';
//        }
}


void MyThing::solve()
{
    // This is where the particle state - position and velocity - are updated
    // 
    solver.solve(particles);


   // This concludes the solver action
   //
   //
   //
   //
   // This is where we can add more particles
   if(emit)
   {
      size_t nbincrease = 5;
      particles.resize(particles.size()+nbincrease);
      Vector P = Vector((rand()/(double)RAND_MAX), (rand()/(double)RAND_MAX), (rand()/(double)RAND_MAX));
      //Vector P = Vector(0,.5,0);
      Vector V;
      Color C;
      std::cout << "Total Points " << particles.size() << std::endl;
      for(size_t i=particles.size()-nbincrease;i<particles.size();i++)
      {
        particles[i].position = P;
        particles[i].color = pba::Color(drand48(),drand48(),drand48(),0);
        particles[i].velocity = pba::Vector(drand48()-0.5,drand48()-0.5,drand48()-0.5);
        particles[i].assignID(i);
      }
   }
}

void MyThing::Reset()
{
    //cout << "RESET CALLED " << reset++ << '\n';

   // Distribute particles with random positions
    particles.clear();
    particles.resize(50);
    for(size_t i=0;i<particles.size();i++)
    {
      double s = 2.0*drand48() - 1.0;
      double ss = std::sqrt( 1.0 - s*s );
      double theta = 2.0*3.14159265*drand48();
      pba::Vector P( ss*std::cos(theta), s, ss*std::sin(theta) );
      P *= std::pow( drand48(), 1.0/6.0 );
      particles[i].position = P;
      particles[i].color = pba::Color(drand48(),drand48(),drand48(),0);
      particles[i].velocity = pba::Vector(drand48()-0.5,drand48()-0.5,drand48()-0.5);
      particles[i].assignID(i);
    }
    //mesh = Mesh("../models/bunny_superlo_scaled.obj", Vector(drand48()*.7,.5, drand48()*.7));
    solver = LeapfrogSolver(dt, box, &restitution, &boidforce);
}

void MyThing::Usage()
{
   PbaThingyDingy::Usage();
   cout << "=== " << name << " ===\n";
   cout << "e            toggle particle emission on/off\n";
   //cout << "G/g          increase/decrease gravity \n";
   cout << "R/r          increase/decrease coefficient of restitution \n";
   cout << "A/a          increase/decrease avoidance\n";
   cout << "V/v          increase/decrease velocity matching \n";
   cout << "M/m          increase/decrease maximum force\n";
}


pba::PbaThing pba::CreateMyThing(){ return PbaThing( new MyThing() ); }


