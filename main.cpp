#include "color.h"
#include "vec3.h"

#include <cstddef>
#include <iostream>
#include <type_traits>

int main()
{
    int image_width = 256;
    int image_height = 256;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int y = 0; y < image_height; ++y)
    {
        std::clog << "\rScanlines remaining: " << (image_height - y) << ' ' << std::flush;
        for (int x = 0; x < image_width; ++x) 
        {
            auto pixel_color = color(double(x)/(image_width-1), double(y)/(image_height-1), 0); 
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                   \n";
}