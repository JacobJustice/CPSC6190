#include "Box.h"
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

using namespace pba;

void Plane::Display()
{
    if (!isVisible) return;

	glBegin(GL_TRIANGLES);
        glColor3f(tri1.red(), tri1.green(), tri1.blue());
        glNormal3f(normal.X(), normal.Y(), normal.Z());
        glVertex3f(BL.X(), BL.Y(), BL.Z());
        glVertex3f(TL.X(), TL.Y(), TL.Z());
        glVertex3f(TR.X(), TR.Y(), TR.Z());

        glColor3f(tri2.red(), tri2.green(), tri2.blue());
        glNormal3f(normal.X(), normal.Y(), normal.Z());
        glVertex3f(TR.X(), TR.Y(), TR.Z());
        glVertex3f(BR.X(), BR.Y(), BR.Z());
        glVertex3f(BL.X(), BL.Y(), BL.Z());
	glEnd();
}

bool Plane::detectIntersection(Vector start, Vector end, double& location)
{
    // direction of the particle
    Vector dir = end - start;
	double dirMag = dir.magnitude();
    double denom = normal*dir;
    if (fabs(denom) < 1e-6)
    {
        return false;
    }
    // get distance from the origin
    double dist = - (normal * BL);
    double t = -((normal * start) + dist) / denom;
    if (t > 0)
    {
        // distance between start and the intersection point
        Vector intersectionDir = t*dir;
        double tMag = intersectionDir.magnitude(); 
        if (tMag < dirMag)
        {
//            cout<< "dotproduct " << intersectionDir*dir << '\n';
//            cout << "start: " << start.X() << ',' << start.Y() << ',' << start.Z();
//            cout << "\tend: " << end.X() << ',' << end.Y() << ',' << end.Z() << "\n";
//            cout << "denom: " << denom << "\tdir: "  << dir.X() << ',' << dir.Y() << ',' << dir.Z() << "\tdirMag: " << dirMag << "\tt*dir.magnitude(): " << tMag << "\n";
    //Vector endPosition = particle.position + (particle.velocity*dT);
            location = dir*intersectionDir/dirMag;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
 
}
