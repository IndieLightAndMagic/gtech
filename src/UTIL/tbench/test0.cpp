#include <memory>
#include <UTIL/Util.h>
int main (void){

	std::unique_ptr<OSWindowWrapperGLFW> ww(new OSWindowWrapperGLFW(800,600,"UtilLibTestBench"));
	OGLManager::init();
	{
		GLFWwindow * pxWindow = ww->operator()();
		while (!glfwWindowShouldClose(pxWindow))
		{
			// render
			// ------
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(pxWindow);
			glfwPollEvents();
		}
	}
	OGLManager::reset();
	return 0;

}