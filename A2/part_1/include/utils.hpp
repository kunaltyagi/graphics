#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <cmath>

#define _FACTOR (180/M_PI)

constexpr float rad2deg(float angle)
{
    return _FACTOR*angle;
}

constexpr float deg2rad(float angle)
{
    return angle/_FACTOR;
}

#undef _FACTOR

#endif  // _UTILS_HPP_
