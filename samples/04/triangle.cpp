#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other includes
#include <SHDR/shdr.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource ="#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec3 aColor;\n"
	"out vec3 ourColor;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos, 1.0);\n"
	"   ourColor = aColor;\n"
	"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec3 ourColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(ourColor, 1.0f);\n"
	"}\n\0";

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);



	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Triangle with Class Shader", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	std::cout << "Window Created" << std::endl;

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	ShaderSource vtx_ss("vs.vs");
	ShaderSource frg_ss("fs.fs");
	const GLchar * vtxSource;
	const GLchar * frgSource;
	std::cout << "################################" << std::endl;
	if (vtx_ss.state() == ShaderSource::SOURCE_STATE_VALID) {
		std::cout << "Vertex Shader Source loaded [Ok]" << std::endl;
		std::cout << "Code: " << std::endl;
		vtxSource = vtx_ss();
		std::cout << vtxSource << std::endl;
		std::cout << "################################" << std::endl;
	} 
	if (frg_ss.state() == ShaderSource::SOURCE_STATE_VALID) {
		std::cout << "Fragment Shader Source loaded [Ok]" << std::endl;
		std::cout << "Code: " << std::endl;
		frgSource = frg_ss();
		std::cout << frgSource << std::endl;
		std::cout << "################################" << std::endl;
					
	} 


	// vertex shader
	
	std::cout << "################################" << std::endl;
	Shader vtx_s(&vtx_ss, GL_VERTEX_SHADER);	
	if (vtx_s.state() ==  Shader::SHADER_STATE_INVALID) {
		std::cout << "VTX SHADER INVALID" << std::endl;
	}
	if (vtx_s.state() ==  Shader::SHADER_STATE_CREATED) {
		std::cout << "VTX SHADER CREATED" << std::endl;
	}
	if (vtx_s.state() ==  Shader::SHADER_STATE_COMPILED) {
		std::cout << "VTX SHADER COMPILED " << vtx_s() << std::endl;
	}

	// fragment shader 

	std::cout << "################################" << std::endl;
	Shader frg_s(&frg_ss, GL_FRAGMENT_SHADER);	
	if (frg_s.state() ==  Shader::SHADER_STATE_INVALID) {
		std::cout << "FRG SHADER INVALID" << std::endl;
	}
	if (frg_s.state() ==  Shader::SHADER_STATE_CREATED) {
		std::cout << "FRG SHADER CREATED" << std::endl;
	}
	if (frg_s.state() ==  Shader::SHADER_STATE_COMPILED) {
		std::cout << "FRG SHADER COMPILED " << frg_s() << std::endl;
	}
	std::cout << "################################" << std::endl;

	
	int success;
	char infoLog[512];
	// link shaders
	Program p;
	p.pushShader(&vtx_s);
	p.pushShader(&frg_s);
	int shaderProgram = p();
	p.link();
	//glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (p.isLinked()==GL_FALSE) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vtx_s());
	glDeleteShader(frg_s());

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);

	// as we only have a single shader, we could also just activate our shader once beforehand if we want to 
	p.use();
	//glUseProgram(shaderProgram);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render the triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
/*
g++ -o triangle triangle.cpp  -I../inc -L../../glew-2.0.0/build/lib/  -L../../glfw/build/src/ -L../src/SHDR/buildout -framework OpenGL -framework Cocoa -framework IOKit  -framework CoreVideo -lglfw3  -lGLEW  -lpthread -lshdr
*/
