/*
 * OpenGLWindow.h
 *
 *  Created on: May 8, 2011
 *      Author: MacBoss
 */

#ifndef OPENGLWINDOW_H_
#define OPENGLWINDOW_H_

#include "BaseWindow.h"
#include <string>
using std::string;

namespace SDL_OpenGL{


	class OpenGLWindow : public BaseWindow{
	public:
		typedef BaseWindow::uInt uInt;
		typedef bool (*FuncPtr)();
		typedef bool (*EventHandler)(const SDL_Event& event);
		typedef bool (*ResizeFunc)(const uInt width, const uInt height);
	private:
		FuncPtr _initFunc;
		FuncPtr _cleanupFunc;
		FuncPtr _renderFunc;
		EventHandler _eventHandler;
		ResizeFunc	_resizeFunc;
	public:
		OpenGLWindow();
		OpenGLWindow(const std::string& title,const uInt width, const uInt height , const uInt flags);
		void setSetupFunc(const FuncPtr& f);
		void setCleanupFunc(const FuncPtr& f);
		void setRenderFunc(const FuncPtr& f);
		void setEventHandler(const EventHandler& e);
		void setResizeHandler(const ResizeFunc& r);
		void createContext();
	private:
		bool setupContext()const;
		bool cleanupContext()const;
		void gameLoop();
	};
}

#endif /* OPENGLWINDOW_H_ */
