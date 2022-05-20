#include "ray.h"
#include "math/float_operations.h"

/*
 sphere (center in origin): x^2 + y^2 + z^2 = r^2
 ray (parametric): x = x_0 + t*(x_1 - x_0)
                   y = y_0 + t*(y_1 - y_0)
                   z = z_0 + t*(z_1 - z_0)
 
 => intersection is a quadratic equation in t: 
 a = (x_1 - x_0)^2 + (y_1 - y_0)^2 + (z_1 - z_0)^2
 b = 2 * (x_0 * (x_1 - x_0) + y_0 * (y_1 - y_0) + z_0 * (z_1 - z_0))
 c = (x_0)^2 + (y_0)^2 + (z_0)^2 - r^2
 
 => Delta = b^2- 4*a*c
 Delta < 0  -> no intersection
 Delta == 0 -> single intersection point, the unique solution is t = -b/2a
 Delta > 0  -> two intersection points, solutions are t_0 = (-b-sqrt(Delta))/(2*a) and t_2 = (-b+sqrt(Delta))/(2*a) 
*/
std::vector<float> Ray3D::intersect(const Sphere& sphere) {
	auto p_1 = origin_ + direction_;
	float x_0 = origin_(0, 0), x_1 = p_1(0, 0);
	float y_0 = origin_(1, 0), y_1 = p_1(1, 0);
	float z_0 = origin_(2, 0), z_1 = p_1(2, 0);

	float a = std::pow(x_1 - x_0, 2) + std::pow(y_1 - y_0, 2) + std::pow(z_1 - z_0, 2);
	float b = 2 * (x_0 * (x_1 - x_0) + y_0 * (y_1 - y_0) + z_0 * (z_1 - z_0));
	float c = std::pow(x_0, 2) + std::pow(y_0, 2) + std::pow(z_0, 2) - sphere.radius();
	float delta = std::pow(b, 2) - 4 * a * c;
	if (delta < 0.00000f) {
		return {};
	}
	else if (floats::equal(delta, 0.0000f)) {
		return {-b/(2*a)};
	}
	const float sqrtDelta = std::sqrt(delta);
	return { (-b - sqrtDelta) / (2 * a), (-b + sqrtDelta) / (2 * a) };
}