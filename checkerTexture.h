#pragma once
#include "texture.h"
#include "solid_color.h"
#include <memory>

using std::shared_ptr;
using std::make_shared;
class checkerTexture : public texture
{
  public:
	checkerTexture() = default;
	checkerTexture(shared_ptr<texture> _even, shared_ptr<texture> _odd);
	checkerTexture(color c1, color c2);


	//p is hit point
	virtual color value(const texcoor2d &txcor, const point3 &p) const override;

  public:
	shared_ptr<texture> odd;
	shared_ptr<texture> even;
};
