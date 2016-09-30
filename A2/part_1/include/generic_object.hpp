#ifndef _GENERIC_OBJECT_HPP_
#define _GENERIC_OBJECT_HPP_

#include <object.hpp>

struct GenericObject: public Object
{
    virtual void draw(void)
    {
        setFlags();
        glColor4f (color.x, color.y, color.z, color.w);

        glPushMatrix();
        transformObj();
        glCallList(_drawList);
        glPopMatrix();

        Object::draw();
    }

    virtual void transformObj(void)
    {
        glRotatef(_objPose.R.w, _objPose.R.x, _objPose.R.y, _objPose.R.z);
        glTranslatef(_objPose.T.x, _objPose.T.y, _objPose.T.z);
        glScalef(scale.x, scale.y, scale.z);
    }

    virtual void setFlags(void)
    {
        glEnable(GL_LIGHTING);
        /* glEnable(GL_COLOR_MATERIAL); */
        /* glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); */
        glShadeModel (GL_SMOOTH);
    }

    virtual void load(void)
    {
        setupMaterial();
        setupObject();
    }

    virtual void setupMaterial(void)
    {
        GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
        GLfloat mat_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess[] = { 50.0 };

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
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
    Vector scale = {1, 1, 1};
    // preferably don't access the public attributes, use ctor instead
    GenericObject(): Object() {}
    GenericObject(Vector vec): Object(), scale(vec) {}
    virtual ~GenericObject() {}

protected:
    GLuint _drawList;
    GLUquadric* qobj = nullptr;
};  // class GenericObject

#endif  // _GENERIC_OBJECT_HPP_
