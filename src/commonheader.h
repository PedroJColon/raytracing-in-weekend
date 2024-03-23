#ifndef COMMONHEADER_H
#define COMMONHEADER_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// utility functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    // TODO: Write down comment
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // TODO: Write down coment
    return min + (max-min)*random_double();
}

// common header files

#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif
