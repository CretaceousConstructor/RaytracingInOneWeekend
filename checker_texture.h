#pragma once
#include "texture.h"
#include "solid_color.h"
#include <memory>

using std::shared_ptr;
using std::make_shared;
class checker_texture : public texture
{
  public:
	checker_texture() = default;
	checker_texture(shared_ptr<texture> _even, shared_ptr<texture> _odd);
	checker_texture(color c1, color c2);


	//p is hit point
	virtual color value(const texcoor2d &txcor, const point3 &p) const override;

  public:
	shared_ptr<texture> odd;
	shared_ptr<texture> even;
};
