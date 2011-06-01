/*
 * ComplexArray.h
 *
 *  Created on: May 23, 2011
 *      Author: MacBoss
 *
 *      Description: 	This class enables compatibility between stl and fftw interface for fftw_complex* arrays.
 *      				It Handles necessary clean up routine, and provides an easier interface
 */

#ifndef COMPLEXARRAY_H_
#define COMPLEXARRAY_H_

#include <fftw3.h>

namespace SDL_OpenGL{
		class ComplexArray{
			private:
			unsigned _size;
			fftw_complex * _array;
			public:
				ComplexArray();
				ComplexArray(const unsigned size);

				//rule of 3 applied, not copy-on-write semantic
				ComplexArray(const ComplexArray& a);
				ComplexArray& operator = (const ComplexArray a);
				~ComplexArray();

				//accessors/mutator operators
				fftw_complex& operator[](const unsigned i);
				const fftw_complex& operator[](const unsigned i)const;

				const bool isEmpty()const;
				const unsigned size()const;

				//can be used to be interfaced with fftw functions
				fftw_complex* getArray();
				//a more efficient swap implementation
				friend void swap(ComplexArray& lhs, ComplexArray& rhs);
			private:
				//helper functions
				fftw_complex* _createArray(const unsigned size);
				//need a specialized since fftw_complex copy isn't linear action completely
				void _fftwComplexCopy(fftw_complex* from, fftw_complex* to, const unsigned size);
		};
}
#endif /* COMPLEXARRAY_H_ */
