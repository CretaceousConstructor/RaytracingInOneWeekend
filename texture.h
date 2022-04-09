#pragma once
#include "TrekMath.h"
using namespace TrekMath;


class texture
{
  public:
	virtual color value(const TrekMath::texcoor2d& txcor, const point3 &p) const = 0;


};
