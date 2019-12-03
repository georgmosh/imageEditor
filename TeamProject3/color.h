//
// C++ course assignment code 
//
// Authors: G. Moschovis (3150113), S. Markopoulos (3150098)
//
//

#include "Array.h"
#include "Image.h"
#include "Vec3.h"
#include "Serializable.h"
#include "ppm_format.h"
#include "Filters.h"
#include <string>
#include <iostream>

namespace math {

	// data accessors
	/*
	*  Color Filter:
	*  The second filter to be illustrated, is created and acts on the image when the arguments are
	*  accompanied the filter name "color". As said, always after the color argument must follow three 
	*  more parameters that define the c color = (Rc, Gc, Bc) which will apply our filter, knock on the
	*  corresponding color of each pixel: p'(i,j) = c * p(i, j) = (Rc * R(i,j), Gc * R(i,j), Bc * R(i,j)).
	*/
	class color : public Filters {
	private:
		Vec3<float> parameter;
	public:
		color::color(float arg1, float arg2, float arg3) : Filters() {
			parameter = (arg1, arg2, arg3);
		}
		virtual void filterate(Image & sampleimage) {
			for (size_t i = 0; i < sampleimage.getWidth(); i++) {
				for (size_t j = 0; j < sampleimage.getHeight(); j++) {
					Vec3<float> samplepixel = sampleimage.getPixel(i, j);
					samplepixel.r *= parameter.r;
					samplepixel.g *= parameter.g;
					samplepixel.b *= parameter.b;
					sampleimage.setPixel(i, j, samplepixel);
				}
			}
		}
	};
};
