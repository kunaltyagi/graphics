#ifndef _GENERIC_OBJECT_HPP_
#define _GENERIC_OBJECT_HPP_

#include <object.hpp>

struct GenericObject: public Object
{
    void draw(void)
    {
        setFlags();
        glColor4f (color.x, color.y, color.z, color.w);

        glPushMatrix();

        glPushMatrix();
        glRotatef(_objPose.R.w, _objPose.R.x,
                  _objPose.R.y, _objPose.R.z);
        glTranslatef(_objPose.T.x, _objPose.T.y, _objPose.T.z);
        glCallList(_drawList);
        glPopMatrix();

        glPopMatrix();
        Object::draw();
    }

    virtual void setFlags(void)
    {
        glEnable(GL_LIGHTING);
        glShadeModel (GL_FLAT);
    }

    virtual void load(void)
    {
        setupMaterial();
        setupObject();
    }

    virtual void setupMaterial(void)
    {
        GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess[] = { 50.0 };
        GLfloat model_ambient[] = { 0.5, 0.5, 0.5, 1.0 };

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
    }

    virtual void setupObject(void)
    {
        // sample setup
        /*
        _drawList = glGenLists(1);
        qobj = gluNewQuadric();

        gluQuadricDrawStyle(qobj, GLU_FILL);
        gluQuadricNormals(qobj, GLU_SMOOTH);
        glNewList(_drawList, GL_COMPILE);
        gluGenericObject(qobj, base_radius, top_radius, height, slices, stacks);
        glEndList();
        */
    }

    virtual void _cleanup() {}

    Point color;
    // preferably don't access the public attributes, use ctor instead
    GenericObject(): Object() {}
    virtual ~GenericObject() {}

protected:
    GLuint _drawList;
    GLUquadric* qobj = nullptr;
};  // class GenericObject

#endif  // _GENERIC_OBJECT_HPP_
