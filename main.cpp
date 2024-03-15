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
        for (int x = 0; x < image_width; ++x) 
        {
            double r = double(x) / (image_width-1);
            double g = double(y) / (image_height-1);
            int b = 0;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
}