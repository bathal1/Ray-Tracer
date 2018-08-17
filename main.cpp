#include <iostream>

#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"

using namespace std;

vec3 color(const ray &r, hitable *world){
    hit_record rec;
    if(world->hit(r, 0.0f, MAXFLOAT, rec)){// if an intersection exists, and it's in front of the camera
        return 0.5f*(rec.normal + vec3(1.0f,1.0f,1.0f));
    }
    //else display the background
    vec3 ray_unit_direction = unit_vector(r.direction());
    float t = 0.5f* (ray_unit_direction.y() + 1.0f);
    return (1.0f-t)*vec3(1.0f, 1.0f, 1.0f) + vec3(0.5f, 0.7f, 1.0f)*t;
}

int main()
{
    int nx = 200;
    int ny = 100;
    cout << "P3\n" << nx << " " << ny << "\n255\n" ;

    hitable *list[2];
    list[0] = new sphere(vec3(0.0f, -100.5f, -1.0f), vec3(0.2f, 0.4f, 0.3f), 100.0f);
    list[1] = new sphere(vec3(0.0f, 0.0f, -1.0f), vec3(0.2f, 0.4f, 0.3f), 0.5f);

    hitable *world = new hitable_list(list,2);

    camera cam;
    for(int j = ny-1 ; j>=0 ; j--){
        for(int i=0 ; i<nx ; i++){
            float u = float(i)/float(nx);
            float v = float(j)/float(ny);

            ray r = cam.get_ray(u,v);
            vec3 col = color(r, world);

            float ir = int(col.r() * 255.99);
            float ig = int(col.g() * 255.99);
            float ib = int(col.b() * 255.99);
            cout << ir << " " << ig << " " << ib << endl;
        }
    }
}
