#include <iostream>
#include "vec3.h"





int main() {

	const int image_height = 100;
	const int image_width = 200;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {   //jmax  = 99
        for (int i = 0; i < image_width; ++i) {     //imax = 199
            auto r = double(i) / image_width;       //rmax = 0.995
            auto g = double(j) / image_height;      //gmax = 0.99
            auto b = 0.2;
            int ir = static_cast<int>(255.999 * r); //ir max = 254
            int ig = static_cast<int>(255.999 * g); //ig max = 253
            int ib = static_cast<int>(255.999 * b); //ib     == 51
            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
}