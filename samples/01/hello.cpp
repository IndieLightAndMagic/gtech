
#include <vector>
#include <iostream>
#include <UTIL/Util.h>
#include <GL/glew.h>

//WindowSize public struct 
#define SCR_WIDTH 1200
#define SCR_HEIGHT 675


/*
 
 
 MAIN APP must be thinked of as a main thread class. Render and Input should
 take place here (SDL2 spirit).
 
 The Approach taken here is MainApp. This is a Scene. Inside a Scene
 This MainApp class MUST HAVE:
 
 1. ProcessInput method: In this method the mechanisms for processing input and
    affecting external variables.
 
    Next iteration: Is important to create a PURE VIRTUAL class to do this. This
    will favor a protocol on how to do this. Any derived classes MUST BE final.
    This means that Base class will be an interface and derived classes will be
    implementations for each scene.
 
    To affect external variables or states, callbacks to other objects must be
    defined. This mechanism is simple and effective.
 
 2. Render method: In this method all the objects must be processed and displayed
    if changes in their visual state changes.
 

 TODO:
 
 + Take sample 08 and implement it using SDL2 and the approach described here.
 
 
 PLANNED YET FAR FROM THIS POINT:
 
 + Object Signal Connection Idiom.
 + Threaded Logic for Game Objects.
 + Blender3D powered Editor.
 + Node 2 Shader Editor.
 + FX Samples Channel. 
 + Engine Making Channel. 
 + C/C++ for graphics development Teaching Channel.
 
 */




class MainApp{
	OSWindowWrapperSDL * m_ww;
	struct {
		float r,g,b;
	}speed;
	struct {
		float r,g,b;
	}color;


public:
	bool dirty        = true;
	bool killmainloop = false;
	
	MainApp():
		m_ww(0x0),
		speed({ 0.01f, 0.01f, 0.01f }),
		color({ 0.00f, 0.00f, 0.00f }),
		dirty(true),
		killmainloop(false){}
	

	void ProcessInput(){
		static bool ok = false;
		/* Process here the Input */
		SDL_Event e;
		if (SDL_PollEvent(&e) != 0){
			
			if (ok == false) {
				std::cout<< "OK" << std::endl;
			}
			switch(e.type)
			{
				case SDL_KEYDOWN:
					ProcessKey(e);
					break;
				case SDL_QUIT:
					killmainloop = true;
					break;
			}
		}
	}

	void ProcessKey(SDL_Event&e){

		if (e.key.keysym.scancode == SDL_SCANCODE_R && e.key.repeat){
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
		if (e.key.keysym.scancode == SDL_SCANCODE_G && e.key.repeat){
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
		if (e.key.keysym.scancode == SDL_SCANCODE_B && e.key.repeat){
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
		if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
			killmainloop = true;
		}
	}
	void Render(){
		if (dirty){
			glClearColor(color.r,color.g,color.b,1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			dirty = false;
			m_ww->vOSWWSwap();
		}

	}
	int MainLoop(){

		std::unique_ptr<OSWindowWrapperSDL> _SDL_(new OSWindowWrapperSDL(SCR_WIDTH, SCR_HEIGHT));
		m_ww = _SDL_.get();
		std::cout << "Starting SDL context, OpenGL 3.3" << std::endl;
		std::cout << "Press R / G / B keys!!" << std::endl;
		
		// Game loop: Here's he window 
		for (;true;)
		{
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			// Process input.
			ProcessInput();
			Render();
			// Swap the screen buffers
			if (killmainloop) break;
		}
		return 0;
	}

};
int main ()
{

	MainApp ma;
	return ma.MainLoop();

}


