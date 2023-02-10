#include "Box.h"
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

using namespace pba;

void Plane::Display()
{
    if (!isVisible) return;

	glBegin(GL_TRIANGLES);
        glColor3f(tri1.red(), tri1.green(), tri1.blue());
        glVertex3f(BL.X(), BL.Y(), BL.Z());
        glVertex3f(TL.X(), TL.Y(), TL.Z());
        glVertex3f(TR.X(), TR.Y(), TR.Z());

        glColor3f(tri2.red(), tri2.green(), tri2.blue());
        glVertex3f(TR.X(), TR.Y(), TR.Z());
        glVertex3f(BR.X(), BR.Y(), BR.Z());
        glVertex3f(BL.X(), BL.Y(), BL.Z());
	glEnd();
}
