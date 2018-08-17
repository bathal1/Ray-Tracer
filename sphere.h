#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

class sphere: public hitable{
    public:
        vec3 center;
        vec3 color;
        float radius, radius_square;

        sphere(){}
        sphere(const vec3 &c, const vec3 &col, float r) : center(c), color(col), radius(r), radius_square(r*r){}

        virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
};

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    //checks wether ray r hits sphere s and where
    vec3 unit_direction = unit_vector(r.direction());//normalize direction vector
    vec3 cp = r.origin() - center;

    float b = dot(unit_direction,cp);
    float c = cp.squared_length()-radius_square;
    float delta = b*b - c; // not really delta, but the constants cancel each other in the following


    if (delta>=0){
        float t = -b - sqrt(delta); //closest solution to the eye
        if(t>t_min && t<t_max){
            //update hit record
            rec.t=t; //parameter
            rec.p = r.origin() + t*unit_direction; //hitpoint
            rec.normal = unit_vector(rec.p - center); //normal at the hitpoint
            return true;
        }

        t = -b + sqrt(delta); //furthest solution to the eye
        if(t>t_min && t<t_max){
            //update hit record
            rec.t=t; //parameter
            rec.p = r.origin() + t*unit_direction; //hitpoint
            rec.normal = unit_vector(rec.p - center); //normal at the hitpoint
            return true;
        }
    }
    return false;
}

#endif // SPHERE_H
