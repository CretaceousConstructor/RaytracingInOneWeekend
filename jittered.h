#pragma once
#include "sampler.h"

class  jittered : public sampler
{
public:
	jittered() = delete;
	//һ��set��Ӧһ��pixel
	jittered(int numSamples, int numSets)
		:sampler(numSamples, numSets)
	{
		
		generate_samples();

	};


private:
	virtual void generate_samples(const double exp = 1.0) override;



};

