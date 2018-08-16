#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray{
    public:
        vec3 origin;
        vec3 direction;

        ray(){}
        ray(const vec3 &o, const vec3 &d){origin=o; direction=d;}

        vec3 origin() const {return origin;}
        vec3 direction() const {return direction;}

        vec3 point_at_parameter(float t) {return origin + t*direction;}
}

#endif // RAY_H
