#ifndef __UTIL__H__
#define __UTIL__H__

#include <iostream>
#include <string>

//#include <GL/glew.h>
#include <SDL2/SDL.h>

class OSWindowWrapper {

protected:
	bool m_bValid;
	std::string m_sAppTitle;
	int m_iWidth, m_iHeight;
public:
	OSWindowWrapper(int iAppWidth, int iAppHeight, std::string sAppTitle);
	virtual ~OSWindowWrapper();

};


class OSWindowWrapperSDL: public OSWindowWrapper {
	SDL_Window * m_pxWindow;
	SDL_GLContext m_xContext;
public:
	OSWindowWrapperSDL(int iWidth, int iHeight, std::string rsAppName = "Unnamed");
	~OSWindowWrapperSDL();
	SDL_Window * operator()();

	bool bOSWWCloseEventReceived();
	void vOSWWRaiseCloseEvent();
};

class OGLManager {
	OGLManager();
	~OGLManager();
	static OGLManager * s_instance;
public:
	static OGLManager* init();
	static void reset();


};
#endif /* __util__h__ */



