#ifndef _CYLINDER_HPP_
#define _CYLINDER_HPP_

#include <object.hpp>

void errorCallback()
{
   exit(0);
}

struct Cylinder: public Object
{
    void draw(void)
    {
        glPushMatrix();

        int numc = 8, numt = 25;
       int i, j, k;
       double s, t, x, y, z, twopi;

       twopi = 2 * (double)M_PI;
       for (i = 0; i < numc; i++) {
          glBegin(GL_QUAD_STRIP);
          for (j = 0; j <= numt; j++) {
             for (k = 1; k >= 0; k--) {
                s = (i + k) % numc + 0.5;
                t = j % numt;

                x = (1+.1*cos(s*twopi/numc))*cos(t*twopi/numt);
                y = (1+.1*cos(s*twopi/numc))*sin(t*twopi/numt);
                z = .1 * sin(s * twopi / numc);
                glVertex3f(x, y, z);
             }
          }
          glEnd();
       }
        /* glEnable(GL_LIGHTING); */
        /* glColor3f (1.0, 1.0, 1.0); */
        /* glShadeModel (GL_FLAT); */
        /* glTranslatef(0.0, 10.0, 0.0); */
        /* glPushMatrix(); */
        /* glRotatef(300.0, 1.0, 0.0, 0.0); */
        /* glCallList(startList); */
        /* glPopMatrix(); */

        glPopMatrix();
        Object::draw();
    }
    void load(void)
    {
        GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess[] = { 50.0 };
        GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
        GLfloat model_ambient[] = { 0.5, 0.5, 0.5, 1.0 };

        glClearColor(0.0, 0.0, 0.0, 0.0);

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

        /* Create 4 display lists, each with a different cylinder object.
         * Different drawing styles and surface normal specifications
         * are demonstrated.
         */
        startList = glGenLists(1);
        qobj = gluNewQuadric();
        gluQuadricCallback(qobj, GLU_ERROR, errorCallback);

        gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
        gluQuadricNormals(qobj, GLU_SMOOTH);
        glNewList(startList, GL_COMPILE);
        gluCylinder(qobj, 0.5, 0.3, 1.0, 15, 5);
        glEndList();
    }
    void _cleanup()
    {
        gluDeleteQuadric(qobj);
    }
    GLuint startList;
    GLUquadric* qobj;
};  // class Cylinder

#endif  // _CYLINDER_HPP_
