
#include "OpenGLWindow.h"
#include "SDL_opengl.h"
#include "SDL_mixer.h"
#include "Utility.h"
#include "MusicPlayer.h"
#include "MusicAnalyzer.h"
#include "HannWindowFunction.h"
#include "ComplexArray.h"

#include <cmath>
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

using namespace SDL_OpenGL;

const unsigned STEREO_CHANNEL = 2;
const unsigned MONO_CHANNEL = 1;

const unsigned DEFAULT_CHUNK_SIZE = 1024;
const unsigned CHANNEL_TO_USE = STEREO_CHANNEL;

//gloabl variable :(
MusicAnalyzer musicAnalyzer( new HannWindowFunction(DEFAULT_CHUNK_SIZE) );
MusicPlayer musicPlayer;

void drawAxis(const int xMin, const int xMax, const int yMin, const int yMax, const int tickSpace = 1, const float tickLength = 0.5f){

	//draw axis
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_LINES);
		glVertex3f(xMin,0.0f,0.0f);
		glVertex3f(xMax,0.0f,0.0f);

		glVertex3f(0.0f,yMin,0.0f);
		glVertex3f(0.0f,yMax,0.0f);
	glEnd();

	//no need to draw 0-sized tick length
	if(tickLength <= 0) return;

	const float tickSize = tickLength / 2;

	//draw x-axis tick
	const int numXOfTicks = ( (std::abs(xMax) + std::abs(xMin)) / std::max(tickSpace,1) ) + 1;
	glColor3f(1.0f,1.0f,1.0f);
	for(int i = 0; i < numXOfTicks ; ++i){
		const int offset = xMin + i * tickSpace;
		glBegin(GL_LINES);
			glVertex3f(offset,-tickSize,0.0f);
			glVertex3f(offset,tickSize,0.0f);
		glEnd();
	}
	//draw y-axis tick
	const int numYTicks = (std::abs(yMax) + std::abs(yMin)) / std::max(tickSpace,1) + 1;
	glColor3f(1.0f,1.0f,1.0f);
	for(int i = 0; i < numYTicks; ++i){
		const int offset = yMin + i * tickSpace;
		glBegin(GL_LINES);
			glVertex3f(-tickSize,offset,0.0f);
			glVertex3f(tickSize,offset,0.0f);
		glEnd();
	}
}
 bool render(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity();
	gluLookAt(0,0,10,	0,0,-5,		0,1,0);

	//draw graph axis
	const int AXIS_SIZE = 5;
	glColor3f(1.0f,1.0f,1.0f);
	drawAxis(-AXIS_SIZE,AXIS_SIZE,-AXIS_SIZE,AXIS_SIZE,1,0);

	glColor3f(1.0f,0.0f,0.0f);
	glBegin(GL_LINES);

	glEnd();


	SDL_GL_SwapBuffers();
	return true;
}
 bool handleEvent(const SDL_Event& event){
	 switch(event.type){
	 	 case SDL_KEYDOWN:
	 		 break;
	 	 case SDL_KEYUP:
				 switch(event.key.keysym.sym)
				 {
					 case SDLK_SPACE: 	musicPlayer.restart();	break;
					 default: break;
				 }
	 		 break;
	 }
	 return true;
 }

 void effectProcessFunc(int ch, void *stream, int len, void *udata){
	 //calculate transformation via FFT
	musicAnalyzer.transform(stream,len);
	const ComplexArray& c = musicAnalyzer.getFFTCalculatedData();
	for(unsigned i = 0; i < c.size(); ++i){
		const fftw_complex& f = c[i];
		cout << f[0] << " " << f[1] << " " << magnitude(f[0],f[1]) << endl;
	}
 }
 void doNothingFunc(int c, void *ud){
	 /* sample processing done */
 }
int main( int argc, char* args[] )
{
	using namespace SDL_OpenGL;

	//init audio components
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,CHANNEL_TO_USE,DEFAULT_CHUNK_SIZE)) {
	   printf("Unable to open audio!\n");
	}

	const std::string musicFileName = "a.wav";
	musicPlayer.loadMusic(musicFileName);
	musicPlayer.setChannelToPlayOn(1);
	//callback function called every time a sample of music is played
	musicPlayer.registerEffectCallback( effectProcessFunc , doNothingFunc );

	OpenGLWindow window;
	window.createContext();
	window.setRenderFunc( render );
	window.setEventHandler( handleEvent );
	window.run();


	//
	Mix_CloseAudio();

    return 0;
}
