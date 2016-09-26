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
        glEnable(GL_LIGHTING);
        glColor3f (1.0, 1.0, 1.0);
        glShadeModel (GL_FLAT);

        glPushMatrix();

        glPushMatrix();
        glRotatef(_objPose.R.w, _objPose.R.x,
                  _objPose.R.y, _objPose.R.z);
        glTranslatef(_objPose.T.x, _objPose.T.y, _objPose.T.z);
        glCallList(startList);
        glPopMatrix();

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
        gluCylinder(qobj, base_radius, top_radius, height, slices, stacks);
        glEndList();
    }
    void _cleanup()
    {
        gluDeleteQuadric(qobj);
    }
    GLuint startList;
    GLUquadric* qobj;
    float base_radius = 0.5, top_radius = 0.5, height = 1.0;
    int slices = 15, stacks = 1;
};  // class Cylinder

#endif  // _CYLINDER_HPP_
