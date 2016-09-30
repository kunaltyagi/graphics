#ifndef _VIEWPORT_HPP_
#define _VIEWPORT_HPP_

#include <glut/glut_framework.hpp>
#include <object.hpp>

struct Viewport: public glut_framework::GlutFramework
{
    using GF = glut_framework::GlutFramework;

    Viewport();

    void setBaseObj(ObjectPtr obj_) { _baseObject = obj_; }

    void load() { _baseObject->load(); }

    void setDisplayMatricies();

    void display(float dTime);

    void keyboardDown(unsigned char key, int x, int y);
protected:
    Point _bg;  // background color
    ObjectPtr _baseObject;
    bool firstRun = true;
};  // class Viewport

#endif  // _VIEWPORT_HPP_
