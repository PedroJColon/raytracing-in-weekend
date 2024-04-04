#ifndef CAMERA_H
#define CAMERA_H

#include "commonheader.h"

#include "color.h"
#include "hittable.h"
#include "material.h"
#include "vec3.h"

#include <cmath>
#include <iostream>

class camera {
public:
  // Note: An image's aspect ratio can be found by the ratio of its height and
  // width (width/height)
  double aspect_ratio = 1.0;  // Ratio of image width over height
  int image_width = 100;      // Rendered image width in pixel count
  int samples_per_pixel = 10; // Count of random samples for each pixel
  int max_depth = 10;         // MAxium number of ray bounces into scene
  double vfov = 90; // Vertical view angle (field of view)
  point3 lookfrom = point3(0,0,-1); // Where camera is looking from
  point3 lookat = point3(0,0,0); // Point camera is looking at 
  vec3 vup = vec3(0,1,0); // Camera relative up direction

  double defocus_angle = 0; 
  double focus_dist = 10;

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
  int image_height; // Rendered image height
  point3 center; // Camera Center
  point3 pixel00_loc; // Pixel coordinates (0,0)
  vec3 pixel_delta_u; // Offset to pixel to the right
  vec3 pixel_delta_v; // Offset to pixel below
  vec3 u; // Camera frame basis vectors
  vec3 v; // Camera frame basis vectors
  vec3 w; // Camera frame basis vectors
  vec3 defocus_disk_u; // DEfocus disk horizontal radius
  vec3 defocus_disk_v; // Defocus disk vertical radius

  void init() {
    // Calculate the image height, and ensure that it's at least 1
    // Reason why we wantto ensure it's 1 for the following reason
    // Make sure that we can scale up or down the image by changing its width
    // Won't throw off our desired aspect ratio (that we set already)
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    center = lookfrom;

    // Camera
    // auto focal_length = (lookfrom - lookat).length();
    auto theta = degrees_to_radians(vfov);
    auto h = tan(theta/2);
    // Viewport widths less than one are okay since they are real valued
    // Viewports are important due to allowing us to setup our 3D world in a way
    // that contains the grid of pixels This ensures that the objects that are
    // bounded to the viewport share the same aspect ratio across the board
    auto viewport_height = 2.0 * h * focus_dist;
    // Reason we don't use the aspect ratio var is because we need the viewport
    // to match the image porportions
    auto viewport_width =
        viewport_height * (static_cast<double>(image_width) / image_height);
    // Note: Distance between two adjacent pixels is called pixel spacing and
    // the standard is square pixels

    // Calcuate the u,v,w unit basis vectors for the camera coordinate frame
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    // Helps us calcuate the vectors across horizontal axis and down the
    // vertical axis
    auto viewport_u = viewport_width * u; // Vector across viewport horizontal edge
    auto viewport_v = viewport_height * v; // Vector down viewport vertical edge

    // Helps us calcuate where to put the pixel values by using the delta
    // vectors as our guide This way, our viewport and pixel grid are evenly
    // divded into identical regions
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
    // auto viewport_upper_left =
    //     center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Calcuate camera defocus disk basis vectors
    auto defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle/2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
  }

  color ray_color(const ray &r, int depth, const hittable &world) const {
    hit_record rec;

    // If we're exceeded ray bounce limit, no more light is gathered
    if (depth <= 0)
      return color(0, 0, 0);

    if (world.hit(r, interval(0.001, infinity), rec)) {
      ray scattered;
      color attenuation;
      if (rec.mat->scatter(r, rec, attenuation, scattered)) {
        return attenuation * ray_color(scattered, depth - 1, world);
      }
      return color(0, 0, 0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  }

  vec3 pixel_sample_square() const {
    // Returns a random point in the square surrounding a pixel at the origin
    auto point_x = -0.5 + random_double();
    auto point_y = -0.5 + random_double();

    return (point_x * pixel_delta_u) + (point_y * pixel_delta_v);
  }

  ray get_ray(int i, int j) const {
    // Get randomy sampled camera ray for the pixel location of i and j, originating from camera defocus disk
    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
    auto pixel_sample = pixel_center + pixel_sample_square();

    auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;

    return ray(ray_origin, ray_direction);
  }

  point3 defocus_disk_sample() const {
    // Returns a random point in the camera defocus disk
    auto p = random_in_unit_disk();
    return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
  }
};

#endif
