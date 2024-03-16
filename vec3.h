#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <ostream>

using std::sqrt;

class vec3 {
    public:
        double point[3];
        vec3() : point{0,0,0} {}
        vec3(double p0, double p1, double p2) : point{p0, p1, p2} {}


        double x() const {return point[0]; }
        double y() const {return point[1]; }
        double z() const {return point[2]; }

        vec3 operator-() const {return vec3(-point[0], -point[1], point[2]);}
        double operator[] (int i) const {return point[i];}
        double& operator[] (int i) {return point[i];}

        vec3& operator+=(const vec3 &v) {
            point[0] += v.point[0];
            point[1] += v.point[1];
            point[2] += v.point[2];
            return *this;
        }

        vec3& operator*=(double t) {
            point[0] *= t;
            point[1] *= t;
            point[2] *= t;
            return *this;
        }

        vec3 operator /=(double t) {
            return *this *= 1/t;
        } 

        double length() const {
            return sqrt(length_squared());
        } 

        double length_squared()  const {
            return (point[0] * point[0]) + (point[1] * point[1]) + (point[2] * point[2]);
        }     
};

// alias for vector 3,  focused on geometric shapes
using point3 = vec3;

// utility functions

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.point[0] << ' ' << v.point[1] << ' ' << v.point[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.point[0] + v.point[0], u.point[1] + v.point[1], u.point[2] + v.point[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.point[0] - v.point[0], u.point[1] - v.point[1], u.point[2] - v.point[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.point[0] * v.point[0], u.point[1] * v.point[1], u.point[2] * v.point[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.point[0], t*v.point[1], t*v.point[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return (u.point[0] * v.point[0]) +
            (u.point[1] * v.point[1]) +
            (u.point[2] * v.point[2]);
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.point[1] * v.point[2] - u.point[2] * v.point[1],
                u.point[2] * v.point[0] - u.point[0] * v.point[2],
                u.point[0] * v.point[0] - u.point[1] * v.point[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

#endif
