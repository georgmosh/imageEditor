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
#include "SortingFilters.h"
#include <string>
#include <iostream>

namespace math {

	// data accessors
	/*
	*  Median Filter:
	*  We read the red, green and blue components of the colors in the 3x3 neighborhood and
	*  sort the values read SEPARATELY for each color channel, using bubbleSort method of
	*  class SortingFilters (described there). Then median filter selects as color component
	*  value the middle element of the sorted series of color components.
	*/
	class median : public SortingFilters {
	public:
		virtual void filterate(Image & sampleimage) {
			size_t sumOfValidations;
			float * redComponents = new float[9];
			float * greenComponents = new float[9];
			float * blueComponents = new float[9];
			Image newimage = sampleimage;
			for (int i = 0; i < sampleimage.getWidth(); i++) {
				for (int j = 0; j < sampleimage.getHeight(); j++) {
					Vec3<float> samplepixel /*= newimage.getPixel(i, j)*/, surroundingpixel;
					sumOfValidations = 0;
					for (int m = -1; m < 2; m++) {
						for (int n = -1; n < 2; n++) {
							if (checkIfValid(sampleimage, i + m, j + n)) {
								surroundingpixel = newimage.getPixel(i + m, j + n);
								redComponents[sumOfValidations] = surroundingpixel.r;
								greenComponents[sumOfValidations] = surroundingpixel.g;
								blueComponents[sumOfValidations] = surroundingpixel.b;
								sumOfValidations++;
							}
						}
					}
					bubbleSort(redComponents, sumOfValidations);
					bubbleSort(greenComponents, sumOfValidations);
					bubbleSort(blueComponents, sumOfValidations);
					samplepixel.r = redComponents[sumOfValidations / 2];
					samplepixel.g = greenComponents[sumOfValidations / 2];
					samplepixel.b = blueComponents[sumOfValidations / 2];
					sampleimage.setPixel(i, j, samplepixel);
				}
			}
			delete[] redComponents;
			delete[] greenComponents;
			delete[] blueComponents;
		}
	};
};