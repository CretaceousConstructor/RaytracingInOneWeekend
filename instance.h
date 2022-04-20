#pragma once

#include "hittable.h"
#include "transform.h"
#include <algorithm>
class instance : public hittable
{
  public:
	instance() = delete;
	explicit instance(std::shared_ptr<hittable> obj);
	bool        hit(const ray &r, double t_min, double t_max, shadeRec &sr) const override;
	std::string object_type() const override;

	void SetTranslation(const glm::vec3 &translation);
	void SetRotation(double x, double y, double z);
	void SetScale(double x, double y, double z);



	bool bounding_box(double time0, double time1, AABB &output_box) const override;




  private:
	transform                 trans;
	std::shared_ptr<hittable> object_ptr;

	bool transform_the_texturecor = false;



};
