#ifndef _CANVAS_H_
#define _CANVAS_H_

#include "../math/matrix.h"
#include "image.h"
#include <vector>
#include <iostream>

using std::size_t;
using std::vector;

struct Color {
	Color(float r, float g, float b, float alpha) {
		color_(0, 0) = r;
		color_(1, 0) = g;
		color_(2, 0) = b;
		color_(3, 0) = alpha;
	}

	float r() const { return color_(0, 0); }
	float g() const { return color_(1, 0); }
	float b() const { return color_(2, 0); }
	float alpha() const { return color_(3, 0); }

	void r(float color) { color_(0, 0) = color; }
	void g(float color) { color_(1, 0) = color; }
	void b(float color){ color_(2, 0) = color; }
	void alpha(float color) { color_(3, 0) = color; }
private:
	Matrix<float, 4, 1> color_;
};

class Canvas {
public:
	Canvas(size_t height, size_t width) : height_{ height }, width_{ width },
		pixels_{ vector<vector<Color>>(height, vector<Color>(width, Color(0,0,0,0))) }
	{ }

	std::size_t width() const { return width_; };
	std::size_t height() const { return height_; };

	Color& operator()(std::size_t i, std::size_t j) { return pixels_[i][j]; }

	const Color& operator()(std::size_t i, std::size_t j) const { return pixels_[i][j]; }

	bool isWithinBounds(const int i, const int j) const{
		return i>=0 && j>=0 && i < width_ && j < height_; 
	}

	template<typename T>
	void draw(const Color& color, const Matrix<T, 4, 1>& position) {
		if (!isWithinBounds(position(0, 0), position(1, 0))) {
			return;
		}
		pixels_[position(0, 0)][position(1, 0)] = color;
	}

	template<typename T>
	Color& colorAt(const Matrix<T, 4, 1>& position) { 
		return pixels_[position(0,0)][position(1, 0)];
	}

	template<typename T>
	const Color& colorAt(const Matrix<T, 4, 1>& position) const{
		return pixels_[position(0, 0)][position(1, 0)];
	}

private:
	size_t width_;
	size_t height_;
	vector<vector<Color>> pixels_;
};

#endif