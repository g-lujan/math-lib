#include <raytracer/math.h>
#include <raytracer/graphics.h>

int main() {
	Canvas canvas(500, 500);
	Matrix<float,4,1> point({ {30}, {0}, {0}, {1} });
	const Color color = Color(255,0,0,0);
	const Matrix<float, 4, 4> clockStepRotation = Transformation::rotZ(Constants::PI / 480);
	for (int i = 0; i < 960; i++) {
		canvas.draw(color, Transformation::translation3D(250, 250, 0) * point);
		point = clockStepRotation * point;
	}
	Render::toFile(canvas, Image::Format::PPM, "example_circle");
}
