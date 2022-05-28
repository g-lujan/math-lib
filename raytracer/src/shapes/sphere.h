#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "../math/matrix.h"
#include "shape.h"
#include "../graphics/ray.h"

class Sphere : public Shape {
public:
	Sphere() : _radius(1), _position({ {0.0f}, {0.0f}, {0.0f}, {1.0f} }){}
	unsigned int radius() const { return _radius; }

	virtual std::vector<float> intersections(const Ray3D& ray) const{
		auto p_1 = ray.origin() + ray.direction();
		float x_0 = ray.origin()(0, 0), x_1 = p_1(0, 0);
		float y_0 = ray.origin()(1, 0), y_1 = p_1(1, 0);
		float z_0 = ray.origin()(2, 0), z_1 = p_1(2, 0);

		float a = std::pow(x_1 - x_0, 2) + std::pow(y_1 - y_0, 2) + std::pow(z_1 - z_0, 2);
		float b = 2 * (x_0 * (x_1 - x_0) + y_0 * (y_1 - y_0) + z_0 * (z_1 - z_0));
		float c = std::pow(x_0, 2) + std::pow(y_0, 2) + std::pow(z_0, 2) - _radius;
		float delta = std::pow(b, 2) - 4 * a * c;
		if (delta < 0.00000f) {
			return { };
		}
		else if (floats::equal(delta, 0.0000f)) {
			return { -b / (2 * a) };
		}
		const float sqrtDelta = std::sqrt(delta);
		return { (-b - sqrtDelta) / (2 * a), (-b + sqrtDelta) / (2 * a) };
	}

private:
	unsigned int _radius;
	Matrix<float, 4, 1> _position;
};

#endif // !_SPHERE_H_
