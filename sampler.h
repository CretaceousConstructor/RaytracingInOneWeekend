#pragma once
#include "TrekMath.h"
#include <vector>
#include <algorithm>
#include <exception>
class sampler {

public:
	sampler(int numSamples,int numSets)
		:
		num_samples(numSamples),
		num_sets(numSets),
		counter(0),
		samplePerPiexlDistribution(0, static_cast<int>(glm::sqrt(numSamples) * glm::sqrt(numSamples))  - 1 ),
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
	
	
	TrekMath::point2 sample_unit_square(void) {   //这是为了防止在水平或者竖直方向的像素上使用同样的sample set，会造成非常糟糕的效果

		if (counter % (num_samples) == 0) {
			///numset index * numSamples
			jump = setNumberDistribution(TrekMath::generator) * (num_samples);  //换sample set
		}

		auto index = shuffled_indices[(counter++ % (num_samples))]; //在一个set里面得到的随机混乱的下标
		return unit_square_samples[jump + index];
	}



	TrekMath::point2 sample_unit_disk(void) {   //这是为了防止在水平或者竖直方向的像素上使用同样的sample set，会造成非常糟糕的效果

		if (counter % (num_samples) == 0) {
			///numset index * numSamples
			jump = setNumberDistribution(TrekMath::generator) * (num_samples);  //换sample set
		}

		auto index = shuffled_indices[(counter++ % (num_samples))]; //在一个set里面得到的随机混乱的下标
		return unit_disk_samples[jump + index];
	}



	TrekMath::point3 sample_hemisphere(void) {   //这是为了防止在水平或者竖直方向的像素上使用同样的sample set，会造成非常糟糕的效果

		if (counter % (num_samples) == 0) {
			///numset index * numSamples
			jump = setNumberDistribution(TrekMath::generator) * (num_samples);  //换sample set
		}

		auto index = shuffled_indices[(counter++ % (num_samples))]; //在一个set里面得到的随机混乱的下标
		return hemisphere_samples[jump + index];
	}


	int get_num_of_samples_per() const {
		return num_samples;
	}

protected:
	virtual void generate_samples() = 0; // 
	int num_samples;
	int num_sets;  
	int jump;
	int sqrt_of_numSamples; //square root of numSamples
	size_t counter;
	std::vector<TrekMath::point2> unit_square_samples;
	std::vector<TrekMath::point2> unit_disk_samples;
	std::vector<TrekMath::point3> hemisphere_samples;
	std::vector<int> shuffled_indices;
	std::uniform_int_distribution<int> setNumberDistribution;
	std::uniform_int_distribution<int> samplePerPiexlDistribution;
	void calculate_num_samples() {

		 num_samples = sqrt_of_numSamples * sqrt_of_numSamples;
	}
	void setup_shuffled_indices() {  //为了防止在一个像素采样时一直遵循从左下角到右上角的顺序，这也可以消除两种采样数目不同造成的alias，比如这样就可以采用view plane 4jittered采样，光平面16 jittered采样

		shuffled_indices.reserve(num_samples * num_sets);

		std::vector<int> indices;
		indices.reserve(num_samples);
		// 0 1 2 3 4 5 --------15
		for (int j = 0; j < num_samples; j++) {

			indices.push_back(j);

		}

		for (int p = 0; p < num_sets; p++) {
			std::shuffle(indices.begin(), indices.end(),TrekMath::generator);
			for (auto index : indices) {

				shuffled_indices.push_back(index);
			}

		}

	

	}
	void map_square_samples_to_unit_disk();
	void map_square_samples_to_hemisphere(const double e = 1.0); 



};