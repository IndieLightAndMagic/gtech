
#include <iostream>
/* First: headers: glew.h & glfw3.h */

//GLEW: The OpenGL Extension Wrangler Library
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW: A multi-platform library for OpenGL, OpenGL ES, Vulkan, window and input http://www.glfw.org/
#include <GLFW/glfw3.h>

//WindowSize public struct 
struct WinSZ {
	static GLuint width;
	static GLuint height;
};

GLuint WinSZ::width	= 800;
GLuint WinSZ::height = 600;



int main ()
{


	/* Initialize the glfw */
	glfwInit();


 	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;


	/* Window characteristics OpenGL 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /* Create a GLFWwindow object that we can use for GLFW's functions */
    GLFWwindow * pwindow = glfwCreateWindow(WinSZ::width, WinSZ::height, "LearnOpenGL",nullptr, nullptr);

    if (pwindow == nullptr)
    {
    	std::cout << "Failed to create GLFW window" << std::endl;
    	glfwTerminate();
    	return -1;
    }
    std::cout << "Window Created" << std::endl;


    // Set our window as the current OpenGL context. 
	glfwMakeContextCurrent(pwindow);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    
    // Initialize GLEW to setup the OpenGL Function pointers
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }    

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(pwindow, &width, &height);  
    glViewport(0, 0, width, height);

    // Game loop: Here's he window 
    while (!glfwWindowShouldClose(pwindow))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
        // Swap the screen buffers
        glfwSwapBuffers(pwindow);
    }



    /* Terminate the glfw */
    glfwTerminate();
    return 0;

}


/* OK Build & Link: 
g++ -o hello hello.cpp  -Iinc -L../glew-2.0.0/lib/  -L../glfw-build/src -lGL  -lglfw3  -lGLEW -ldl -lX11 -lXrandr -lpthread -lXinerama -lXcursor
*/

