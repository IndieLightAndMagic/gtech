#include <stdlib.h>
#include <time.h>


#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else 
#include <OpenGL/gl.h>
#endif /*__APPLE__*/

#include <SDL2/SDL_joystick.h>
#include <UTIL/Util.h>
#include <PRMTV/Primitive.h>
#include <iostream>

/*
void framebuffer_size_callback(SDL_Window* window, int width, int height);
void mouse_callback(SDL_Window* window, double xpos, double ypos);
void scroll_callback(SDL_Window* window, double xoffset, double yoffset);
void processInput(SDL_Window *window);
*/
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const int JOYSTICK_DEAD_ZONE = 8000;
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
extern CubeData * pCubeArchetype;
class MainScene{

	/*!
	 * \brief Windows Wrapper SDL. 
	 * 
	 */
	SDL_Window * pWindow;
	SDL_Joystick * pGameController;
    SDL_JoystickID xGameControllerID;
    /**
	 * \brief Shader for Scene
	 */
	Program m_shaderProgram;

	/*!
	 Cubes
	 */
	CubeObj * m_cube;

	/* Running? */
	bool m_bRun;

	/* First Pass */
	bool m_bFirstPass;

public:

	MainScene(OSWindowWrapperSDL * pSDL)
	{
		/* The window the Scene is running in */
		pWindow = (*pSDL)();
		
		/* [1]Initialize Controller Hardware */
		initControllerHw();

		/* The following two flags could be better expressed with states */
		/* The Scene is now Running : Not on screen, just running.. on the RAM! */
		m_bRun = true;

		/* [2] Load on Memory the archetype */
		CubeData::CreateCubeData();

		/* First Pass Flag */
		m_bFirstPass = true;
	}
	~MainScene(){

			if (pGameController) {
				
				SDL_JoystickClose(pGameController);
				std::cout << " Joystick shutdown... " << std::endl;

			}
			pGameController = 0;
			CubeData::FinishCubeData();
	}

	void initControllerHw(){

		/* Initialize Joystick */
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
		
		int njoy = SDL_NumJoysticks();
		if (njoy<1){
            std::cout << " Warning: No Joysticks " << std::endl;
 		} else {
            std::cout << " Found " << njoy << " joysticks " << std::endl;
 			pGameController = SDL_JoystickOpen(0);
            xGameControllerID = SDL_JoystickInstanceID(pGameController);
 			if (!pGameController)
 			{
 				std::cout << " Sorry Unable to init joysticks." << std::endl;
 			} else {
 				std::cout << " Joystick Instance ID: [" << SDL_JoystickInstanceID(pGameController) << "] --  Cool." << std::endl;
 				std::cout << " Joystick name: " << SDL_JoystickName(pGameController) << std::endl;
 				std::cout << " Joystick num axis: " << SDL_JoystickNumAxes(pGameController) << std::endl;
 				std::cout << " Joystick num buttons: " << SDL_JoystickNumButtons(pGameController) << std::endl;
 				std::cout << " Joytstick num hats: " << SDL_JoystickNumHats(pGameController) << std::endl;
 			}
 		}

	}
	void processInput(){
		SDL_Event e;
		if (SDL_PollEvent(&e)==0) return;

		if ( e.type == SDL_QUIT) {
			m_bRun = false;
        } else if(e.type == SDL_KEYDOWN) {
            
            if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                m_bRun = false;
            
        } else if (e.type == SDL_JOYAXISMOTION){
            if (e.jaxis.which == xGameControllerID){
                std::cout << "Axis: " << (unsigned int)e.jaxis.axis << std::endl;
            }
        } else if (e.type == SDL_JOYBUTTONUP || e.type == SDL_JOYBUTTONDOWN){
            if (e.jbutton.which == xGameControllerID){
                std::cout << "Button: " << (unsigned int)e.jbutton.button << std::endl;
            }
        }



		

	}
	void sceneInit(){

		/* [3] Create 10 cubes */
		m_cube = new CubeObj[10];

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
		
		// configure global opengl state
		// -----------------------------
		glEnable(GL_DEPTH_TEST);

		m_shaderProgram.pushShader("vs.vs", GL_VERTEX_SHADER);
		m_shaderProgram.pushShader("fs.fs", GL_FRAGMENT_SHADER);
		m_shaderProgram.link();



		for (auto index = 0; index < 10; ++index)
		{	

			m_cube[ index ].SetPosition(cubePositions[ index ]);
			m_cube[ index ].AssignProgramRenderer(&m_shaderProgram);

		}
		

	}
	void renderScene(){

		if (m_bFirstPass){
			m_bFirstPass = false;
		}

		


	}
	void finishScene(){
		delete [] m_cube;
		std::cout << "Finished Scene" << std::endl;
	}
	int mainLoop(){
        sceneInit();
		for (;m_bRun;){
			processInput();
			renderScene();
		}
        return 0;
	}
};
int main(int argc, char ** argv)
{
	
	std::unique_ptr<OSWindowWrapperSDL>_SDL_(new OSWindowWrapperSDL(SCR_WIDTH, SCR_HEIGHT));
	MainScene scn(_SDL_.get());
	scn.mainLoop();

	return 0;
}
	/*unsigned int VBO, VAO;
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

			// Create a translation matrix 
			model_tx = glm::translate(model_tx, cubePositions[i]);
			

			// Create a rotation matrix
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
}*/
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
/*void processInput(GLFWwindow *window)
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
}*/

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	// glViewport(0, 0, width, height);
//}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
/*void mouse_callback(GLFWwindow* window, double xpos, double ypos)
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
}*/

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
/*void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
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
}*/
