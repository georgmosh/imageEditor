//------------------------------------------------------------
//
// C++ course assignment code 
//
// Authors: G. Moschovis (3150113), S. Markopoulos (3150098)
//
//

#ifndef Filters_H
#define Filters_H

#include "Array.h"
#include "Image.h"
#include "Vec3.h"
#include "Serializable.h"
#include "ppm_format.h"
#include <string>
#include <iostream>

namespace math {

	// data accessors
	/* An abstract class illustrating all filters: gray, color, blur, diff, median; from a rather general approach.
	* being applies on such a range of image processing filters according to the specifications of the project.
	* The type, number and order of image filters will act on the image identified by the application arguments.
	*/
	class Filters {
		public:
			virtual void filterate(Image & sampleimage) = 0;
	};
};

#endif