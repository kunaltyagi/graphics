#ifndef _VIEWPORT_HPP_
#define _VIEWPORT_HPP_

#include <glut/glut_framework.hpp>
#include <object.hpp>

struct Viewport: public glut_framework::GlutFramework
{
    using GF = glut_framework::GlutFramework;

    Viewport(): GF()
    {
        this->setTitle("Assignment 2 (I)");
    }

    void setBaseObj(ObjectPtr obj_) { _baseObject = obj_; }

    void display(float dTime)
    {
        _baseObject->draw();
        std::cout << dTime << '\n';
    }
    void keyboardDown(unsigned char key, int x, int y)
    {
        GF::keyboardDown(key, x, y);
        switch(key)
        {
        case 'X':
            glRotatef(30.,1.0,0.0,0.0);
            glutPostRedisplay();
            break;
        case 'Y':
            glRotatef(30.,0.0,1.0,0.0);
            glutPostRedisplay();
            break;
        case 'I':
            glLoadIdentity();
            glutPostRedisplay();
            gluLookAt(eyeVector.x, eyeVector.y, eyeVector.z,
                    centerVector.x, centerVector.y, centerVector.z,
                    upVector.x, upVector.y, upVector.z);
            break;
        case 27:
            exit(0);
        }
    }
protected:
    Point _bg;  // background color
    ObjectPtr _baseObject;
};  // class Viewport

#endif  // _VIEWPORT_HPP_
