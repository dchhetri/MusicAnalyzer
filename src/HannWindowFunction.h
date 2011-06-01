/*
 * HannWindowFunction.h
 *
 *  Created on: May 21, 2011
 *      Author: MacBoss
 */

#ifndef HANNWINDOWFUNCTION_H_
#define HANNWINDOWFUNCTION_H_

#include "WindowFunction.h"
#include "Utility.h"
#include <cmath>

namespace SDL_OpenGL{

	class HannWindowFunction : public WindowFunction{
	public:
		HannWindowFunction(const unsigned initSize ): WindowFunction(initSize){
			_initializeFunction();
		}
		virtual void apply(T* begin , T* end){
			const int N = end - begin;
			//grow the function to calculate more hann values if it needs to
			if( N > (int)_windowMultiplier.size()) {	_growWindowFunction(N);	}
			unsigned int i = 0;
			while( begin != end){
				*begin *= _windowMultiplier[i++];
				++begin;
			}
		}
	private:
		//used to initialize the windowing function
		 void _initializeFunction(){
			 const unsigned N = _windowMultiplier.size();
			 for(unsigned n = 0; n < N; ++n){
				 _windowMultiplier[n] = _getHannValue(n);
			 }
		 }
		 void _growWindowFunction(const int N){
			 const int lengthToGrow = N - _windowMultiplier.size();
			 const int baseN = _windowMultiplier.size();
			 if( lengthToGrow < 0) return;
			 for(int n = 0 ; n < lengthToGrow; ++n){
				 _windowMultiplier.push_back( _getHannValue( baseN + n));
			 }
		 }
		 float _getHannValue(const int n){
			 const int N = _windowMultiplier.size();
			 const float PI = SDL_OpenGL::Constants::PI;
			 const float theta = 2 * PI * n / (N - 1);
			 return 0.5f * (1 - std::cos(theta)) ;
		 }
	};

}
#endif /* HANNWINDOWFUNCTION_H_ */
