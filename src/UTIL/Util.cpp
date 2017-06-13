


#include "Util.h"

OSWindowWrapper::OSWindowWrapper(int iAppWidth, int iAppHeight, std::string sAppTitle):
	m_sAppTitle(sAppTitle),
	m_iWidth(iAppWidth),
	m_iHeight(iAppHeight) {
		std::cout << "[+]OSWrapper" << std::endl;
	}
OSWindowWrapper::~OSWindowWrapper(){
		std::cout << "[-]OSWrapper" << std::endl; 
 	};

 /*This ctor must be implemented for each Helper/Toolkit/Etc you wanna to implement. Only the ctor can write the value of the m_bValid flag.*/
OSWindowWrapperGLFW::OSWindowWrapperGLFW (int iWidth, int iHeight, std::string rsAppName):
	OSWindowWrapper(iWidth,iHeight,rsAppName){
	std::cout << "[+]GLFW -- Wrapper" << std::endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	m_pxWindow = glfwCreateWindow(iWidth,iHeight,m_sAppTitle.c_str(), nullptr, nullptr); 
	if (m_pxWindow){
		std::cout << "GLFW -- Wrapper: Cool." << std::endl;
		m_bValid = true;
		glfwMakeContextCurrent(m_pxWindow);

	} else {
		std::cout << "GLFW -- Wrapper: Failed." << std::endl;
		m_bValid = false;

	}
}
OSWindowWrapperGLFW::~OSWindowWrapperGLFW () {
	std::cout << "[-]GLFW -- Wrapper: Destroyed" << std::endl;
	// If window then:
	if (m_pxWindow) glfwDestroyWindow(m_pxWindow);
	// Terminate
	glfwTerminate();
	std::cout << "GLFW -- Terminated" << std::endl;
}
GLFWwindow*OSWindowWrapperGLFW::operator()(){
	return m_pxWindow;
}


OGLManager::OGLManager(){}
OGLManager * OGLManager::init(){

	if (!s_instance){
		s_instance = new OGLManager;
		if (s_instance){
			// Initialize GLEW to setup the OpenGL Function pointers
			glewExperimental = GL_TRUE;
			if (glewInit() != GLEW_OK)
			{
				std::cout << "Failed to initialize GLEW" << std::endl;
				delete s_instance;
			} else {
				std::cout << "Success initialized GLEW cool (+)" << std::endl;
				std::cout << "OGLManager::OGLInit (+)" << std::endl;
			}
		} else {
			std::cout << "Failed OGL Singleton (+)" << std::endl;
		}
	}
	return s_instance;
}
OGLManager * OGLManager::s_instance = 0;
