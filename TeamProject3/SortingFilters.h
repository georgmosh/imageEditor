//------------------------------------------------------------
//
// C++ course assignment code 
//
// Authors: G. Moschovis (3150113), S. Markopoulos (3150098)
//
//

#ifndef SFilters_H
#define SFilters_H

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
	/* An abstract class illustrating sorting filters. We separate neighborhood filters in another class, as in all
	*  of those; such as the diff filter, we need a sorting method. The sorting method selected in this task is
	*  bubble sort; being described above.
	*/
	class SortingFilters: public NeighborhoodFilters {
	public:
		virtual void filterate(Image & sampleimage) = 0;

		/* The method of direct exchange sorting is based on the comparison and exchange of adjacent element
		*  pairs until all items are sorted. According to this method array accesses take place and the smaller key
		*  found in each moves to the left edge of the table. If the table is supposed in a vertical position rather than
		*  horizontal, integers can be considered - if we use enough imagination - as bubbles in a water tank with
		*  weights according to their value, then any access results to the increase of a bubble.
		*/
		virtual void bubbleSort(float * pixelarray, size_t arraysize) {
			for (size_t i = 0; i < arraysize; i++) {
				for (int j = arraysize-1; j > i; j--) {
					if (pixelarray[j] < pixelarray[i]) {
						float t = pixelarray[i];
						pixelarray[i] = pixelarray[j];
						pixelarray[j] = t;
					}
				}
			}
		}
	};
};

#endif