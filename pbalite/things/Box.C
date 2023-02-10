#include "Box.h"
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

void pba::Box::Display()
{
    for (Plane plane: planes)
	{
		plane.Display();
    }
}

