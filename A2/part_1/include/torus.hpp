#ifndef _TORUS_HPP_
#define _TORUS_HPP_

#include <generic_object.hpp>

struct Torus: public GenericObject
{
    void load(void)
    {
        int numc = 8, numt = 25;
        int i, j, k;
        double s, t, x, y, z, twopi;

        twopi = 2 * (double)M_PI;
        for (i = 0; i < numc; i++)
        {
           glBegin(GL_QUAD_STRIP);
           for (j = 0; j <= numt; j++)
           {
              for (k = 1; k >= 0; k--)
              {
                 s = (i + k) % numc + 0.5;
                 t = j % numt;

                 x = (1+.1*cos(s*twopi/numc))*cos(t*twopi/numt);
                 y = (1+.1*cos(s*twopi/numc))*sin(t*twopi/numt);
                 z = .1 * sin(s * twopi / numc);
                 glVertex3f(x, y, z);
              }
           }
          glEnd();
        }
    }
    void _cleanup()
    {
        gluDeleteQuadric(qobj);
    }

    float base_radius = 0.5, top_radius = 0.5, height = 1.0;
    int slices = 15, stacks = 1;
    Torus(): GenericObject() {}
    Torus(float r_base, float r_top, float h, int slice, int stack = 1):
        GenericObject(), base_radius(r_base), top_radius(r_top), height(h),
        slices(slice), stacks(stack)
    {
        color.x = color.y = color.z = 0.8;
        color.w = 1.0;
    }
};  // class Torus

#endif  // _TORUS_HPP_
