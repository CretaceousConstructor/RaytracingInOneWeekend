#pragma once


#include "sampler.h"



class hammersley : public sampler {



public:
	hammersley() = delete;
	//һ��set��Ӧһ��pixel
	hammersley(int numSamples, int numSets)
		:sampler(numSamples, numSets)
	{
		
		generate_samples();
		
	};



private:
	virtual void generate_samples(const double exp = 1.0) override;

	double phi(int j);


};