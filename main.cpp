#include <iostream>

#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"

using namespace std;

vec3 random_vector(){
    vec3 v;
    do{
        v = 2.0f*vec3(drand48(), drand48(), drand48()) - vec3(1.0f, 1.0f, 1.0f);
    }while(v.squared_length() > 1);
    return v;
}

vec3 color(const ray &r, hitable *world){
    hit_record rec;
    if(world->hit(r, 0.001f, MAXFLOAT, rec)){// if an intersection exists, and it's in front of the camera
        vec3 target = rec.p + random_vector();
        return 0.5f*color(ray(rec.p, random_vector() + rec.normal), world);
    }
    //else display the background
    vec3 ray_unit_direction = unit_vector(r.direction());
    float t = 0.5f* (ray_unit_direction.y() + 1.0f);
    return (1.0f-t)*vec3(1.0f, 1.0f, 1.0f) + vec3(0.2f, 0.7f, 1.0f)*t;
}

int main()
{

    int nx = 500;
    int ny = 250;//canvas dimenensions
    int ns = 100; //number of samples for antialiasing

    cout << "P3\n" << nx << " " << ny << "\n255\n" ;

    hitable *list[2];
    list[0] = new sphere(vec3(0.0f, -100.5f, -1.0f), vec3(0.2f, 0.4f, 0.3f), 100.0f);
    list[1] = new sphere(vec3(0.0f, 0.0f, -1.0f), vec3(0.2f, 0.4f, 0.3f), 0.5f);

    hitable *world = new hitable_list(list,2);
    camera cam;
    int ns = 10; //number of samples for antialiasing
    for(int j = ny-1 ; j>=0 ; j--){
        for(int i=0 ; i<nx ; i++){
            float u = float(i)/float(nx);
            float v = float(j)/float(ny);

            vec3 col(0,0,0);
            for(int k =0; k<ns; k++){
                float u = float(i + drand48())/float(nx); //add a random seed
                float v = float(j + drand48())/float(ny);
                ray r = cam.get_ray(u,v);
                col += color(r, world);
            }
            col /= ns;
            col = vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b());
            float ir = int(col.r() * 255.99);
            float ig = int(col.g() * 255.99);
            float ib = int(col.b() * 255.99);
            cout << ir << " " << ig << " " << ib << endl;
        }
    }
}
