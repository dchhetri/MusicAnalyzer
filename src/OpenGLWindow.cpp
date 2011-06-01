/*
 * OpenGLWindow.cpp
 *
 *  Created on: May 8, 2011
 *      Author: MacBoss
 */

#include "OpenGLWindow.h"
#include "SDL_opengl.h"
#include <iostream>

namespace SDL_OpenGL{
	/*** Default function for OpenGLWindow class***/
	static bool _defaultOpenGLInit();
	static bool _defaultOpenGLDestroy();
	static bool _defaultOpenGLEventHandler(const SDL_Event&);
	static bool _defaultOpenGLRenderFunc();
	static bool _defaultOpenGLResizeFunc(const OpenGLWindow::uInt,const OpenGLWindow::uInt);

	static bool _defaultOpenGLInit(){
		glShadeModel(GL_SMOOTH);						// Enable Smooth Shading
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);			// Black Background
		glClearDepth(1.0f);								// Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);						// Enables Depth Testing
		glDepthFunc(GL_LEQUAL);							// The Type Of Depth Testing To Do
		return true;
	}
	static bool _defaultOpenGLDestroy(){
		SDL_Quit();
		return true;
	}
	//returns true if the program should still be running else false
	static bool _defaultOpenGLEventHandler(const SDL_Event& event){
		return true;
	}
	static bool _defaultOpenGLRenderFunc(){
		return true;
	}
	static bool _defaultOpenGLResizeFunc(const OpenGLWindow::uInt width, const OpenGLWindow::uInt height){
		//Tell OpenGL how to convert from coordinates to pixel values
		glViewport(0, 0, width,height);
		glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
		//Set the camera perspective
		glLoadIdentity(); //Reset the camera

		//set the pyramid
		gluPerspective(	45.0,(double)width / (double)height,1.0,2000.0);

		glMatrixMode(GL_MODELVIEW);
		return true;
	}
	/*** Public Function ***/
	OpenGLWindow::OpenGLWindow()
	:BaseWindow("OpenGLWindow" ,640,400,SDL_OPENGL | SDL_RESIZABLE),
	 _initFunc(_defaultOpenGLInit),
	 _cleanupFunc( _defaultOpenGLDestroy),
	_renderFunc( _defaultOpenGLRenderFunc ),
	_eventHandler( _defaultOpenGLEventHandler ),
	_resizeFunc( _defaultOpenGLResizeFunc)
	{}

	OpenGLWindow::OpenGLWindow(const std::string& title,const uInt width, const uInt height , const uInt flags)
	:BaseWindow(title,width,height,flags),
	 _initFunc( _defaultOpenGLInit ),
	 _cleanupFunc( _defaultOpenGLDestroy ),
	 _renderFunc(_defaultOpenGLRenderFunc ),
	 _eventHandler( _defaultOpenGLEventHandler),
	 _resizeFunc( _defaultOpenGLResizeFunc)
	{}

	void OpenGLWindow::setSetupFunc(const FuncPtr& f){
		_initFunc = f;
	}
	void OpenGLWindow::setCleanupFunc(const FuncPtr& f){
		_cleanupFunc = f;
	}
	void OpenGLWindow::setRenderFunc(const FuncPtr& f){
		_renderFunc = f;
	}
	void OpenGLWindow::setEventHandler(const EventHandler& e){
		_eventHandler = e;
	}

	/**** Private function ***/
	//sets opengl default attributes and then create sdl context
	void OpenGLWindow::createContext(){
		SDL_Init( SDL_INIT_EVERYTHING);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,      8);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      16);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,     32);

		SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,  8);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);

		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

		BaseWindow::createContext();
	}
	bool OpenGLWindow::setupContext()const{
		(*_resizeFunc)(width(),height());
		return (*_initFunc)();
	}
	bool OpenGLWindow::cleanupContext()const{
		 return (*_cleanupFunc)();
	}
	void OpenGLWindow::gameLoop(){
		SDL_Event event;
		bool isRunning = true;
		//start the game loop
		while(isRunning){
			//check and handle for any events
			while(SDL_PollEvent(&event)){
				switch(event.type){
					//exit on escape key
					case SDL_KEYUP: if(event.key.keysym.sym == SDLK_ESCAPE) isRunning = false; break;
					//exit on close button pressed
					case SDL_QUIT: isRunning = false; break;
					//resize on resizing the window
					case SDL_VIDEORESIZE: 	setWidth(event.resize.w); setHeight(event.resize.h);
											setCanvas( SDL_SetVideoMode( width(), height() , 32 , flags() ) );
											(*_resizeFunc)(event.resize.w,event.resize.h); break;
				}
				//call additional event handler provided by user
				_eventHandler(event);
			}
			//render screen
			(*_renderFunc)();
		}
	}

}//end of namespace SDL_OpenGL
