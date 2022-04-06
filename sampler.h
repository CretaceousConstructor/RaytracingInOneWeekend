#pragma once
#include "TrekMath.h"
#include <vector>
#include <algorithm>
#include <exception>
class sampler {

public:
	sampler() = delete;
	virtual ~sampler() = default;
	sampler(int numSamples, int numSets);
	
	
	TrekMath::point2 sample_unit_square(void);
	TrekMath::point2 sample_unit_disk(void);
	TrekMath::point3 sample_hemisphere(void);

	//get_num_of_samples_per_pixel
	int get_num_of_samples_per_pix() const;
	int get_num_of_sets() const;

protected:
	virtual void generate_samples(const double exp = 1.0) = 0; // 
	int num_samples;
	int num_sets;  
	int sqrt_of_numSamples; //square root of numSamples
	size_t counter = 0;
	int jump = 0 ;
	std::vector<TrekMath::point2> unit_square_samples;
	std::vector<TrekMath::point2> unit_disk_samples;
	std::vector<TrekMath::point3> hemisphere_samples;
	std::vector<int> shuffled_indices;
	std::uniform_int_distribution<int> setNumberDistribution;
	std::uniform_int_distribution<int> samplePerPiexlDistribution;
	
	void calculate_num_samples();
	void setup_shuffled_indices();

	void map_square_samples_to_unit_disk();
	void map_square_samples_to_hemisphere(const double e); 



};