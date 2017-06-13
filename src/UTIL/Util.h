#ifndef __UTIL__H__
#define __UTIL__H__

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class OSWindowWrapper {

protected:
	bool m_bValid;
	std::string m_sAppTitle;
	int m_iWidth, m_iHeight;
public:
	OSWindowWrapper(int iAppWidth, int iAppHeight, std::string sAppTitle);
	virtual ~OSWindowWrapper();

};


class OSWindowWrapperGLFW: public OSWindowWrapper {
	GLFWwindow * m_pxWindow;
public:
	OSWindowWrapperGLFW(int iWidth, int iHeight, std::string rsAppName = "GLFW - Unnamed");
	~OSWindowWrapperGLFW();
	GLFWwindow * operator()();

	bool bOSWWCloseEventReceived();
	void vOSWWRaiseCloseEvent();
};

class OGLManager {
	OGLManager();
	static OGLManager * s_instance;
public:
	static OGLManager* init();

};
#endif /* __util__h__ */



