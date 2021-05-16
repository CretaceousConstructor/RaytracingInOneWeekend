#pragma once


class renderState {


public:

	static constexpr  double aspect_ratio = static_cast<double>(16) / static_cast<double>(9);
	//static constexpr  int image_width = 384;
	static constexpr  int image_width =400;
	static constexpr  int image_height = static_cast<int>(image_width / aspect_ratio);

	//static constexpr  int max_depth = 50;


	static constexpr int view_plane_samples_per_pixel = 64;
	static constexpr int view_plane_sample_sets = 83;


	static constexpr int lense_samples_per_pixel = 25;
	static constexpr int lense_sample_sets = 83;


};