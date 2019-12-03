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
#include "NeighborhoodFilters.h"
#include <string>
#include <iostream>

namespace math {

	// data accessors
	/*
	*  Blur Filter:
	*  When the command line meets as a filter argument the word "blur", we create a filter
	*  with the center of each pixel (i, j) of the target image, reads an area 3x3 pixels of the
	*  filter input image and sets a pixel's color (i, j) the average of the 9 3x3 block colors.
	*/
	class blur : public NeighborhoodFilters {
	public:
		virtual void filterate(Image & sampleimage) {
			float sumOfValidations, fraction;
			Image newimage = sampleimage;
			Vec3<float> sumOfProducts;
			for (int i = 0; i < sampleimage.getWidth(); i++) {
				for (int j = 0; j < sampleimage.getHeight(); j++) {
					Vec3<float> samplepixel;
					sumOfValidations = 0;
					sumOfProducts = 0;
					for (int m = -1; m < 2; m++) {
						for (int n = -1; n < 2; n++) {
							sumOfValidations += checkIfValid(sampleimage, i + m, j + n);
							sumOfProducts += checkIfValid(sampleimage, i + m, j + n) * newimage.getPixel(i + m, j + n);
						}
					}
					fraction = 1.0 / sumOfValidations;
					samplepixel = fraction * sumOfProducts;
					sampleimage.setPixel(i, j, samplepixel);
				}
			}
		}
	};
};
