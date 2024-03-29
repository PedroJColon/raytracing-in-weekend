#ifndef CAMERA_H
#define CAMERA_H

#include "commonheader.h"

#include "color.h"
#include "hittable.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

class camera {
public:
  // Note: An image's aspect ratio can be found by the ratio of its height and
  // width (width/height)
  double aspect_ratio = 1.0; // Ratio of image width over height
  int image_width = 100;     // Rendered image width in pixel count
  int samples_per_pixel = 10; // Count of random samples for each pixel
  int max_depth = 10; // Maximum number of ray bounces into scene

  void render(const hittable &world) {
    init();

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int y = 0; y < image_height; ++y) {
      std::clog << "\rScanlines remaining: " << (image_height - y) << ' '
                << std::flush;
      for (int x = 0; x < image_width; ++x) {
        color pixel_color(0, 0, 0);
        for (int sample = 0; sample < samples_per_pixel; ++sample) {
          ray r = get_ray(x, y);
          pixel_color += ray_color(r, max_depth, world);
        }
        write_color(std::cout, pixel_color, samples_per_pixel);
      }
    }

    std::clog << "\rDone.                   \n";
  }

private:
  int image_height;
  point3 center;
  point3 pixel00_loc;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;

  void init() {
    // Calculate the image height, and ensure that it's at least 1
    // Reason why we wantto ensure it's 1 for the following reason
    // Make sure that we can scale up or down the image by changing its width
    // Won't throw off our desired aspect ratio (that we set already)
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    center = point3(0, 0, 0);

    // Camera
    auto focal_length = 1.0;
    // Viewport widths less than one are okay since they are real valued
    // Viewports are important due to allowing us to setup our 3D world in a way
    // that contains the grid of pixels This ensures that the objects that are
    // bounded to the viewport share the same aspect ratio across the board
    auto viewport_height = 2.0;
    // Reason we don't use the aspect ratio var is because we need the viewport
    // to match the image porportions
    auto viewport_width =
        viewport_height * (static_cast<double>(image_width) / image_height);
    // Note: Distance between two adjacent pixels is called pixel spacing and
    // the standard is square pixels

    // Helps us calcuate the vectors across horizontal axis and down the
    // vertical axis
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Helps us calcuate where to put the pixel values by using the delta
    // vectors as our guide This way, our viewport and pixel grid are evenly
    // divded into identical regions
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left =
        center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
  }

  color ray_color(const ray &r, int depth, const hittable &world) const {
    hit_record rec;

    // If we're exceeded ray bounce limit, no more light is gathered
    if (depth <= 0)
      return color(0, 0, 0);

    if (world.hit(r, interval(0, infinity), rec)) {
      vec3 direction = random_on_hemisphere(rec.normal);
      return 0.5 * ray_color(ray(rec.p, direction), depth-1, world);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  }

  vec3 pixel_sample_square() const {

    //
    auto point_x = -0.5 + random_double();
    auto point_y = -0.5 + random_double();

    return (point_x * pixel_delta_u) + (point_y * pixel_delta_v);
  }

  ray get_ray(int i, int j) const {
    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
    auto pixel_sample = pixel_center + pixel_sample_square();

    auto ray_origin = center;
    auto ray_direction = pixel_sample - ray_origin;

    return ray(ray_origin, ray_direction);
  }
};

#endif
