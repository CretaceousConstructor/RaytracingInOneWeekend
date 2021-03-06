#pragma once
#include "hittable.h"
#include "TrekMath.h"


class sphere : public hittable {
public:
    sphere() = default;
    sphere(TrekMath::point3 cen, double r, std::shared_ptr<material> m)
        
        : 
        hittable(m),
        center(cen), radius(r)
    {
    }

     bool hit(const ray& r, double tmin, double tmax, shadeRec& sr) const override;
     bool shadow_hit(const ray& r, double& t_shadow) const override;
public:
    TrekMath::point3 center;
    double radius;
 
    virtual std::string objectType() const override;
private:
    static constexpr double kEpsilon = 0.00001;

};

