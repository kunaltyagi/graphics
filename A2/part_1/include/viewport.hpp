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

    void displayFramework()
    {
        if (this->displayTimer.isStopped())
        {
            this->displayTimer.start();
        }

        glClearColor(_bg.x, _bg.y, _bg.z, _bg.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->displayTimer.stop();
        this->elapsedTimeInSeconds = this->displayTimer.getElapsedSeconds();

        setupLights();
        setDisplayMatricies();

        _baseObject->draw();

        glutSwapBuffers();
        this->displayTimer.start();
    }
protected:
    Point _bg;  // background color
    ObjectPtr _baseObject;
};  // class Viewport

#endif  // _VIEWPORT_HPP_
