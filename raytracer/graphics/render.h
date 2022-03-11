#ifndef _RENDER_H_
#define _RENDER_H_

#include "canvas.h"
#include "image.h"

namespace Render {
	void toFile(const Canvas&, Image::Format, std::string);
}

#endif