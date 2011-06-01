/*
 * MusicAnalyzer.cpp
 *
 *  Created on: May 20, 2011
 *      Author: MacBoss
 */

#include "MusicAnalyzer.h"
#include "Utility.h"
#include "ComplexArray.h"

#include <fftw3.h>

namespace SDL_OpenGL{

	MusicAnalyzer::MusicAnalyzer(): _fftwPlan(NULL){
	}
	MusicAnalyzer::MusicAnalyzer(WindowFunction* windowFunction)
	: _windowFunc(windowFunction), _fftwPlan(NULL){
	}
	MusicAnalyzer::~MusicAnalyzer(){
 		fftw_destroy_plan(_fftwPlan);
 	}
	const ComplexArray& MusicAnalyzer::getFFTCalculatedData()const{
		return _frequencyDomainData;
	}
	void MusicAnalyzer::setWindowingFunction(const MusicAnalyzer::WindowFuncPtr& w){
		_windowFunc = w;
	}
	void MusicAnalyzer::transform(const void *sample,const int length){
		const char * sampleChunk =  reinterpret_cast<const char *>(sample);
		_currentSample = TimeDomainArray(length);
		const double scaleFactor = 32768;
		for(int i = 0; i < length; i += 4){
			//sum the channels for now
			double leftChannel = to16BitLSB<double>(sampleChunk[i],sampleChunk[i+1]);
			double rightChannel = to16BitLSB<double>(sampleChunk[i+2],sampleChunk[i+3]);
			double scaledSum = (leftChannel + rightChannel)/(scaleFactor);
			//std::cout << i << " : " << sum << endl;
			_currentSample[i] = scaledSum;
		}
		//apply fft on current sample data
		_applyFFT();
	}
	/* private helper function */
 	void MusicAnalyzer::_applyFFT(){
		//apply windowing function
		_windowFunc->apply(&_currentSample[0] ,&_currentSample[_currentSample.size()]);
		//applying 1D real input outputs N/2 + 1, according to the fftw3.2.2 documentation
		const int OUTPUT_SIZE = _currentSample.size()/2 + 1;
		//setup output data if not created already
		if(_frequencyDomainData.isEmpty()) _frequencyDomainData = ComplexArray(OUTPUT_SIZE);
		//setup FFT algorithm if not setup already
		if(!_fftwPlan) _fftwPlan = fftw_plan_dft_r2c_1d(_currentSample.size(), &_currentSample[0],_frequencyDomainData.getArray(),FFTW_MEASURE);
		//check for valid setup
		if(!_fftwPlan){ std::cout << "Error: Couldn't create plan\n"; return;}
		//execute FFT
		fftw_execute(_fftwPlan);

	}

}
