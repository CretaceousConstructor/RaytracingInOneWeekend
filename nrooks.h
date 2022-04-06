#pragma once
#include "sampler.h"

class nrooks : public sampler {



public:
	nrooks() = delete;
	//一个set对应一个pixel
	nrooks(int numSamples, int numSets)
		:sampler(numSamples, numSets)
	{
		
		generate_samples();
		
	};
public:
	



private:
	virtual void generate_samples(const double exp = 1.0) override;
private:
	void shuffle_x_coordinates();
	void shuffle_y_coordinates();


};