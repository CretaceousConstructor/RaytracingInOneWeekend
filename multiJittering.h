#pragma once
#include "sampler.h"


class  multiJittering : public sampler
{
public:
	multiJittering() = delete;
	//一个set对应一个pixel
	multiJittering(int numSamples, int numSets)
		:sampler(numSamples, numSets),
		SquareRootOfSamplePerPiexlDistribution(0, static_cast<int>(glm::sqrt(numSamples)) - 1)
	{
		
		generate_samples();
		
	};

	

private:
	


	std::uniform_int_distribution<int> SquareRootOfSamplePerPiexlDistribution;
	virtual void generate_samples() override {
		for (int p = 0; p < num_sets; p++) {
			for (int j = 0; j < sqrt_of_numSamples; j++) {
				for (int k = 0; k < sqrt_of_numSamples; k++) {
					TrekMath::point2 sp;
					//[12,13] ∈ [12 / 16,13 / 16]
					//[0,1]   ∈ [0      ,1/16]



					//  y
					//  |
					//  |
					//  |------ x

					sp.x = (k * sqrt_of_numSamples + j + TrekMath::random_double()) / (sqrt_of_numSamples * sqrt_of_numSamples);
					sp.y = (j * sqrt_of_numSamples + k + TrekMath::random_double()) / (sqrt_of_numSamples * sqrt_of_numSamples);
					unit_square_samples.push_back(sp);
				}
			}
		}

		shuffle_x_coordinates();
		shuffle_y_coordinates();


		map_square_samples_to_unit_disk();
		map_square_samples_to_hemisphere();
	}


	


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

