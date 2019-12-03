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
	*  Gray Filter:
	*  When the filter meet the command line has the name "gray", then create a new 
	*  version of the image that each pixel of p'(i,j) = (R'(i,j) = ì, G'(i,j) = ì, B'(i,g) = ì)
	*  where ì = (R'(i,j) + G'(i,j) + B'(i,g)) / 3.
	*/
	class gray: public Filters {
		public:
			virtual void filterate(Image & sampleimage) {
				for (size_t i = 0; i < sampleimage.getWidth(); i++) {
					for (size_t j = 0; j < sampleimage.getHeight(); j++) {
						Vec3<float> samplepixel = sampleimage.getPixel(i, j);
						float averageofsamples = ((samplepixel.r + samplepixel.g + samplepixel.b) / 3);
						samplepixel.r = averageofsamples;
						samplepixel.g = averageofsamples;
						samplepixel.b = averageofsamples;
						sampleimage.setPixel(i, j, samplepixel);
					}
				}
			}
	};
};
