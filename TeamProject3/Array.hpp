//------------------------------------------------------------
//
// C++ course assignment code 
//
// Prof.:  G. Papaioannou, 2016
// Authors: G. Moschovis (3150113), S. Markopoulos (3150098)
//
//

#ifndef _ARRAY_IMPLEMENTATION_
#define _ARRAY_IMPLEMENTATION_

namespace math
{
	/*! Obtains a constant pointer to the internal data.
	*
	*  This is NOT a copy of the internal array data, but rather a pointer
	*  to the internally allocated space.
	*/
	template <typename T>
	void * const Array<T>::getRawDataPtr() {
		return buffer;
	}

	/*! Returns a reference to the element at the zero-based position (column x, row y).
	*
	* \param x is the zero-based column index of the array.
	* \param y is the zero-based row index of the array.
	*
	* \return a reference to the element at position (x,y)
	*/
	template <typename T>
	T & Array<T>::operator () (int x, int y) {

		if ((x < width) && (y < height)){ T & value = buffer[y * width + x]; return value; }
		else { T & value = buffer[0]; return value; }
	}

	/*! Returns a constant reference to the element at the zero-based position (column x, row y).
	*
	* \param x is the zero-based column index of the array.
	* \param y is the zero-based row index of the array.
	*
	* \return a reference to the element at position (x,y)
	*/
	template <typename T>
	const T & Array<T>::operator () (int x, int y) const {
		
		if ((x < width) && (y < height)){ T & value = buffer[y * width + x]; return value; }
		else { T & value = buffer[0]; return value; }
	}

	/*! Constructor with array size.
	*
	* No default constructor is provided as it makes no sense.
	*
	* \param w is the width (columns) of the array
	* \param h is the height (rows) of the array
	*/
	template <typename T>
	Array<T>::Array(unsigned int w, unsigned int h) {
		this->width = w;
		this->height = h;
		buffer = new T[width * height];
	}

	/*! Copy constructor.
	*
	* No default constructor is provided as it makes no sense.
	*
	* \param source is the array to replicate.
	*/
	template <typename T>
	Array<T>::Array<T>(const Array<T> & source) {
		this->width = source.width;
		this->height = source.height;
		this->buffer = new T[width*height];
		if ((source.buffer != nullptr) && (buffer != nullptr)) {
			for (size_t i = 0; i < width * height; i++) {
				buffer[i] = source.buffer[i];
			}
		}
	}

	/*! Copy assignment operator
	*
	* \param source is the array to replicate.
	*/
	template <typename T>
	Array<T> & Array<T>::operator = (const Array<T> & source) {
		if (this != &source) { //avoidance of auto-anathesis
			this->width = source.width;
			this->height = source.height;
			delete[] buffer;
			buffer = new T[width * height];
			if ((source.buffer != nullptr) && (buffer != nullptr)) {
				for (size_t i = 0; i < width * height; i++) {
					buffer[i] = source.buffer[i];
				}
			}

		}
		return *this;
	}

	/*! Equality operator.
	*
	*  \param right is the array to compare the current object to.
	*
	*  \return true if the current array and the source have the same dimensions AND
	*  one by one their elements of type T are the same.
	*/
	template <typename T>
	bool Array<T>::operator == (const Array<T> & right) const {
		bool flag = true;
		if (this != &right) {
			if ((width != right.width) || (height == right.height)) flag = false;
			if ((right.buffer != nullptr) && (buffer != nullptr)) {
				size_t i = 0;
				while ((i < width * height) && (flag == true)) {
					if (buffer[i] != right.buffer[i]) flag = false;
					i++;
				}
			}

		}
		return flag;
	}

	/*! Changes the internal array data storage size.
	*
	* If the one or both of the given dimensions are smaller, the array should be clipped
	* by discarding the remaining elements in the rows and/or columns outside the margins.
	* If the new dimensions are larger, pad the old elements with default values of type T.
	* If the array is not yet allocated (zero width and height), allocate the internal buffer and
	* set the array size according to the given dimensions.
	*
	* \param new_width is the user-provided width to resize the array to.
	* \param new_height is the user-provided height to resize the array to.
	*/
	template <typename T>
	void Array<T>::resize(unsigned int new_width, unsigned int new_height) {
		if ((new_width != width) || (new_height != width)) {
			T * new_buffer = new T[new_width * new_height];
			size_t h = 0, w = 0;

			while (h < new_height) {

				w = 0;
				while (w < new_width) {

					if (h < height && w < width) {
						new_buffer[w + h*new_width] = buffer[w + h*width];
					}
					else {
						new_buffer[w + h*new_width] = 0; // default value
					}

					w++;
				} //end while(w < new_width)

				h++;
			} //end while(h < new_height)
			delete[] buffer;
			buffer = new_buffer;
			this->width = new_width;
			this->height = new_height;
		}
	}

	/*! Virtual destructor.
	*/
	template <typename T>
	Array<T>::~Array() {
		delete[] buffer;
	}

} // namespace math

#endif