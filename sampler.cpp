#include "sampler.h"

sampler::sampler(int numSamples, int numSets)
	:
	num_samples(numSamples),
	num_sets(numSets),
	counter(0),
	samplePerPiexlDistribution(0, static_cast<int>(glm::sqrt(numSamples)* glm::sqrt(numSamples)) - 1),
	setNumberDistribution(0, numSets - 1), //[0,numSets)
	sqrt_of_numSamples(static_cast<int>(glm::sqrt(numSamples))),
	jump(0)
{
	if (numSamples < 1 || numSets < 1) {
		throw "Too small a number";
	}
	calculate_num_samples();
	setup_shuffled_indices();
}

TrekMath::point2 sampler::sample_unit_square(void)
{
	if (counter % (num_samples) == 0) {//����Ϊ�˷�ֹ��ˮƽ������ֱ�����������ʹ��ͬ����sample set������ɷǳ�����Ч��
		///numset index * numSamples
		jump = setNumberDistribution(TrekMath::generator) * num_samples;  //jump��Ϊ�˻�sample set
	}

	auto index = shuffled_indices[(counter++ % (num_samples))]; //��ĳһ��set����õ���������ҵ��±꣨���������Ϊ16�����±귶Χ����[0,15])
	return unit_square_samples[jump + index];
}

TrekMath::point2 sampler::sample_unit_disk(void)
{   //����Ϊ�˷�ֹ��ˮƽ������ֱ�����������ʹ��ͬ����sample set������ɷǳ�����Ч�� 
	if (counter % (num_samples) == 0) {
		///numset index * numSamples
		jump = setNumberDistribution(TrekMath::generator) * (num_samples);  //��sample set
	}

	auto index = shuffled_indices[(counter++ % (num_samples))]; //��һ��set����õ���������ҵ��±�
	return unit_disk_samples[jump + index];
}

TrekMath::point3 sampler::sample_hemisphere(void)
{   //����Ϊ�˷�ֹ��ˮƽ������ֱ�����������ʹ��ͬ����sample set������ɷǳ�����Ч��

	if (counter % (num_samples) == 0) {
		///numset index * numSamples
		jump = setNumberDistribution(TrekMath::generator) * (num_samples);  //��sample set
	}

	auto index = shuffled_indices[(counter++ % (num_samples))]; //��һ��set����õ���������ҵ��±�
	return hemisphere_samples[jump + index];
}

int sampler::get_num_of_samples_per_pix() const
{
	return num_samples;
}

int sampler::get_num_of_sets() const
{
	return num_sets;
}




void sampler::calculate_num_samples()
{

	num_samples = sqrt_of_numSamples * sqrt_of_numSamples;
}

void sampler::setup_shuffled_indices()
{  //Ϊ�˷�ֹ��һ�����ز���ʱһֱ��ѭ�����½ǵ����Ͻǵ�˳����Ҳ�����������ֲ�����Ŀ��ͬ��ɵ�alias�����������Ϳ���ʵ��plane 4jittered��������ƽ��16 jittered����

	shuffled_indices.reserve(num_samples * num_sets);

	std::vector<int> indices;
	indices.reserve(num_samples);
	// 0 1 2 3 4 5 --------15
	for (int j = 0; j < num_samples; j++) {

		indices.push_back(j);

	}

	for (int p = 0; p < num_sets; p++) {
		std::shuffle(indices.begin(), indices.end(), TrekMath::generator);
		for (auto index : indices) {
			shuffled_indices.push_back(index);
		}

	}



}

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
				if (sp.y != 0.) {  //��ֹ��0����
					phi = 6 - sp.x / sp.y;
				}
				else {
					phi = 0.; //����ԭ��
				}

			}


		}

		phi *= (glm::pi<double>() / 4.0);

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
		double cos_theta = glm::pow((1.0 - unit_square_samples[j].y), 1. / (e + 1.));
		double sin_theta = glm::sqrt(1.0 - cos_theta * cos_theta);
		double pu = sin_theta * cos_phi;
		double pv = sin_theta * sin_phi;
		double pw = cos_theta;


		hemisphere_samples.push_back(TrekMath::point3(pu, pv, pw));  //�����������u ,v ,w���ϵ��
	}


}
