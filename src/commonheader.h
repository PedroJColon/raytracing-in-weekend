#ifndef COMMONHEADER_H
#define COMMONHEADER_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>

// usings

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// utility functions

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

/// C++ implementation
// // return a real num between 0-1
// inline double random_double() {
//   static std::uniform_real_distribution<double> distribution(0.0, 1.0);
//   static std::mt19937 generator;
//   return distribution(generator);
// }

// inline double random_double(double min, double max) {
//   static std::uniform_real_distribution<double> distribution(min, max);
//   static std::mt19937 generator;
//   return distribution(generator);
// }

/// C-like implementation
inline double random_double() {
  // returns a real num between 0-1
  return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
  // returns a real num between the min and max
  return min + (max - min) * random_double();
}

// common header files

#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif
