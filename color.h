#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "ray.h"
#include <iostream>
#include <ostream>

using color = vec3;

void write_color(std::ostream &out, color pixel_color) {
    out << static_cast<int>(255 * pixel_color.x()) << ' '
    << static_cast<int>(255 * pixel_color.y()) << ' '
    << static_cast<int>(255 * pixel_color.z()) << '\n';
}

color ray_color(const ray& r){
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0-a) * color(1.0,1.0,1.0) + a * color(0.5, 0.7, 1.0);
}

#endif
