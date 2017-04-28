

//Salida C++ por el stdout/err
#include <iostream>

//Manejador de extensiones de OpenGl
#include <GL/glew.h>

//Manejador de Ventanas
#include <GLFW/glfw3.h>




GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

static bool killmainloop = false;

void key_callback(GLFWwindow * pwindow, int key, int scancode, int action, int mode){
    if (key == GLFW_KEY_ESCAPE){
        killmainloop = true;
    }
}



static struct {
	const GLuint WIDTH = 800, HEIGHT = 600;
}screen_dim;

static struct {
	GLchar * vtx_shader_source = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";
    GLuint vtx_shader;
    GLchar * frg_source = "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
    GLuint frg_shader;
}shader;


int main (int argc, char ** argv){

	// Init GLFW
	glfwInit();

	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;	

	// Window characteristics OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow * pwindow = glfCreateWindow(screen_dim.WIDTH,screen.HEIGHT, "Triangle - 02",nullptr,nullptr);
    if (pwindow == nullptr){
    	std::cout << "Failed to create GLFW window" << std::endl;
    	glfwTerminate();
    	return -1;
    }

    //Now we have a valid window, set it as the context. 
    glfwMakeContextCurrent(pwindow);


    //Callback for the keyboard
    glfwSetKeyCallback(pwindow, key_callback);

    //Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;

    // Initialize GLEW to setup the OpenGL Function pointers
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }    
	
	// Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(pwindow, &width, &height);  
    glViewport(0, 0, width, height);

    //Compile Vertex Shader
    shader.vtx_shader = glCreateShader(GL_VERTEX_SHADER);
   	glShaderSource(shader.vtx_shader, 1, &(shader.vtx_shader_source), NULL);
   	glCompileShader(shader.vtx_shader);

   	//Check
   	GLint success;
   	glGetShaderiv( shader.vtx_shader, GL_COMPILE_STATUS, &success );
   	if (!success){
   		glGerShaderInfoLog()
   	}






}
