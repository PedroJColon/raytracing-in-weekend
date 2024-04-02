#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <ostream>

using std::sqrt;

class vec3 {
public:
  double point[3];
  vec3() : point{0, 0, 0} {}
  vec3(double p0, double p1, double p2) : point{p0, p1, p2} {}

  double x() const { return point[0]; }
  double y() const { return point[1]; }
  double z() const { return point[2]; }

  vec3 operator-() const { return vec3(-point[0], -point[1], point[2]); }
  double operator[](int i) const { return point[i]; }
  double &operator[](int i) { return point[i]; }

  vec3 &operator+=(const vec3 &v) {
    point[0] += v.point[0];
    point[1] += v.point[1];
    point[2] += v.point[2];
    return *this;
  }

  vec3 &operator*=(double t) {
    point[0] *= t;
    point[1] *= t;
    point[2] *= t;
    return *this;
  }

  vec3 operator/=(double t) { return *this *= 1 / t; }

  double length() const { return sqrt(length_squared()); }

  double length_squared() const {
    return (point[0] * point[0]) + (point[1] * point[1]) +
           (point[2] * point[2]);
  }
  bool near_zero() const {
    // Returns true if the vector is close to zero in all dimensions
    auto s = 1e-8;
    return (fabs(point[0]) < s) && (fabs(point[1]) < s) && (fabs(point[2]) < s);
  }

  static vec3 random() {
    return vec3(random_double(), random_double(), random_double());
  }

  static vec3 random(double min, double max) {
    return vec3(random_double(min, max), random_double(min, max),
                random_double(min, max));
  }
};

// alias for vector 3,  focused on geometric shapes
using point3 = vec3;

// utility functions

inline std::ostream &operator<<(std::ostream &out, const vec3 &v) {
  return out << v.point[0] << ' ' << v.point[1] << ' ' << v.point[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
  return vec3(u.point[0] + v.point[0], u.point[1] + v.point[1],
              u.point[2] + v.point[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
  return vec3(u.point[0] - v.point[0], u.point[1] - v.point[1],
              u.point[2] - v.point[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
  return vec3(u.point[0] * v.point[0], u.point[1] * v.point[1],
              u.point[2] * v.point[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
  return vec3(t * v.point[0], t * v.point[1], t * v.point[2]);
}

inline vec3 operator*(const vec3 &v, double t) { return t * v; }

inline vec3 operator/(vec3 v, double t) { return (1 / t) * v; }

inline double dot(const vec3 &u, const vec3 &v) {
  return (u.point[0] * v.point[0]) + (u.point[1] * v.point[1]) +
         (u.point[2] * v.point[2]);
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
  return vec3(u.point[1] * v.point[2] - u.point[2] * v.point[1],
              u.point[2] * v.point[0] - u.point[0] * v.point[2],
              u.point[0] * v.point[0] - u.point[1] * v.point[0]);
}

inline vec3 unit_vector(vec3 v) { return v / v.length(); }

inline vec3 random_in_unit_sphere() {
  while (true) {
    auto p = vec3::random(-1, 1);
    if (p.length_squared() < 1)
      return p;
  }
}

inline vec3 random_unit_vector() {
  return unit_vector(random_in_unit_sphere());
}

inline vec3 random_on_hemisphere(const vec3 &normal) {
  vec3 on_unit_sphere = random_unit_vector();
  // In the same hemisphere as the normal
  if (dot(on_unit_sphere, normal) > 0.0) {
    return on_unit_sphere;
  } else {
    return -on_unit_sphere;
  }
}

vec3 reflect(const vec3 &v, const vec3 &n) { return v - 2 * dot(v, n) * n; }

#endif
