#include "nrooks.h"

void nrooks::generate_samples(const double exp)
{


	//在主对角线上产生samples
	for (int p = 0; p < num_sets; p++) {
		for (int j = 0; j < num_samples; j++) {
			TrekMath::point2 pv;
			//[0,1] / 25 ∈ [0,1/25]
			//[1,2] / 25 ∈ [1/25,2/25]
			//[2,3] / 25 ∈ [2/25,3/25]


			pv.x = (j + TrekMath::random_double()) / num_samples;
			pv.y = (j + TrekMath::random_double()) / num_samples;
			unit_square_samples.push_back(pv);

		}
	}
	shuffle_x_coordinates();
	shuffle_y_coordinates();



	map_square_samples_to_unit_disk();
	map_square_samples_to_hemisphere(exp);


}

void nrooks::shuffle_x_coordinates()
{

	for (int p = 0; p < num_sets; p++) {
		for (int i = 0; i < num_samples - 1; i++) {
			int target = samplePerPiexlDistribution(TrekMath::generator) + p * num_samples;

			std::swap(unit_square_samples[i + p * num_samples + 1].x, unit_square_samples[target].x);

			/*float temp = samples[i + p * num_samples + 1].x;
			samples[i + p * num_samples + 1].x = samples[target].x;
			samples[target].x = temp;*/


		}
	}

}

void nrooks::shuffle_y_coordinates()
{

	for (int p = 0; p < num_sets; p++) {
		for (int i = 0; i < num_samples - 1; i++) {
			int target = samplePerPiexlDistribution(TrekMath::generator) + p * num_samples;

			std::swap(unit_square_samples[i + p * num_samples + 1].y, unit_square_samples[target].y);

			/*float temp = samples[i + p * num_samples + 1].y;
			samples[i + p * num_samples + 1].y = samples[target].y;
			samples[target].y = temp;*/

		}
	}

}