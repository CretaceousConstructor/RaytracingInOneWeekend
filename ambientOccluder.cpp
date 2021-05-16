#include "ambientOccluder.h"

TrekMath::vec3 ambientOccluder::get_direction(shadeRec& sr)
{
  

    TrekMath::point3 sp = sampler_ptr->sample_hemisphere();

    return (sp.x*u + sp.y*v + sp.z*w);

}

void ambientOccluder::set_sampler(std::unique_ptr<sampler>&& s_ptr)
{

    sampler_ptr = std::move(s_ptr);


}

bool ambientOccluder::in_shadow(const ray& r, const shadeRec& sr)
{

    double t;
    for (auto obj : sr.wor->objects) {
        if (obj->shadow_hit(r, t)) {
            return true;
        }
    }

    return false;
}

TrekMath::color ambientOccluder::L(shadeRec& sr)
{
    //��������ϵ
    w = sr.normal;
    v = glm::cross(w,TrekMath::vec3(0.0072,1.0,0.0034));//�����vec3��ѡ�񾡿��ܲ�Ҫ��w�غ�
    v = glm::normalize(v);
    u = glm::cross(v,w);
    //���������������
    ray shadow_ray;
    shadow_ray.setOrigin(sr.hitPoint);
    shadow_ray.setDir(get_direction(sr));

    if (in_shadow(shadow_ray,sr)) { //�������������˵�����ڱ���
        return min_amount* ls * cl;
    }
    else {
        return ls * cl;
    }


}
