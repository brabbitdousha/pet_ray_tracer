#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"
#include "hittable.h"
#include "texture.h"
#include "onb.h"

struct hit_record;

class material {
    public:
        virtual color emitted(double u, double v, const point3& p) const {
            return color(0,0,0);
        }
        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& albedo, ray& scattered, double& pdf
        ) const {
            return false;
        }

        virtual double scattering_pdf(
            const ray& r_in, const hit_record& rec, const ray& scattered
        ) const {
            return 0;
        }

};

class lambertian:public material
{
    public:
    lambertian(const color& a): albedo(make_shared<solid_color>(a)){}
    lambertian(shared_ptr<texture> a):albedo(a) {}
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& alb, ray& scattered, double& pdf
    )const override
    {  /*
        auto scatter_direction=rec.normal+random_unit_vector();

        if(scatter_direction.near_zero())
        scatter_direction=rec.normal;
 
        scattered=ray(rec.p,unit_vector(scatter_direction),r_in.time());
        alb=albedo->value(rec.u,rec.v,rec.p);
        pdf=dot(rec.normal,scattered.direction())/pi;
        */

       /*
       auto direction=random_in_hemisphere(rec.normal);
       scattered=ray(rec.p,unit_vector(direction),r_in.time());
       alb=albedo->value(rec.u,rec.v,rec.p);
       pdf=0.5/pi;
       */
       

      
      onb uvw;
      uvw.build_from_w(rec.normal);
      auto direction=uvw.local(random_cosine_direction());
      scattered = ray(rec.p, unit_vector(direction), r_in.time());
      alb = albedo->value(rec.u, rec.v, rec.p);
      pdf = dot(uvw.w(), scattered.direction()) / pi;
      

        return true;
    }
    double scattering_pdf(
        const ray& r_in,const hit_record& rec,const ray& scattered
    )const{
        auto cosine=dot(rec.normal,unit_vector(scattered.direction()));
        return cosine<0? 0:cosine/pi;
    }
    public:
    shared_ptr<texture> albedo;
};

class diffuse_light:public material
{
    public:
    diffuse_light(shared_ptr<texture> a): emit(a) {}
    diffuse_light(color c):emit(make_shared<solid_color>(c)){}

    virtual color emitted(double u, double v, const point3& p) const override {
            return emit->value(u, v, p);
        }

    public:
        shared_ptr<texture> emit;
};


#endif