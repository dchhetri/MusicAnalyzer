/*
 * Window.h
 *
 *  Created on: May 8, 2011
 *      Author: MacBoss
 */

#ifndef BASE_WINDOW_H_
#define BASE_WINDOW_H_

#include "SDL.h"
#include <string>
using std::string;

namespace SDL_OpenGL{


	class BaseWindow{
	public:
		typedef unsigned int uInt;
	private:
		string _title;
		uInt _width;
		uInt _height;
		uInt _flags;
		SDL_Surface* _canvas;

	public:
		BaseWindow();
		BaseWindow(const string& title, const uInt width, const uInt height,const uInt flags);

		const string& title()const;
		const uInt width()const;
		const uInt height()const;
		const uInt flags()const;
		const SDL_Surface& canvas()const;

		void setCanvas(SDL_Surface* c);
		void setFlags(const uInt flags);
		void setWidth(const uInt w);
		void setHeight(const uInt h);

		bool run();
		//creates and initializes the window
		virtual void createContext();
		virtual void gameLoop() = 0;
		virtual bool setupContext()const = 0;
		virtual bool cleanupContext()const = 0;
	};
}
#endif /* BASE_WINDOW_H_ */
