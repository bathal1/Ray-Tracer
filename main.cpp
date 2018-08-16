#include <iostream>

#include "vec3.h"
#include "ray.h"

using namespace std;

vec3 color(const ray &r){
    vec3 ray_unit_direction =
}

int main()
{
    int h = 200;
    int w = 100;
    cout << "P3\n" << h << " " << w << "\n255\n" ;
    for(int i = w-1 ; i>=0 ; i--){
        for(int j=0 ; j<h ; j++){
            float r = float(i)/float(w);
            float g = float(j)/float(h);
            float b = 0.2;
            vec3 col(r,g,b);
            float ir = int(col.r() * 255.99);
            float ig = int(col.g() * 255.99);
            float ib = int(col.b() * 255.99);
            cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
