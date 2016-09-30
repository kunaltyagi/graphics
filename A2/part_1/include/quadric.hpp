#ifndef _QUADRIC_HPP_
#define _QUADRIC_HPP_

#include <object.hpp>

void errorCallback()
{
   exit(0);
}

struct Quadric: public Object
{
    void draw(void)
    {
        glPushMatrix();
        /* glTranslatef(-1.0, -1.0, 0.0); */

        glCallList(startList);

        glShadeModel (GL_FLAT);
        glTranslatef(0.0, 2.0, 0.0);
        glPushMatrix();
        glRotatef(300.0, 1.0, 0.0, 0.0);
        glCallList(startList+1);
        glPopMatrix();

        glDisable(GL_LIGHTING);
        glColor3f(0.0, 1.0, 1.0);
        glTranslatef(2.0, 2.0, 0.0);
        glCallList(startList+2);

        glColor3f(1.0, 1.0, 0.0);
        glTranslatef(-4.0, 2.0, 0.0);
        glCallList(startList+3);

        glPopMatrix();
        glFlush();
        Object::draw();
    }
    void load(void)
    {
        GLUquadricObj *qobj;
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

        /* Create 4 display lists, each with a different quadric object.
         * Different drawing styles and surface normal specifications
         * are demonstrated.
         */
        startList = glGenLists(4);
        qobj = gluNewQuadric();
        gluQuadricCallback(qobj, GLU_ERROR, errorCallback);

        gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
        gluQuadricNormals(qobj, GLU_SMOOTH);
        glNewList(startList, GL_COMPILE);
        gluSphere(qobj, 0.75, 15, 10);
        glEndList();

        gluQuadricDrawStyle(qobj, GLU_FILL); /* flat shaded */
        gluQuadricNormals(qobj, GLU_FLAT);
        glNewList(startList+1, GL_COMPILE);
        gluQuadric(qobj, 0.5, 0.3, 1.0, 15, 5);
        glEndList();

        gluQuadricDrawStyle(qobj, GLU_LINE); /* wireframe */
        gluQuadricNormals(qobj, GLU_NONE);
        glNewList(startList+2, GL_COMPILE);
        gluDisk(qobj, 0.25, 1.0, 20, 4);
        glEndList();

        gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);
        gluQuadricNormals(qobj, GLU_NONE);
        glNewList(startList+3, GL_COMPILE);
        gluPartialDisk(qobj, 0.0, 1.0, 20, 4, 0.0, 225.0);
        glEndList();
    }
    GLuint startList;
};  // class Quadric

#endif  // _QUADRIC_HPP_
