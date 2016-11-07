#ifndef _COMBO_HPP_
#define _COMBO_HPP_

#include <generic_object.hpp>
#include <cylinder.hpp>
#include <sphere.hpp>

struct Combo: public GenericObject
{
    void setupObject(void)
    {
        cylinder.setupObject();
        GenericObject::setupObject();
    }

    void setupMaterial(void)
    {
        cylinder.setupMaterial();
    }

    void drawObject()
    {
        cylinder.draw();
    }

    void input(int key)
    {
        float inp = 0;
        switch(key)
        {
        case 'v': inp = -0.5; break;
        case 'b': inp = 0.5; break;
        }
        _jointVec[0]->manipulate(inp);
    }

    Cylinder cylinder;
    Combo(): GenericObject()
    {
        Pose far;
        far.T.x = 5;
        addJoint(std::make_shared<TranslateJoint>());
        /* _jointVec[0]->replaceParent(std::make_shared<Cylinder>()); */
        _jointVec[0]->replaceChild(std::make_shared<Sphere>());
        _jointVec[0]->setAxis({1, 0, 0});
        _jointVec[0]->setOffset(far);

        color.x = color.y = color.z = 0.9;
        color.w = 1.0;
    }
};  // class Combo

#endif  // _COMBO_HPP_
