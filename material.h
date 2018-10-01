#ifndef MATERIAL_H
#define MATERIAL_H


#include "ray.h"
#include "hitable.h"

vec3 random_unit_vector(){
    vec3 v;
    do{
        v = 2.0f*vec3(drand48(), drand48(), drand48()) - vec3(1.0f, 1.0f, 1.0f);
    }while(v.squared_length() > 1);
    return v;
}

vec3 reflect(const vec3& v, const vec3& n){
    return v - 2*dot(v,n)*n;
}


class material{
    public:
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const =0;
};

class lambertian : public material{
    public:
        vec3 albedo;

        lambertian(const vec3& a) : albedo(a) {}

        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const{
            vec3 target = rec.p + random_unit_vector() + rec.normal;
            scattered = ray(rec.p, target - rec.p);
            attenuation = albedo;
            return true;
        }
};

class metal : public material{
    public:
        vec3 albedo;
        float fuzz;

        metal(const vec3& a, float f) : albedo(a) {if(f<1.0f){fuzz=f;} else{fuzz=1.0f;}}

        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const{
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);//reflexion
            reflected+=fuzz*random_unit_vector();//add a little randomness to the reflection, will create some blur
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return dot(scattered.direction(), rec.normal) >0;
        }

};

#endif // MATERIAL_H
