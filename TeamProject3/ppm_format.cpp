//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2016
//
//
//-------------------------------------------------------------

#include "Image.h"
#include "ppm_format.h"
#include "Array.h"
#include "Vec3.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

namespace math
{
	/*! Reads a PPM image file and returns a pointer to a newly allocated Image object containing the image.
	*
	*  \param filename is the null-terminated string of the name of the file to open.
	*
	*  \return a pointer to a new Image object, if the read operation was successful, nullptr otherwise.
	*/
	Image * ReadPPM(const char * filename) {
		ifstream Stream(filename, ios_base::binary);
		string firstArg;
		unsigned int secondArg, thirdArg, fourthArg; // File Arguments definition
													 // secondArg, thirdArg represent image dimensions
													 // fourthArg has standard value 255, for this project
		unsigned char red, green, blue;
		Image * image = nullptr;

		if (!Stream) {
			cerr << "Cannot open file." << endl;
			return nullptr;
		}

		Stream >> firstArg;
		Stream >> secondArg;
		Stream >> thirdArg;
		Stream >> fourthArg;
		Stream.get();
		if ((firstArg == "P6") && (secondArg > 0) && (thirdArg > 0) && (fourthArg == 255)) {
			Vec3<float> * component = new Vec3<float>[secondArg * thirdArg];
			for (size_t i = 0; i < secondArg * thirdArg; i++) {
				Stream.read((char *)&red, 1); // char occupy 1 byte of memory each
				component[i].r = red / 255.0f;
				Stream.read((char *)&green, 1); // char occupy 1 byte of memory each
				component[i].g = green / 255.0f;
				Stream.read((char *)&blue, 1); // char occupy 1 byte of memory each
				component[i].b = blue / 255.0f;
				// i = y * width + x
			}
			image = new Image(secondArg, thirdArg, component);
			delete[] component;
		}

		if (Stream.fail()) {
			cerr << "Could not write data." << endl;
			return nullptr;
		}

		Stream.close();
		return image;
	}


	/*! Writes an existing image as a PPM file.
	*
	*  \param image is the Image object to save to a file in the PPM format.
	*  \param filename is the null-terminated string of the name of the file to create.
	*
	*  \return true if the image save operation was successful, false otherwise.
	*/
	bool WritePPM(Image & image, const char * filename) {
		ofstream Stream(filename, ios::binary | ios::out);
		unsigned char red, green, blue;
		
		if (!Stream) {
			cerr << "Cannot open file." << endl;
			return false;
		}

		Stream << "P6";
		Stream << " " << image.getWidth();
		Stream << " " << image.getHeight();
		Stream << " " << 255;
		Stream << endl;

		Vec3<float> * component = image.getRawDataPtr();
		for (size_t i = 0; i < image.getWidth() * image.getHeight(); i++) {
			red = component[i].r * 255;
			Stream.write((char *)& red, 1); // char occupy 1 byte of memory each
			
			green = component[i].g * 255;
			Stream.write((char *)& green, 1);
			
			blue = component[i].b * 255;
			Stream.write((char *)& blue, 1);
		}
		Stream.close();

		return true;
	}

} //namespace imaging