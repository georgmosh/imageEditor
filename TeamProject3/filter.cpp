//------------------------------------------------------------
//
// C++ course assignment code 
//
// Prof.: G. Papaioannou, 2015 - 2016
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
#include "gray.h"
#include "color.h"
#include "blur.h"
#include "diff.h"
#include "median.h"
#include <string>
#include <iostream>


using namespace std;
using namespace math;

int main(int argc, char * argv[]) {

	if (argc > 3) {
		bool correctFormat = true;
		size_t i = 2;
		while (i < argc - 1) {
			
			if (strcmp(argv[i-1] , "-f")!=0) correctFormat = false;
			if (strcmp(argv[i] , "gray")!=0 && strcmp(argv[i] , "color")!=0 && strcmp(argv[i] , "blur")!=0 && strcmp(argv[i] , "diff")!=0 && strcmp(argv[i] , "median")!=0) correctFormat = false;
			i = (strcmp(argv[i] , "color")==0) ? i + 5 : i + 2;
		}
		string fileSpecified = argv[argc - 1], typeOfFile;
		size_t pos = fileSpecified.find(".ppm");      // position of ".ppm" in string
		typeOfFile = fileSpecified.substr(pos);
		if(typeOfFile != ".ppm") correctFormat = false;
		if (correctFormat) {
			Image basicImage;
			Image * sampleImage = &basicImage;
			Filters * instanceFilter;
			
			if (sampleImage->operator<< (argv[argc-1])) {
				size_t i = 2;
				while (i < argc - 1) {
					if (strcmp(argv[i], "gray") == 0 ){
						instanceFilter = new gray();
						instanceFilter->filterate(*(sampleImage));
						i += 2;
					}
					else if (strcmp(argv[i], "color") == 0 ){
						instanceFilter = new color(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
						instanceFilter->filterate(*(sampleImage));
						i += 5;
					}
					else if (strcmp(argv[i], "blur") == 0 ){
						instanceFilter = new blur();
						instanceFilter->filterate(*(sampleImage));
						i += 2;
					}
					else if (strcmp(argv[i], "diff") == 0 ){
						instanceFilter = new diff();
						instanceFilter->filterate(*(sampleImage));
						i += 2;
					}
					else if (strcmp(argv[i], "median")==0) {
						instanceFilter = new median();
						instanceFilter->filterate(*(sampleImage));
						i += 2;
					}
				}
				string new_name = argv[argc - 1];
				new_name = new_name.substr( 0, new_name.size()-4);
				new_name.append(".filtered.ppm");
				bool flag = (*sampleImage).operator >> (new_name);
				if (flag) {
					cout << "Image written to " << new_name;
				}
			}
		}
		else {
			cout << "Could not load data.";
		}
	}
	else { // Garbage
		cout << "Could not handle arguments.";
	}

	return 0;
}