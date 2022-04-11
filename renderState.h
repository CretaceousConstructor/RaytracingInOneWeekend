#pragma once

using namespace TrekMath;

namespace DefaultRenderState
{
//constexpr  double aspect_ratio = static_cast<double>(16) / static_cast<double>(9);

constexpr double aspect_ratio = 1.0;

//constexpr  int image_width = 480;
constexpr int image_width = 600;

constexpr int image_height = static_cast<int>(image_width / aspect_ratio);

constexpr int max_depth = 50;

constexpr int samples_per_set              = 32;
constexpr int view_plane_sample_sets       = 83;
constexpr int view_plane_samples_per_pixel = 200;

constexpr int lense_sample_sets       = 83;
constexpr int lense_samples_per_pixel = view_plane_samples_per_pixel;




};        // namespace DefaultRenderState