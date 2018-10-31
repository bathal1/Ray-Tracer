#include <iostream>


#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "material.h"

using namespace std;

vec3 color(const ray &r, hitable *world, int depth){
    hit_record rec;
    if(world->hit(r, 0.001f, FLT_MAX, rec)){// if an intersection exists, and it's in front of the camera
        ray scattered;
        vec3 attenuation;
        if(depth<50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)){
            return attenuation * color(scattered, world, depth+1);
        }
        else{
            return vec3(0,0,0);
        }
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
    int ns = 15; //number of samples for antialiasing

    cout << "P3\n" << nx << " " << ny << "\n255\n" ;

    float R = 0.5f;
    hitable *list[4];
    list[0] = new sphere(vec3(0.0f, -100.0f - R, -1.0f), 100.0f, new lambertian(vec3(0.8f,0.8f,0.0f)));
    list[1] = new sphere(vec3(0.0f,0.0f,-1.0f),R, new lambertian(vec3(0,0,1)));
    list[2] = new sphere(vec3(2*R,0.0f,-1.0f),R, new metal(vec3(1,1,1), 0.0f));
    list[3] = new sphere(vec3(-2*R,0.0f,-1.0f),R, new dielectric(1.5f));
    hitable *world = new hitable_list(list,4);

    camera cam(vec3(-2,2,1), vec3(0.0f,0.0f,-1.0f),vec3(0.0f,1.0f,0.0f),20, float(nx)/float(ny));
    for(int j = ny-1 ; j>=0 ; j--){
        for(int i=0 ; i<nx ; i++){
            float u = float(i)/float(nx);
            float v = float(j)/float(ny);
            vec3 col(0,0,0);
            for(int k =0; k<ns; k++){
                float u = float(i + drand48())/float(nx); //add a random seed
                float v = float(j + drand48())/float(ny);
                ray r = cam.get_ray(u,v);
                col += color(r, world,0);
            }
            col /= ns;
            col = vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));
            float ir = int(col.r() * 255.99);
            float ig = int(col.g() * 255.99);
            float ib = int(col.b() * 255.99);
            cout << ir << " " << ig << " " << ib << endl;
        }
    }
}
