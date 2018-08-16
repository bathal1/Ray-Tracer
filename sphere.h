#ifndef SPHERE_H
#define SPHERE_H

#include "ray.h"

class sphere{
    public:
        vec3 cent;
        vec3 col;
        float radius, radius_square;

        sphere(){}
        sphere(const vec3 &c, const vec3 &color, float r){cent = c; col = color; radius = r; radius_square = r*r;}

        vec3 color() const {return col;}
        vec3 center() const {return cent;}
        float r() const {return radius;}
        float r2() const {return radius_square;}
};

#endif // SPHERE_H
