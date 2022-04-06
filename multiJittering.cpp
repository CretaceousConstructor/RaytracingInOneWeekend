#include "multiJittering.h"

void multiJittering::generate_samples(const double exp)
{
	for (int p = 0; p < num_sets; p++) {
		for (int j = 0; j < sqrt_of_numSamples; j++) {
			for (int k = 0; k < sqrt_of_numSamples; k++) {
				TrekMath::point2 sp;
				//[12,13] ¡Ê [12 / 16,13 / 16]
				//[0,1]   ¡Ê [0      ,1/16]



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
	map_square_samples_to_hemisphere(exp);
}

