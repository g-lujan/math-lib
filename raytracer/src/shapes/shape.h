#ifndef _FORM_H_
#define _FORM_H_

#include <vector>
#include "../graphics/ray.h"

struct Shape {
	virtual ~Shape() {}
	virtual std::vector<float> intersections(const Ray3D&) const = 0;
	virtual Matrix<float, 4, 1> position() const = 0;
	virtual Matrix<float, 4, 4> transformation() const = 0;
	virtual void transformation(const Matrix<float, 4, 4>&) = 0;
};

#endif
