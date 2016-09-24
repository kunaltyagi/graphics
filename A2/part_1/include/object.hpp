#include <cmath>
#include <iostream>
#include <cstdlib>
#include <GL/glut.h>

#include <memory>

class Object
{
public:
    virtual void draw(void);
};

using ObjectPtr = std::shared_ptr<Object>;
