#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include "shape.h"

class Intersections {
public:
	Intersections(std::vector<float> intersections, const Shape& form) : intersections_{ intersections }, form_{ form }{}
	bool empty() const { return intersections_.empty(); }
	std::size_t size() const { return intersections_.size(); }
	float operator[](std::size_t i) const { return intersections_[i]; }

private:
	std::vector<float> intersections_;
	const Shape& form_;
};

#endif