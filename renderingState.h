#pragma once
class renderingState
{
  public:
	double aspect_ratio = static_cast<double>(16) / static_cast<double>(9);
	
	int image_width = 480;


	int image_height = static_cast<int>(image_width / aspect_ratio);

	int max_depth = 50;

	int samples_per_set              = 32;
	int view_plane_sample_sets       = 83;
	int view_plane_samples_per_pixel = 100;

	int lense_sample_sets       = 83;
	int lense_samples_per_pixel = view_plane_samples_per_pixel;


};
