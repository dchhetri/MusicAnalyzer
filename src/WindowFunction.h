/*
 * WindowFunction.h
 *
 *  Created on: May 20, 2011
 *      Author: MacBoss
 *
 *     Description: Used regularly to reduce noise in a signal by applying a type of Window Function
 */

#ifndef WINDOWFUNCTION_H_
#define WINDOWFUNCTION_H_

#include <vector>

namespace SDL_OpenGL{

	class WindowFunction{
	public:
		typedef double T;
	protected:
		std::vector<T> _windowMultiplier;
	public:
		WindowFunction(const unsigned initSize){
			_windowMultiplier.resize(initSize);
		}
		virtual void apply(T* begin , T* end) = 0;
	};
}
#endif /* WINDOWFUNCTION_H_ */
