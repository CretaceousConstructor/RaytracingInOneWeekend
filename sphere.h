#pragma once
#include "hittable.h"
#include "vec3.h"


class sphere : public hittable {
public:
    sphere() = default;
    sphere(point3 cen, double r, shared_ptr<material> m) : center(cen), radius(r), mat_ptr(m) {};

    virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const;

public:
    point3 center;
    double radius;
    shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().squared_length();
    auto half_b = vec3::dot(oc, r.direction());
    auto c = oc.squared_length() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant > 0) {
        auto root = sqrt(discriminant);
        auto temp = (-half_b - root) / a;// temp is the parameter t,and is the one that's smaller between the two possible intersecting points,and it's closer
        if (temp < t_max && temp > t_min) {
            rec.t = temp;                             // temp is the parameter t;
            rec.p = r.point_at_parameter(rec.t);      // intersecting point p;
            //set things up so that normals always point “outward” from the surface,
            //调整法线使得视线方向和法线总是呈现钝角
            vec3 outward_normal = (rec.p - center) / radius; // intersecting normal vector,normalized
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

