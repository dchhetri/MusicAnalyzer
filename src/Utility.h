/*
 * Utility.h
 *
 *  Created on: May 17, 2011
 *      Author: MacBoss
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <functional>
#include <iostream>
#include <vector>
#include <cmath>

using std::vector;
using std::cout;
using std::endl;

namespace SDL_OpenGL{

	//holds all constants used
	namespace Constants{
		const float PI = 3.14159265f;
		const float TWO_PI = 6.28318531f;
		const float DEG_TO_RAD = 0.0174532925f;
		const float RAD_TO_DEGREE = 57.2957795f;
	}


	template<int MIN, int MAX>
	struct RandRange{
		int operator()(){ return rand() % (MAX-MIN) + MIN; }
	};
	template<typename Itr>
	void print(Itr begin, Itr end, const std::string& delim = " "){
		cout << "[ ";
		while(begin != end){ cout << *begin << delim; ++begin; }
		cout << "]";
	}

	template<typename ReturnType, typename InputValue>
	ReturnType clampValue(	const InputValue& value, const InputValue& minRange,
							const InputValue& maxRange,const ReturnType& clampValue){
		return  (minRange <= value && value <= maxRange) ? clampValue : value;
	}
	template<typename InputType>
	struct ClampZero : std::binary_function<int,InputType,float>{
		int operator()(const InputType& val, const float precision = 0.001f)const{
			return clampValue(val,-precision,precision,0);
		}
	};
	template<typename InputType>
	struct Round: std::unary_function<int,InputType>{
		int operator()(const InputType& val)const {
			return int( val + 0.5);
		}
	};

	template<typename R, typename T>
	inline R to16BitLSB(const T& d1, const T& d2){
		return  (  (( d2 << 8 ) & 0xff00) | d1 );
	}
	template<typename R, typename T>
	inline R to16BitMSB(const T& d1, const T& d2){
		return  to16BitLSB(d2,d1);
	}

	template<typename T>
	inline T magnitude(const T& d1, const T& d2){
		return std::sqrt( d1 * d1 + d2 * d2);
	}
}
#endif /* UTILITY_H_ */
