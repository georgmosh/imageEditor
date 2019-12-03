//------------------------------------------------------------
//
// C++ course assignment code 
//
// Authors: G. Moschovis (3150113), S. Markopoulos (3150098)
//
//

#ifndef NFilters_H
#define NFilters_H

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
	/* An abstract class illustrating neighborhood filters. We separate neighborhood filters in another class,
	*  as in all of those; such as the average filter, the edges of the image require special handling as values
	*  (i + m, j + n) can overcome the limits of the image, since i, j are in the interval [0, width-1], [0, height-1]
	*  and m, n in [-1,1].
	*/
	class NeighborhoodFilters : public Filters {
	public:
		virtual void filterate(Image & sampleimage) = 0;
		
		/* This method checks if a coordinate (i + m, j + n) is valid and only then counted on average of the 
		 * corresponding pixel. This means that the population respectively in which we divide the sum is not
		 * constant (9) but equals the number of valid pixels.
		*/
		virtual bool checkIfValid(Image & sampleimage, int x, int y) {
			if (x < 0 || y < 0 || !(x < sampleimage.getWidth()) || !(y < sampleimage.getHeight())) return false;
			return true;
		}
	};
};

#endif