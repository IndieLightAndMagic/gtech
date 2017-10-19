#include <stdlib.h>
#include <time.h>


#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else 
#include <OpenGL/gl.h>
#endif /*__APPLE__*/

#include <SHDR/shdr.h>
#include <CAM/Cam.h>
#include <SDL2/SDL_joystick.h>
#include <UTIL/Util.h>
#include <MESHCOMPONENT/GMeshComponent.h>
#include <MESHCOMPONENT/GCamComponent.h>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


constexpr float degrees_to_radians(float deg){ return (deg/180.0f)*glm::pi<float>(); }

extern void getCubeData(unsigned int *, unsigned int *);
extern void drawCube(Program &shaderProgram, unsigned int vao);
extern void setCubeLocation(glm::vec3 &locationVector);
extern void setCubeRotation(glm::vec3 &rotationalAxis, float &radians);



const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 600;	
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

class MainScene{

	SDL_Window * pWindow;
	SDL_Joystick * pGameController;
	SDL_JoystickID xGameControllerID;
	Program m_shaderProgram;
	bool m_bRun{true};

	struct {
		
		unsigned int vbo,vao;
		glm::vec3 location;
		glm::vec3 axisRotation;
		float rotationMagnitude;

	}triangle;
    
    struct {
        glm::vec3 direction{glm::vec3(1.0f,0.0f,-1.0f)};
        glm::vec3 diffuseColor{glm::vec3(WHITE)};
        glm::vec3 specularColor{glm::vec3(WHITE)};
    }directionalLight;
    struct {
    	glm::vec3 diffuse{glm::vec3(NAVY)};
    	float ambientPower{1.0f};
    	float shininess{32.0f};

    }material;
    std::shared_ptr<GModelComponent> pCube;
    std::shared_ptr<GCamComponent> pCam;
    
public:

	MainScene(OSWindowWrapperSDL * pSDL)
	{
		/* The window the Scene is running in */
		pWindow = (*pSDL)();
		
		/* [1]Initialize Controller Hardware */
		initControllerHw();

	}
	~MainScene(){

	}

	void finishControllerHw(){
		if (pGameController) {
			SDL_JoystickClose(pGameController);
			std::cout << " Joystick shutdown... " << std::endl;
		}
		pGameController = 0;
		SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
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
			if (e.jbutton.which == xGameControllerID && e.type == SDL_JOYBUTTONUP){
				//std::cout << "Button: " << (unsigned int)e.jbutton.button << std::endl;
				
				if ((unsigned int)e.jbutton.button == 10 || (unsigned int)e.jbutton.button == 11){
					if (e.jbutton.button == 10){
					} else if (e.jbutton.button == 11) {
					} 
				}
			}
		}
	}
	void sceneInit(){
		
		// configure global opengl state
		// -----------------------------
		glEnable(GL_DEPTH_TEST);
        
        pCube = GAssimpLoaderComponent::loadComponentFromScene(std::string(RES_DIR)+std::string("Models/monkey.blend"),std::string("Suzanne"));
        pCam = GAssimpLoaderComponent::loadCamFromScene(std::string(RES_DIR)+std::string("Models/monkey.blend"), std::string("Camera"), glm::radians(45.0f), SCR_WIDTH, SCR_HEIGHT);
        
		std::string vertexShaderResource=RES_DIR;
        vertexShaderResource+="Shaders/smb/vrtx.shdr";
		std::string fragmentShaderResource=RES_DIR;fragmentShaderResource+="Shaders/smb/frag.shdr";
		ShaderSource * vtxshdrsource(new ShaderSource(vertexShaderResource));
		ShaderSource * frgshdrsource(new ShaderSource(fragmentShaderResource)); 
		m_shaderProgram.pushShader(vtxshdrsource, GL_VERTEX_SHADER);
		m_shaderProgram.pushShader(frgshdrsource, GL_FRAGMENT_SHADER);
		m_shaderProgram.link();
        
        
        
        // Color
        m_shaderProgram.use();
        m_shaderProgram.setVec3("viewPos", cameraPos);
        
        m_shaderProgram.setVec3("diffuseColor",material.diffuse);
        m_shaderProgram.setFloat("ambientPower",material.ambientPower);
        m_shaderProgram.setFloat("shininess",material.shininess);
        
        m_shaderProgram.setVec3("directionalLight.direction", directionalLight.direction);
        m_shaderProgram.setVec3("directionalLight.diffuse",directionalLight.diffuseColor);
        m_shaderProgram.setVec3("directionalLight.specular", directionalLight.specularColor);
        
	}
	void renderScene(){
		
		glClearColor(DARKSLATEBLUE, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        //Use specific shader
        m_shaderProgram.use();
        

        // Set Program Shader's Cam Projection & Viewport Model with m_pCam's. This should be made with Assign Program Renderer...
        //glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //m_shaderProgram.setMat4("camModel.pr", projection);
        // camera/view transformation
        //glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        //m_shaderProgram.setMat4("camModel.vw", view);
        
        //Set Specific Camera
        pCam->useCamera(m_shaderProgram);
        
        //Draw Cube
        pCube->drawComponent(m_shaderProgram);
		
		SDL_GL_SwapWindow(pWindow);
	}
	void finishScene(){
		std::cout << "Finished Scene" << std::endl;
	}
	int mainLoop(){
		sceneInit();
        //pCube = GAssimpLoaderComponent::loadComponentFromScene(std::string(RES_DIR)+std::string("Models/foxy.blend"),std::string("Cube"));
		for (;m_bRun;){
			processInput();
			renderScene();
		}
		finishScene();
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
