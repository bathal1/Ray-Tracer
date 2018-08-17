#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class camera{
    public:
        vec3 vertical;
        vec3 horizontal;
        vec3 bottom_left_corner;
        vec3 origin;

        camera(){
            origin = vec3(0.0f, 0.0f, 0.0f);
            vertical = vec3(0.0f,2.0f, 0.0f);
            horizontal = vec3(4.0f, 0.0f, 0.0f);
            bottom_left_corner = vec3(-2.0f, -1.0f, -1.0f);
        }

        ray get_ray(float u, float v){ return ray(origin, bottom_left_corner + u*horizontal + v*vertical - origin);}
};


#endif // CAMERA_H
