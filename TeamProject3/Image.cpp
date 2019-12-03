//------------------------------------------------------------
//
// C++ course assignment code 
//
// Prof.:  G. Papaioannou, 2016
// Authors: G. Moschovis (3150113), S. Markopoulos (3150098)
//
//

#include "Vec3.h"
#include "Array.h"
#include "Serializable.h"
#include "Image.h"
#include "ppm_format.h"

namespace math {

	// data accessors

	/*! Obtains a pointer to the internal data.
	*
	*  This is NOT a copy of the internal image data, but rather a pointer
	*  to the internally allocated space, so DO NOT attempt to delete the pointer.
	*/
	Vec3<float> * Image::getRawDataPtr() {
		return (Vec3<float> *)Array::getRawDataPtr();
	}

	/*! Obtains the color of the image at location (x,y).
	*
	*  The method should do any necessary bounds checking.
	*
	*  \param x is the (zero-based) horizontal index of the pixel to get.
	*  \param y is the (zero-based) vertical index of the pixel to get.
	*
	*  \return The color of the (x,y) pixel as a Color object. Returns a black (0,0,0) color in case of an out-of-bounds x,y pair.
	*/
	Vec3<float> Image::getPixel(unsigned int x, unsigned int y) const {

		return Array::operator () (x, y);
	}

	// data mutators

	/*! Sets the RGB values for an (x,y) pixel.
	*
	*  The method should perform any necessary bounds checking.
	*
	*  \param x is the (zero-based) horizontal index of the pixel to set.
	*  \param y is the (zero-based) vertical index of the pixel to set.
	*  \param value is the new color for the (x,y) pixel.
	*/
	void Image::setPixel(unsigned int x, unsigned int y, Vec3<float> & value) {
		int std_x = Array<Vec3<float>>::getWidth();
		int std_h = Array<Vec3<float>>::getHeight();
		if ((x < std_x) && (y < std_h)) Array::operator () (x, y) = value;
	}

	/*! Copies the image data from an external raw buffer to the internal image buffer.
	*
	*  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the
	*  Image object and that the data buffer has been alreeady allocated. If the image buffer is not allocated or the
	*  width or height of the image are 0, the method should exit immediately.
	*
	*  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Image object.
	*/
	void Image::setData(const Vec3<float> * & data_ptr) {
		if ((buffer != nullptr) && (data_ptr  != nullptr)) {
			for (size_t i = 0; i < width * height; i++) {
				Array::buffer[i] = data_ptr[i];
			}
		}
	}

	/*! Changes the internal image data storage size.
	*
	* If the one or both of the given dimensions are smaller, the image should be clipped
	* by discarding the remaining pixels in the rows and/or columns outside the margins.
	* If the new dimensions are larger, pad the old pixels with zero values (black color).
	* If the image is not yet allocated (zero width and height), allocate the internal buffer and
	* set the image size according to the given dimensions.
	*
	* \param new_width is the user-provided width to resize the image storage to.
	* \param new_height is the user-provided height to resize the image storage to.
	*/
	void Image::resize(unsigned int new_width, unsigned int new_height) {
		Array::resize(new_width, new_height);
	}

	/*! Reads the contents of an object from the specified file.
	*
	*  The operator can be used for the implementation of "de-serialization".
	*
	*  \param filename is the name of the file to use for loading the data.
	*
	*  \return true if the operation was successful, false otherwise.
	*/
	bool Image::operator << (std::string filename) {

		Image * temp = ReadPPM(filename.c_str());

		if (temp != nullptr){
			operator = (*temp);
			delete temp;
			return true;
		}
		else {
			return false;
		}
	}

	/*! Writes the contents of an object to the specified file.
	*
	*  The operator can be used for the implementation of "serialization".
	*
	*  \param filename is the name of the file to use for saving the data.
	*
	*  \return true if the operation was successful, false otherwise.
	*/
	bool Image::operator >> (std::string filename) {
		return WritePPM(*this, filename.c_str());
		// "this" is a pointer to image that called Image::operator >> thus (* this) gives out the image.
		// WritePPM returns true if the image save operation was successful, false otherwise.
	}

	// constructors and destructor

	/*! Default constructor.
	*
	* By default, the dimensions of the image should be zero and the buffer must be set to nullptr.
	*/
	Image::Image(): Array(0, 0) {
		buffer = nullptr;
	}

	/*! Constructor with width and height specification.
	*
	* \param width is the desired width of the new image.
	* \param height is the desired height of the new image.
	*/
	Image::Image(unsigned int width, unsigned int height) : Array(width, height) {
	}

	/*! Constructor with data initialization.
	*
	* \param width is the desired width of the new image.
	* \param height is the desired height of the new image.
	* \param data_ptr is the source of the data to copy to the internal image buffer.
	*
	* \see setData
	*/
	Image::Image(unsigned int width, unsigned int height, const Vec3<float> * data_ptr) : Array(width, height) {
		if (&data_ptr != nullptr) {
			for (size_t i = 0; i < height * width; i++) {
				Array::buffer[i] = data_ptr[i];
			}
		}
	}

	/*! Copy constructor.
	*
	* \param src is the source image to replicate in this object.
	*/
	Image::Image(const Image &src) : Array(src) {	}

	/*! Copy assignment operator.
	*
	* \param right is the source image.
	*/
	Image & Image::operator = (const Image & right) {
		Array::operator = (right);

		return *this;
	}

	/*! The Image destructor.
	*/
	Image::~Image() {
		
	}

};