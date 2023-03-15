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
static int reset = 0;

MyThing::MyThing(const std::string nam) :
 PbaThingyDingy (nam), 
 gravity		(1.0),
 restitution	(1.0),
 emit       	(false)
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
      glColor3f( ci.red(), ci.green(), ci.blue() );
      glVertex3f( P.X(), P.Y(), P.Z() );
   }
   glEnd();
   box.Display();
}

Mesh MyThing::LoadMesh(const char* model)
{
    cout <<"loading model "<< model<< " ...\n";

    vector<unsigned int> vertexIndices;
    vector<Vector> temp_vertices;

    FILE * file = fopen(model, "r");
    if (file == NULL){
        cout << "CAN'T OPEN FILE\n";
        throw invalid_argument("Invalid filename for model\n");
    }

    while (true)
    {
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF){
            break;
        }
        else
        {
            if ( strcmp(lineHeader, "v") == 0){
                float x, y, z;
                if (fscanf(file, "%f %f %f\n", &x, &y, &z) == 0){
                    cout << "matching failure\n";
                }
                else{
                    cout << x << " " << y << " " << z <<"\n";
                    Vector vertex = Vector(x, y, z);
                    temp_vertices.push_back(vertex);
                }
            }
        }
    }
    cout << temp_vertices[0].X() << " "<< temp_vertices[0].Y() << " "<< temp_vertices[0].Z() << " " << "\n";

    cout <<"loading complete!\n";
    return Mesh();
}

void MyThing::Keyboard( unsigned char key, int x, int y )
{
        PbaThingyDingy::Keyboard(key,x,y);
        //cout << key<< '\n';
        if( key == 'e' ){ emit = !emit; }

        if( key == 'g' )
        { 
            gravity -= .1; 
            cout << "gravity: " << gravity << '\n';
        }
        if( key == 'G' )
        { 
            gravity += .1; 
            cout << "gravity: " << gravity << '\n';
        }

        if( key == 'c' )
        { 
            restitution -= .1; 
            cout << "coefficent of restitution: " << restitution << '\n';
        }
        if( key == 'C' )
        { 
            restitution += .1;
            cout << "coefficent of restitution: " << restitution << '\n';
        }
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
      size_t nbincrease = 10;
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
      }
   }
}

void MyThing::Reset()
{
    cout << "RESET CALLED " << reset << '\n';
    reset++;
   // Distribute particles with random positions
//    particles.clear();
//   particles.resize(20);
//   for(size_t i=0;i<particles.size();i++)
//   {
//      double s = 2.0*drand48() - 1.0;
//      double ss = std::sqrt( 1.0 - s*s );
//      double theta = 2.0*3.14159265*drand48();
//      pba::Vector P( ss*std::cos(theta), s, ss*std::sin(theta) );
//      P *= std::pow( drand48(), 1.0/6.0 );
//      particles[i].position = P;
//      particles[i].color = pba::Color(drand48(),drand48(),drand48(),0);
//      particles[i].velocity = pba::Vector(drand48()-0.5,drand48()-0.5,drand48()-0.5);
//   }
    Mesh mesh = LoadMesh("../models/bunny_superlo_scaled.obj");
}

void MyThing::Usage()
{
   PbaThingyDingy::Usage();
   cout << "=== " << name << " ===\n";
   cout << "e            toggle particle emission on/off\n";
   cout << "G/g          increase/decrease gravity \n";
   cout << "C/c          increase/decrease coefficient of restitution \n";
}


pba::PbaThing pba::CreateMyThing(){ return PbaThing( new MyThing() ); }


