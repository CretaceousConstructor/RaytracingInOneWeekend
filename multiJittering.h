#pragma once
#include "sampler.h"


class  multiJittering : public sampler
{
public:
	multiJittering() = delete;
	//一个pixel用一个set
	multiJittering(int numSamples, int numSets)
		:sampler(numSamples, numSets),
		SquareRootOfSamplePerPiexlDistribution(0, static_cast<int>(glm::sqrt(numSamples)) - 1)
	{
		
		generate_samples();
		
	};

	multiJittering(int numSamples, int numSets,const double exp)
		:sampler(numSamples, numSets),
		SquareRootOfSamplePerPiexlDistribution(0, static_cast<int>(glm::sqrt(numSamples)) - 1)
	{

		generate_samples(exp);

	};

private:
	


	std::uniform_int_distribution<int> SquareRootOfSamplePerPiexlDistribution;
	virtual void generate_samples(const double exp = 1.0) override;

	


	void shuffle_x_coordinates() {

		for (int p = 0; p < num_sets; p++) {

			shuffle_x_column(p * num_samples);

		}

	}

	void shuffle_x_column(int base) {
		for (int i = 0; i < sqrt_of_numSamples; i++) {  //four columns
			for (int j = 0; j < sqrt_of_numSamples ; j++)//shuffle counts from bottom to top 
			{

				int target = SquareRootOfSamplePerPiexlDistribution(TrekMath::generator) * sqrt_of_numSamples + i;
				std::swap(unit_square_samples[base + j * sqrt_of_numSamples  + i].x, unit_square_samples[base + target].x);
			}

		}
	
	}


	void shuffle_y_coordinates() {

		for (int p = 0; p < num_sets; p++) {
			shuffle_y_row(p * num_samples);
		}

	}

	void shuffle_y_row(int base) {
		for (int i = 0; i < sqrt_of_numSamples; i++) {  //four rows
			for (int j = 0; j < sqrt_of_numSamples; j++)//shuffle 
			{

				int target = SquareRootOfSamplePerPiexlDistribution(TrekMath::generator)  +  i * sqrt_of_numSamples;
				std::swap(unit_square_samples[base + i * sqrt_of_numSamples + j].x, unit_square_samples[base + target].x);
			}

		}

	}






};

