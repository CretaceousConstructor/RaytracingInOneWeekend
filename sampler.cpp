#include "sampler.h"

void sampler::map_square_samples_to_unit_disk()
{
	auto size = unit_square_samples.size();
	double r, phi;
	TrekMath::point2 sp;
	unit_disk_samples.resize(size);


	for (int j = 0; j < size; j++) {

		//map sample points from [0,1] [0,1]  to [-1,1] [-1,1]
		sp.x = 2.0 * unit_square_samples[j].x - 1.0;
		sp.y = 2.0 * unit_square_samples[j].y - 1.0;

		if (sp.x > -sp.y) 
		{
			if (sp.x > sp.y) {

				r = sp.x;
				phi = sp.y / sp.x;
			}
			else {
				r = sp.y;
				phi = 2. - sp.x / sp.y;
			}


		}
		else {

			if (sp.x < sp.y) {

				r = -sp.x;
				phi = 4. + sp.y / sp.x;
			}
			else {
				r = -sp.y;
				if (sp.y != 0.) {  //防止除0错误
					phi = 6 - sp.x / sp.y;
				}
				else {
					phi = 0.; //点在原点
				}

			}


		}

		phi *= (glm::pi<double>() /4.0);

		unit_disk_samples[j].x = r * glm::cos(phi);
		unit_disk_samples[j].y = r * glm::sin(phi);


	}



}

void sampler::map_square_samples_to_hemisphere(const double e)
{
	auto PI = glm::pi<double>();
	auto size = unit_square_samples.size();
	hemisphere_samples.reserve(num_samples * num_sets);



	for (int j = 0; j < size; j++) {

		double cos_phi = glm::cos(2.0 * PI * unit_square_samples[j].x);
		double sin_phi = glm::sin(2.0 * PI * unit_square_samples[j].x);
		double cos_theta = glm::pow((1.0 - unit_square_samples[j].y),1. / (e + 1.));
		double sin_theta = glm::sqrt(1.0 - cos_theta*cos_theta);
		double pu = sin_theta * cos_phi;
		double pv = sin_theta * sin_phi;
		double pw = cos_theta;


		hemisphere_samples.push_back(TrekMath::point3(pu,pv,pw));  //这里仅仅给定u ,v ,w轴的系数
	}


}
