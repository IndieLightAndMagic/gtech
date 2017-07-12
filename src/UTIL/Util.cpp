


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
OSWindowWrapperSDL::OSWindowWrapperSDL (int iWidth, int iHeight, std::string rsAppName):
	OSWindowWrapper(iWidth,iHeight,rsAppName){
	std::cout << "[+]SDL -- Wrapper" << std::endl;
	
	if (SDL_Init(SDL_INIT_VIDEO)<0) {
		std::cout << "SDL -- Wrapper: Failed." << std::endl;
		m_bValid = false;
		return;
	};
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	//SDL_GL_SetAttribute(SDL_RESIZABLE, GL_FALSE);
	
	m_pxWindow = SDL_CreateWindow(
		m_sAppTitle.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		iWidth,
		iHeight,
		SDL_WINDOW_OPENGL);

	if (m_pxWindow){
		std::cout << "SDL -- Wrapper: Cool." << std::endl;
		m_bValid = true;
		m_xContext = SDL_GL_CreateContext(m_pxWindow);

	} else {
		std::cout << "SDL -- Wrapper: Failed." << std::endl;
		m_bValid = false;

	}
}
OSWindowWrapperSDL::~OSWindowWrapperSDL () {
	std::cout << "[-]SDL -- Wrapper: Destroyed" << std::endl;
	
	// Destroy Context
	SDL_GL_DeleteContext(m_xContext);

	// If window then:
	if (m_pxWindow) SDL_DestroyWindow(m_pxWindow);
	
	// Terminate
	SDL_Quit();
	std::cout << "SDL -- Terminated" << std::endl;
}
SDL_Window *OSWindowWrapperSDL::operator()(){
	return m_pxWindow;
}


OGLManager::OGLManager(){}
OGLManager::~OGLManager(){
	std::cout << "OGLManager::Reseted (-)"<<std::endl;
}
OGLManager * OGLManager::init(){

	if (!s_instance){
		s_instance = new OGLManager;
		if (s_instance){
			// Initialize SDL setup the OpenGL Function pointers
			if (SDL_FALSE)
			{
				std::cout << "Failed to initialize SDL/GL" << std::endl;
				delete s_instance;
			} else {
				std::cout << "Success initialized SDL/GL cool (+)" << std::endl;
				std::cout << "OGLManager::OGLInit (+)" << std::endl;
			}
		} else {
			std::cout << "Failed OGL Singleton (+)" << std::endl;
		}
	}
	return s_instance;
}
void OGLManager::reset(){
	if (s_instance) delete s_instance;
}
OGLManager * OGLManager::s_instance = 0;
