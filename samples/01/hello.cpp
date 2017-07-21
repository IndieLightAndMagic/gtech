
#include <vector>
#include <iostream>
#include <UTIL/Util.h>
#include <GL/glew.h>

//WindowSize public struct 
#define SCR_WIDTH 1200
#define SCR_HEIGHT 675


/* So this is a demo of what should have a principal thread in a game.
 * 
 * Objects in the thread: A main thread should have a dynamic/static list of
 * objects which are supposed to be processed. Just as a regular a thread but it
 * will be called from main. This main thread will render and will get input from
 * external devices such as keyboard, gamepad etc. 
 * 
 * Main thread should be the only one. So it could be a Singleton or a namespace
 * with a bunch of functions, or a class with static methods all over the place.
 * 
 * A main thread also could be a class / structure with a bunch of specific
 * callbacks. 
 * 
 * As this is a demo, we are going to oversimplify what we are doing. So a bunch
 * of functions will do for now... in fact, a single static function called
 * mainloop.
 * 
 * So Our MainThread class will inherit from GTh (A thread class).

	

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


