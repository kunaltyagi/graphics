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

    void load()
    {
        _baseObject->load();
    }


    void setDisplayMatricies()
    {
        GF::setDisplayMatricies();
        if (firstRun)
        {
            glLoadIdentity();
            gluLookAt(eyeVector.x, eyeVector.y, eyeVector.z,
                    centerVector.x, centerVector.y, centerVector.z,
                    upVector.x, upVector.y, upVector.z);
            firstRun = false;
        }
    }

    void display(float dTime)
    {
        _baseObject->draw();
        glFlush();
        /* std::cout << dTime << '\n'; */
    }
    void keyboardDown(unsigned char key, int x, int y)
    {
        GF::keyboardDown(key, x, y);
        const float del_theta = 15;
        const float del_x = 1;
        switch(key)
        {
        case 'X': glRotatef(del_theta, 1.0, 0.0, 0.0); break;
        case 'x': glRotatef(-del_theta, 1.0, 0.0, 0.0); break;
        case 'Y': glRotatef(del_theta, 0.0, 1.0, 0.0); break;
        case 'y': glRotatef(-del_theta, 0.0, 1.0, 0.0); break;
        case 'Z': glRotatef(del_theta, 0.0, 0.0, 1.0); break;
        case 'z': glRotatef(-del_theta, 0.0, 0.0, 1.0); break;

        // make translations in view frame TODO
        case 'w': glTranslatef(del_x, 0.0, 0.0); break;
        case 's': glTranslatef(-del_x, 0.0, 0.0); break;
        case 'a': glTranslatef(0.0, del_x, 0.0); break;
        case 'd': glTranslatef(0.0, -del_x, 0.0); break;
        case 'q': glTranslatef(0.0, 0.0, del_x); break;
        case 'e': glTranslatef(0.0, 0.0, -del_x); break;

        case 'I': case 'i':
            glLoadIdentity();
            gluLookAt(eyeVector.x, eyeVector.y, eyeVector.z,
                    centerVector.x, centerVector.y, centerVector.z,
                    upVector.x, upVector.y, upVector.z);
            break;
        case 27:
            exit(0);
        }
        glutPostRedisplay();
    }
protected:
    Point _bg;  // background color
    ObjectPtr _baseObject;
    bool firstRun = true;
};  // class Viewport

#endif  // _VIEWPORT_HPP_
