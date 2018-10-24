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

bool refract(const vec3& v, const vec3& n, float n1_over_n2, vec3& refracted_ray){
    vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float vertical_refraction = 1.0f - (n1_over_n2*n1_over_n2)*(1.0f - dt*dt); // coordinate of the refracted ray along the normal

    if(vertical_refraction > 0){
        //if the ray is indeed refracted (according to Snell-Descartes' law)
        refracted_ray = -sqrt(vertical_refraction)*n + n1_over_n2*(uv - dt*n);
        return true;
    }
    //else
    return false;
}

float schlick(float cos, float ref_index){
    //compute the Schlick approximation of the reflection factor
    float r0 = (1.0f - ref_index) / (1.0f + ref_index);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1-cos),5);
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

class dielectric : public material{
    public:
        float ref_index;

        dielectric(float r) : ref_index(r) {}

        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const{
            float n1_over_n2;
            vec3 refracted;
            vec3 outward_normal;
            float ref_prob, cos;

            attenuation = vec3(1.0f, 1.0f, 1.0f);

            if(dot(r_in.direction(), rec.normal) > 0){//if it is an internal ray
                outward_normal = -rec.normal;
                n1_over_n2 = ref_index;
                cos = dot(r_in.direction(), rec.normal) / r_in.direction().length();
                cos = sqrt(1 - ref_index*ref_index*(1-cos*cos));
            }
            else{
                outward_normal = rec.normal;
                n1_over_n2 = 1.0f / ref_index;
                cos = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
            }

            if (refract(r_in.direction(), outward_normal, n1_over_n2, refracted)){
                ref_prob = schlick(cos, ref_index);
            }
            else{
                ref_prob =1.0f;
            }
            if(drand48() < ref_prob){
                vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);//reflexion
                //reflected+=fuzz*random_unit_vector();//add a little randomness to the reflection, will create some blur
                scattered = ray(rec.p, reflected);
            }
            else{
                scattered = ray(rec.p, refracted);
            }
            return true;
        }
};

#endif // MATERIAL_H
