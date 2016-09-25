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

        glColor3f (1.0, 1.0, 1.0);
        glShadeModel (GL_FLAT);
        glTranslatef(0.0, 10.0, 0.0);
        glPushMatrix();
        glRotatef(300.0, 1.0, 0.0, 0.0);
        glCallList(startList);
        glPopMatrix();

        glPopMatrix();
        glFlush();
        Object::draw();
    }
    void _init(void)
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
