#include <iostream>

#include "ray.h"

using namespace std;

vec3 color(const ray &r){
    vec3 ray_unit_direction = unit_vector(r.direction());
    float t = 0.5f* (ray_unit_direction.y() + 1.0f);
    return (1.0f-t)*vec3(1.0f, 1.0f, 1.0f) + vec3(0.5f, 0.7f, 1.0f)*t;
}

int main()
{
    int h = 200;
    int w = 100;
    cout << "P3\n" << h << " " << w << "\n255\n" ;


    vec3 origin(0.0f, 0.0f, 0.0f);
    vec3 vertical(2.0f,0.0f, 0.0f);
    vec3 horizontal(0.0f,4.0f,0.0f);
    vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);


    for(int i = w-1 ; i>=0 ; i--){
        for(int j=0 ; j<h ; j++){
            float u = float(i)/float(w);
            float v = float(j)/float(h);

            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r);

            float ir = int(col.r() * 255.99);
            float ig = int(col.g() * 255.99);
            float ib = int(col.b() * 255.99);
            cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
