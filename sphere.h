#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere :public hittable {
public:
    sphere();

    bool hit();

private:
    point3 center;
    double radius;
};


#endif
