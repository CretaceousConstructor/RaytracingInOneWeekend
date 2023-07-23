#pragma once
#include "TrekMath.h"
#include <algorithm>
#include <stdexcept>
#include <vector>
class sampler
{
  public:
	sampler()          = delete;
	virtual ~sampler() = 0;
	sampler(unsigned int numSamples, unsigned int numSets);

  public:
	TrekMath::point2 sample_unit_square();
	TrekMath::point2 sample_unit_disk();
	TrekMath::point3 sample_hemisphere();

	//get_num_of_samples_per_pixel
	[[nodiscard]] int get_num_of_samples_per_pix() const;
	[[nodiscard]] int get_num_of_sets() const;

  protected:
	virtual void generate_samples(const double exp = 1.0) = 0;        //
  protected:
	unsigned int                  num_samples;
	unsigned int                  num_sets;
	unsigned int                  sqrt_of_numSamples;        //square root of numSamples
	unsigned int                  counter{0};
	unsigned int                  jump{0};
	std::vector<TrekMath::point2> unit_square_samples;
	std::vector<TrekMath::point2> unit_disk_samples;
	std::vector<TrekMath::point3> hemisphere_samples;

	std::vector<size_t>                shuffled_indices;
	std::uniform_int_distribution<int> setNumberDistribution;
	std::uniform_int_distribution<int> samplePerPiexlDistribution;

  private:
	void calculate_num_samples();
	void setup_shuffled_indices();

  protected:
	void map_square_samples_to_unit_disk();
	void map_square_samples_to_hemisphere(const double e);
};