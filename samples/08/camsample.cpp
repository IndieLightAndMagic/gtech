#include <stdlib.h>
#include <time.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>
#include <SHDR/shdr.h>
#include <UTIL/Util.h>
#include <TXTR/Txtr.h>
#include <CAM/Cam.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 800;
const float MAX_FOV = 75.0f;
bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  SCR_WIDTH / 2.0;
float lastY =  SCR_HEIGHT / 2.0;
float fov   =  MAX_FOV;
float fAspectRatio = (float)SCR_WIDTH / (float)SCR_HEIGHT;
float fNearz = 0.1f;
float fFarz = 100.0f;
bool bProjectionDirty = false;
bool bCamViewDirty = false;
bool bCamMouseDirty = false;
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

/*
 * In this example we are going to implement the MainScene class with a more sophisticated example.
 * 
 * What we are going to do:
 * 
 * 	1. We will implement the MainScene class which is an object representing the Scene. 
 * 	2. MainScene class is a main thread class. It will process the input, calculate the scene each frame and render the
 * 		scene.
 *	3. We will make an object class called camera. Camera is an object with logic. The logic of it will go on a thread.
 *		Things that go on a thread are LOGIC things aside or different from Render and Input Process. 
 *	4. Syntax style: we'll use Qt Syntax Style. 
 *	5. We will implement a simple random ID generator.  
 */ 

class Camera {
	// camera
	glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
public:
	Camera():
		GOb(),
		cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)),
		cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
		cameraUp(glm::vec3(0.0f, 1.0f, 0.0f))
		{

		}
};

class MainScene : public GOb{

	/*!
	 * \brief Windows Wrapper SDL. 
	 * 
	 */
	OSWindowWrapperSDL * m_xWW;
	
	/*!
	 * \brief First Pass flag.
	 */
	bool m_bFP;

	/**
	 * \brief Shader Program to render the cubes
	 */
	// build and compile our shader zprogram
	// ------------------------------------
	Program m_shaderProgram;


	

public:
	MainScene():
		GOb(),
		m_xWW(0x0),
		m_bFP(true)
		{
		}
	void processInput(){
	}
	void sceneInit(){
		std::unique_ptr<OSWindowWrapperSDL>_SDL_(new OSWindowWrapperSDL(SCR_WIDTH, SCR_HEIGHT));
		m_xWW = _SDL_.get();

		// configure global opengl state
		// -----------------------------
		glEnable(GL_DEPTH_TEST);

		m_shaderProgram.pushShader("vs.vs", GL_VERTEX_SHADER);
		m_shaderProgram.pushShader("fs.fs", GL_FRAGMENT_SHADER);
		m_shaderProgram.link();

	}
	void renderScene(){
	}
	int mainLoop(){
		for (;true;){
			renderScene();
		}
	}
}
int main(int argc, char ** argv)
{
	

	//GLuint m_shaderProgramId = m_shaderProgram();

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	//70
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,	//32
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	//13
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	//13
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	//51
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	//70

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	//60
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	//22
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,	//03
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,	//03
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,	//41
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	//60

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	//42
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	//53
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	//71
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	//71
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	//60
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	//42

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	//02
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	//13
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	//31
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	//31
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	//20
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	//02

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	//71
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,	//33
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	//22
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	//22
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	//60
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	//71

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	//51
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	//13
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	//02
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	//02
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,	//40
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0		//51	
	
	};
	// world space positions of our cubes
	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f,  2.0f, -2.5f),
		glm::vec3( 1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture 1
	// ---------
	Txtr texture0(argv[1]);
	Txtr texture1(argv[2]); 

	
	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	m_shaderProgram.use();
	m_shaderProgram.setInt("texture1",0);
	m_shaderProgram.setInt("texture2",1);
	
	Cam cam(
		cameraPos,
		cameraFront,
		cameraUp,
		fov,
		fAspectRatio,
		fNearz,
		fFarz
		);


	// pass projection matrix to shader (note that in this case it could change every frame)
	bCamMouseDirty = bCamViewDirty = bProjectionDirty = true;
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

		// bind textures on corresponding texture units
		texture0.txtrSelect(GL_TEXTURE0);
		texture1.txtrSelect(GL_TEXTURE1);
		
		// activate shader
		m_shaderProgram.use();

		// Update Items that can "change"
		// camera/view transformation
		if (bCamViewDirty){
			cam.vSetPosition(cameraPos);
		}
		if (bCamMouseDirty){
			cam.vSetFront(cameraFront);
		}
		if (bProjectionDirty){
			cam.vSetFov(fov);
		}

		
		if (bCamMouseDirty||bCamViewDirty||bProjectionDirty){
			
			cam.vUpdateCamera();
			if (bProjectionDirty) m_shaderProgram.setMat4("camModel.pr", cam.xGetProjection());
			if (bCamViewDirty||bCamMouseDirty) m_shaderProgram.setMat4("camModel.vw", cam.xGetView());
			bCamMouseDirty = bCamViewDirty = bProjectionDirty = false;
		
		}


		
		
		// render boxes
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model_tx;
			glm::mat4 model_rt;

			/* Create a translation matrix */
			model_tx = glm::translate(model_tx, cubePositions[i]);
			

			/* Create a rotation matrix */
			float angle = 20.0f * i;
			model_rt = glm::rotate(model_rt, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			
			m_shaderProgram.setMat4("objModel.tx", model_tx);
			m_shaderProgram.setMat4("objModel.rt", model_rt);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

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

	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		cameraPos += cameraSpeed * cameraFront;
		bCamViewDirty = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		cameraPos -= cameraSpeed * cameraFront;
		bCamViewDirty = true;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		bCamViewDirty = true;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		bCamViewDirty = true;
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		
		lastX = xpos; 
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
	bCamMouseDirty = true;  
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= MAX_FOV){
		fov -= yoffset;
		bProjectionDirty = true;
	}
	if (fov <= 1.0f){
		fov = 1.0f;
	}
	if (fov >= MAX_FOV){
		fov = MAX_FOV;
	}
}