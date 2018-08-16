#include <iostream>

#include "sphere.h"

using namespace std;

bool intersects(const sphere &s, const ray &r){
    vec3 unit_d = unit_vector(r.direction());
    vec3 cp = r.origin() - s.center();

    float b = dot(unit_d,cp);
    float c = cp.squared_length()-s.radius_square;
    float delta = b*b - c;
    return (delta >= 0.0f);

}

vec3 color(const ray &r, const sphere &s){
    if(intersects(s, r)){
        return s.color();// the ray hit the sphere
    }
    vec3 ray_unit_direction = unit_vector(r.direction());
    float t = 0.5f* (ray_unit_direction.y() + 1.0f);
    return (1.0f-t)*vec3(1.0f, 1.0f, 1.0f) + vec3(0.5f, 0.7f, 1.0f)*t;
}

int main()
{
    int nx = 200;
    int ny = 100;
    cout << "P3\n" << nx << " " << ny << "\n255\n" ;


    vec3 origin(0.0f, 0.0f, 0.0f);
    vec3 vertical(0.0f,2.0f, 0.0f);
    vec3 horizontal(4.0f,0.0f,0.0f);
    vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);

    sphere first_sphere(vec3(0.0f, 0.0f, -1.0f), vec3(0.2f, 0.4f, 0.3f), 0.5f);

    vec3 center = first_sphere.cent;
    for(int j = ny-1 ; j>=0 ; j--){
        for(int i=0 ; i<nx ; i++){
            float u = float(i)/float(nx);
            float v = float(j)/float(ny);

            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r, first_sphere);

            float ir = int(col.r() * 255.99);
            float ig = int(col.g() * 255.99);
            float ib = int(col.b() * 255.99);
            cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
