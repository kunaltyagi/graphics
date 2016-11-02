#ifndef _GENERIC_OBJECT_HPP_
#define _GENERIC_OBJECT_HPP_

#include <object.hpp>

struct GenericObject: public Object
{
    virtual void draw(void);

    virtual void drawObject(void) {}

    virtual void transformObj(void);

    virtual void setFlags(void);

    virtual void load(void);

    virtual void setupMaterial(void);

    virtual void setupObject(void)
    {
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
