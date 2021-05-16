#pragma once
#include "TrekMath.h"
class ray {

public:
	ray() = default;	
	ray(const TrekMath::point3& a, const TrekMath::vec3& b)
		:A(a),B(glm::normalize(b))
	{
		
	}

	void setOrigin(const TrekMath::point3& p) {
		A = p;
	}
	void setDir(const TrekMath::vec3& dir) {
		B = glm::normalize(dir);
	}

	inline TrekMath::point3 eye() const {
		return A;
	}
	inline TrekMath::point3 origin() const {
		return A;
	}
	
	inline  TrekMath::vec3 direction()  const {
		return B;
	}




	TrekMath::vec3 point_at_parameter(double t )const {
		return A + t*B;
	}

	

private:
	TrekMath::point3 A;
	TrekMath::vec3 B;
};