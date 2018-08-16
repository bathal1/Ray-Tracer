#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray{
    public:
        vec3 O;
        vec3 D;

        ray(){}
        ray(const vec3 &o, const vec3 &d){O=o; D=d;}

        vec3 origin() const {return O;}
        vec3 direction() const {return D;}

        vec3 point_at_parameter(float t) {return O + t*D;}
};

#endif // RAY_H
