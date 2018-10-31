#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

using namespace std;
class camera{
    public:
        vec3 vertical;
        vec3 horizontal;
        vec3 bottom_left_corner;
        vec3 origin;

        camera(vec3 lookFrom, vec3 lookAt, vec3 vup, float vfov, float aspect){
            //focal : focal length, vfov: verticla angle of view (in degrees), aspect: aspect ratio
            vec3 u, v, w;
            float theta = vfov * M_PI/180.0f;
            float height = tan(theta/2.0f);
            float width = aspect * height;

            w = unit_vector(lookFrom-lookAt);
            u = unit_vector(cross(vup,w));
            v = cross(w,u);

            origin = lookFrom;
            vertical = 2 * height * v;
            horizontal = 2 * width * u;
            bottom_left_corner = origin - width*u - height*v - w ;
        }

        ray get_ray(float u, float v){ return ray(origin, bottom_left_corner + u*horizontal + v*vertical - origin);}
};


#endif // CAMERA_H
