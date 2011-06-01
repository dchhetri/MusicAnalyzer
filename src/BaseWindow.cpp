/*
 * BaseWindow.cpp
 *
 *  Created on: May 8, 2011
 *      Author: MacBoss
 */

#include "BaseWindow.h"
#include "SDL.h"

namespace SDL_OpenGL{

	BaseWindow::BaseWindow()
	:  _title("Window"), _width(640), _height(400), _flags(SDL_SWSURFACE)
	{
	}
	BaseWindow::BaseWindow(const string& title, const uInt width, const uInt height,const uInt flags)
	:  _title(title), _width(width), _height(height), _flags(flags)
	{}

	bool BaseWindow::run(){
		if(!setupContext()) return false;
		gameLoop();
		if(!cleanupContext()) return false;
		return true;
	}
	//accessors
	const BaseWindow::uInt BaseWindow::width()const{
		return _width;
	}
	const BaseWindow::uInt BaseWindow::height()const{
		return _height;
	}
	const BaseWindow::uInt BaseWindow::flags()const{
		return _flags;
	}
	const SDL_Surface& BaseWindow::canvas()const{
		return *_canvas;
	}
	//mutators
	void BaseWindow::setCanvas(SDL_Surface * s){
		_canvas = s;
	}
	void BaseWindow::setWidth(const BaseWindow::uInt w){
		_width = w;
	}
	void BaseWindow::setHeight(const BaseWindow::uInt h){
		_height = h;
	}
	void BaseWindow::setFlags(const BaseWindow::uInt flags){
		_flags = flags;
	}
	void BaseWindow::createContext(){
		//init sdl components
		SDL_Init( SDL_INIT_EVERYTHING);
		//set title
		SDL_WM_SetCaption(_title.c_str(), 0);
		//create window
		_canvas = SDL_SetVideoMode( _width, _height , 32 , _flags );
	}

}
