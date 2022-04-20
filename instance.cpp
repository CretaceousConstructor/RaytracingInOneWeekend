#include "instance.h"

instance::instance(std::shared_ptr<hittable> obj) :
    object_ptr(obj)
{
}

bool instance::hit(const ray &r, double t_min, double t_max, shadeRec &sr) const
{
	ray  inv_ray;
	auto trans_mat = trans.GetLocalToWorldMatrix();
	auto inv_mat   = glm::inverse(trans_mat);

	inv_ray.setOrigin(TrekMath::transform_point3(inv_mat, r.origin()));
	inv_ray.setDir(TrekMath::transform_vec3(inv_mat, r.direction()));

	if (object_ptr->hit(inv_ray, t_min, t_max, sr))
	{
		sr.normal = TrekMath::vec3(glm::transpose(inv_mat) * glm::vec4(sr.normal, 0.0));
		glm::normalize(sr.normal);
		sr.hitPoint = TrekMath::transform_point3(trans_mat, sr.hitPoint);
		sr.cast_ray = r;

		return true;
	}

	return false;
}

std::string instance::object_type() const
{
	return std::string{"instanced "} + object_ptr->object_type();
}

void instance::SetTranslation(const glm::vec3 &translation)
{
	trans.SetTranslation(translation);
	return;
}

void instance::SetRotation(double x, double y, double z)
{
	trans.SetRotation(x, y, z);
	return;
}

void instance::SetScale(double x, double y, double z)
{
	trans.SetScale(x, y, z);
	return;
}

bool instance::bounding_box(double time0, double time1, AABB &output_box) const
{
	bool result = object_ptr->bounding_box(time0, time1, output_box);

	if (!result)
	{
		return false;
	}

	auto min_point = output_box.min();
	auto max_point = output_box.max();

	std::vector<TrekMath::point3> set_of_points;
	double                        x_values[2] = {min_point.x, max_point.x};
	double                        y_values[2] = {min_point.y, max_point.y};
	double                        z_values[2] = {min_point.z, max_point.z};

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				set_of_points.push_back(TrekMath::point3(x_values[i], y_values[j], z_values[k]));
			}
		}
	}

	for (auto &p : set_of_points)
	{
		p = TrekMath::transform_point3(trans.GetLocalToWorldMatrix(), p);
	}

	auto x_comparator = [](const TrekMath::point3 &a, const TrekMath::point3 &b) -> bool { return a.x > b.x; };
	std::sort(std::begin(set_of_points),
	          std::end(set_of_points),
	          x_comparator);
	max_point.x = set_of_points.begin()->x;
	min_point.x = set_of_points.rbegin()->x;

	auto y_comparator = [](const TrekMath::point3 &a, const TrekMath::point3 &b) -> bool { return a.y > b.y; };
	std::sort(std::begin(set_of_points),
	          std::end(set_of_points),
	          y_comparator);
	max_point.y = set_of_points.begin()->y;
	min_point.y = set_of_points.rbegin()->y;

	auto z_comparator = [](const TrekMath::point3 &a, const TrekMath::point3 &b) -> bool { return a.z > b.z; };
	std::sort(std::begin(set_of_points),
	          std::end(set_of_points),
	          z_comparator);
	max_point.z = set_of_points.begin()->z;
	min_point.z = set_of_points.rbegin()->z;

	output_box = AABB{min_point, max_point};

	return result;
}
