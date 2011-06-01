/*
 * ComplexArray.cpp
 *
 *  Created on: May 23, 2011
 *      Author: MacBoss
 */

#include "ComplexArray.h"
#include "boost/assert.hpp"
#include <algorithm>

namespace SDL_OpenGL{


/*friend*/
	void swap(ComplexArray& lhs, ComplexArray& rhs){
		std::swap( lhs._array, rhs._array);
		std::swap(lhs._size,rhs._size);
	}

	ComplexArray::ComplexArray()
	: _size(0), _array(0){}
	ComplexArray::ComplexArray(const unsigned size)
	: _size(size), _array ( _createArray(size) ){
	}
	ComplexArray::~ComplexArray(){
		fftw_free(_array);
	}
	ComplexArray::ComplexArray(const ComplexArray& a)
	: _size(a._size), _array(_createArray(a._size))
	{
		_fftwComplexCopy(a._array,_array,_size);
	}
	ComplexArray& ComplexArray::operator =(ComplexArray a){
		swap(*this,a);
		return *this;
	}
	fftw_complex& ComplexArray::operator[](const unsigned i){
		BOOST_ASSERT(i > 0 && i < size());
		return _array[i];
	}
	const fftw_complex& ComplexArray::operator[](const unsigned i)const{
		BOOST_ASSERT(i > 0 && i< size());
		return _array[i];
	}
	const unsigned ComplexArray::size()const{
		return _size;
	}
	const bool ComplexArray::isEmpty()const{
		return _size == 0;
	}

	fftw_complex* ComplexArray::getArray(){
		return _array;
	}
	/* private helper functions */

	fftw_complex* ComplexArray::_createArray(const unsigned size){
		return size > 0 ? (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size) : 0;
	}

	void ComplexArray::_fftwComplexCopy(fftw_complex* from, fftw_complex* to, const unsigned size){
		for(unsigned i = 0; i < size; ++i){
			to[i][0] = from[i][0]; //copy real part
			to[i][1] = from[i][1]; //copy imaginary part
		}
	}
}
