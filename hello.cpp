
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

static struct {
    bool r,g,b;
}active = { false, false, false};
static struct {
    float r,g,b;
}speed = { 0.01f, 0.01f, 0.01f };
static struct {
    float r,g,b;
}color = { 0.0f, 0.0f, 0.0f };


static bool dirty = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){

    if (key == GLFW_KEY_R && action == GLFW_REPEAT){
        color.r += speed.r;
        dirty = true;
        if (color.r > 1.0f) {
            color.r = 1.0f;
            speed.r *= -1;
        } else if (color.r < 0.0f) {
            color.r = 0.0f;
            speed.r *= -1;
        } 
    }
    if (key == GLFW_KEY_G && action == GLFW_REPEAT){
        color.g += speed.g;
        dirty = true;
        if (color.g > 1.0f) {
            color.g = 1.0f;
            speed.g *= -1;
        } else if (color.g < 0.0f) {
            color.g = 0.0f;
            speed.g *= -1;
        } 
    }
    if (key == GLFW_KEY_B && action == GLFW_REPEAT){
        color.b += speed.b;
        dirty = true;
        if (color.b > 1.0f) {
            color.b = 1.0f;
            speed.b *= -1;
        } else if (color.b < 0.0f) {
            color.b = 0.0f;
            speed.b *= -1;
        } 
    }
        
}


int main ()
{


	/* Initialize the glfw */
	glfwInit();


 	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    std::cout << "Press R / G / B keys!!" << std::endl;


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


    // Set Callbacks for keyboard.
    glfwSetKeyCallback(pwindow, key_callback);


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

        //When some change has been made 
        if (dirty){

            glClearColor(color.r,color.g,color.b,1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            dirty = false;

        
        }
        // Swap the screen buffers
        glfwSwapBuffers(pwindow);
    }



    /* Terminate the glfw */
    glfwTerminate();
    return 0;

}


/* OK Build & Link (TESTED ON LINUX): 
g++ -o hello hello.cpp  -Iinc -L../glew-2.0.0/lib/  -L../glfw-build/src -lGL  -lglfw3  -lGLEW -ldl -lX11 -lXrandr -lpthread -lXinerama -lXcursor
*/

