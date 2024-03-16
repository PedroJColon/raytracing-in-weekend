#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <cstddef>
#include <iostream>
#include <type_traits>


int main() {
    // Note: An image's aspect ratio can be found by the ratio of its height and width (width/height)
    auto aspect_ratio = 16.0/9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1
    // Reason why we wantto ensure it's 1 for the following reason
    // Make sure that we can scale up or down the image by changing its width
    // Won't throw off our desired aspect ratio (that we set already)
    int image_height = static_cast<int>(image_width/aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    auto focal_length = 1.0;
    // Viewport widths less than one are okay since they are real valued
    // Viewports are important due to allowing us to setup our 3D world in a way that contains the grid of pixels
    // This ensures that the objects that are bounded to the viewport share the same aspect ratio across the board
    auto viewport_height = 2.0;
    // Reason we don't use the aspect ratio var is because we need the viewport to match the image porportions
    auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
    // Note: Distance between two adjacent pixels is called pixel spacing and the standard is square pixels
    auto camera_center = point3(0,0,0);

    // Helps us calcuate the vectors across horizontal axis and down the vertical axis
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);


    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int y = 0; y < image_height; ++y) {
        std::clog << "\rScanlines remaining: " << (image_height - y) << ' ' << std::flush;
        for (int x = 0; x < image_width; ++x) {
            auto pixel_center = pixel00_loc + (x * pixel_delta_u) + (y * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                   \n";
}
