#include "Box.h"
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;
using namespace pba;

void Box::Display()
{
    for (Plane plane: planes)
	{
		plane.Display();
    }
}

/*
 * location gets updated such that position + location*velocity the point
 * on the plane that was intersected
 */

bool detect_intersection(Vector start, Vector end, double& location, int& plane_ind)
{
    for (Plane pl: planes)
    {
        double loc = 2.0;
        if (pl.detectIntersection(start, end, location)
        {
            if (loc < location)
            {
                location = loc;
                plane_ind = i;
            }
        }
    }
}

