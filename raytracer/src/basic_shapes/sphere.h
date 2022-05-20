#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "../math/matrix.h"

class Sphere{
public:
	Sphere() : _radius(1), _position({ {0.0f}, {0.0f}, {0.0f}, {1.0f} }){}
	unsigned int radius() const { return _radius; }
private:
	unsigned int _radius;
	Matrix<float, 4, 1> _position;
};

#endif // !_SPHERE_H_
