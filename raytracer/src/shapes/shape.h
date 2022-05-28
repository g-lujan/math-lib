#ifndef _FORM_H_
#define _FORM_H_

#include <vector>
#include "../graphics/ray.h"

struct Shape {
	virtual ~Shape() {}
	virtual std::vector<float> intersections(const Ray3D&) const = 0;
};

#endif
