#pragma once
class renderingState
{
  public:
	renderingState() :
	    aspect_ratio(static_cast<double>(16) / static_cast<double>(9)),
	    image_width(480),
	    view_plane_sample_sets(97),
	    view_plane_samples_per_pixel(100),
	    lense_sample_sets(83)
	{


		image_height            = static_cast<int>(image_width / aspect_ratio);
		lense_samples_per_pixel = view_plane_samples_per_pixel;

	}

	double aspect_ratio;
	int    image_width;
	int    image_height = static_cast<int>(image_width / aspect_ratio);

	int view_plane_sample_sets;
	int view_plane_samples_per_pixel;

	int lense_sample_sets;
	int lense_samples_per_pixel;
};
