/*
 * MusicAnalyzer.h
 *
 *  Created on: May 19, 2011
 *      Author: MacBoss
 *      Description: Analyzes sample chunk of music via FFT and maps it into amplitude spectrum
 */

#ifndef MUSICANALYZER_H_
#define MUSICANALYZER_H_

#include <vector>
#include <complex>
#include <fftw3.h>
#include <boost/shared_ptr.hpp>
#include "WindowFunction.h"
#include "ComplexArray.h"

namespace SDL_OpenGL{
	class MusicAnalyzer{
	private:

	private:
		typedef double Type;
		typedef boost::shared_ptr<WindowFunction> WindowFuncPtr;
		typedef std::vector<Type> TimeDomainArray;
	private:
		WindowFuncPtr _windowFunc;
		fftw_plan _fftwPlan;
		TimeDomainArray _currentSample;
		ComplexArray _frequencyDomainData;
	public:
		~MusicAnalyzer();
		MusicAnalyzer();
		MusicAnalyzer(WindowFunction*);
		void setWindowingFunction(const WindowFuncPtr& w);
		//transforms given sample via FFT and various other procedures
		void transform(const void* sampleChunk,const int length);
		//Note: analyzeSample should be called to retrieve new calculated data
		const ComplexArray& getFFTCalculatedData()const;
	private:
		//applies windowing functions then applies FFT
		void _applyFFT();
	};

}
#endif /* MUSICANALYZER_H_ */
