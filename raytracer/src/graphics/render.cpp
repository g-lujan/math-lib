#include <fstream>
#include "render.h"

using std::string;
using std::to_string;

namespace Render {
	static void toPPM(const Canvas&, const string);
	static void save(string, string);

	void toFile(const Canvas& canvas, Image::Format format, const string fileName) {
		switch (format) {
		case Image::Format::PPM:
			toPPM(canvas, fileName);
		}
	}

	static void toPPM(const Canvas& canvas, const string fileName) {
		string lines = "P3\n" + to_string(canvas.width()) + " " + to_string(canvas.height()) + "\n" + to_string(255) + "\n";
		for (int i = 0; i < canvas.width(); i++) {
			for (int j = 0; j < canvas.height(); j++) {
				auto position = Matrix<int, 4, 1>({ {i}, {j}, {0}, {1} });
				lines += std::to_string(canvas.colorAt(position).r()) + " " + std::to_string(canvas.colorAt(position).g()) + " " + std::to_string(canvas.colorAt(position).b()) + " ";
			}
		}
		lines += "\n";
		save(lines, fileName+".ppm");
	}

	static void save(string data, string fileName) {
		std::ofstream outfile;
		outfile.open(fileName, std::ios::trunc);
		outfile << data << "\n";
		outfile.close();
	}
}