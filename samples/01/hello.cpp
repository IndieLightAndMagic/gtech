
#include <vector>
#include <iostream>
#include <GENG/g.h>
#include <UTIL/Util.h> 
/* First: headers: glew.h & glfw3.h */

//GLEW: The OpenGL Extension Wrangler Library
/*#define GLEW_STATIC*/
#include <GL/glew.h>

//GLFW: A multi-platform library for OpenGL, OpenGL ES, Vulkan, window and input http://www.glfw.org/
//#include <GLFW/glfw3.h>

//WindowSize public struct 
#define SCR_WIDTH 1200
#define SCR_HEIGHT 675
/*static struct {
    bool r,g,b;
}active = { false, false, false};*/
static struct {
    float r,g,b;
}speed = { 0.01f, 0.01f, 0.01f };
static struct {
    float r,g,b;
}color = { 0.0f, 0.0f, 0.0f };


static bool dirty        = true;
static bool killmainloop = false;
void key_callback(int key, int repeat){

    if (key == SDLK_r && repeat){
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
    if (key == SDLK_g && repeat){
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
    if (key == SDLK_b && repeat){
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
    if (key == SDLK_ESCAPE){
        killmainloop = true;
    }
}
using namespace GENG;
class GObInputProcess:public GOb {

    /* Initialize keys to track */
    std::vector<char> m_vKeysToTrack;
    
    void init(){
        GOb::init();
        std::vector<char>v {SDLK_r, SDLK_g, SDLK_b, 0x0};
        m_vKeysToTrack = v;
    }

    /* This will be called by the thread */
    void update(ui32 ui32delta){
        /* Process here the Input */
        SDL_Event e;
        while (SDL_PollEvent(&e)!=0){
            if (e.type == SDL_QUIT){
                killmainloop = true;
                if (e.type != SDL_KEYDOWN) continue; //You Can Push it... however this is not optimal, optimization is not needed now. 
                
                for (
                    int index=0;
                    (e.type==SDL_KEYDOWN) && m_vKeysToTrack[index];
                    ++index
                    ) if (e.key.keysym.scancode == m_vKeysToTrack[index]) key_callback(e.key.keysym.scancode, e.key.repeat);   
            }
        }
    }
};

int main ()
{


	std::unique_ptr<OSWindowWrapperSDL> _SDL_(new OSWindowWrapperSDL(SCR_WIDTH, SCR_HEIGHT));

 	std::cout << "Starting SDL context, OpenGL 3.3" << std::endl;
    std::cout << "Press R / G / B keys!!" << std::endl;

    // Create A Thread for Objects that process Input (TI).
    GTh xInputThread(GNULL);


    // Create An Object which processes the input events (OI).
    GObInputProcess xInputProcess;

    // Add OI as a worker into TI.
    xInputThread.pushObject(&xInputProcess);    


    // Game loop: Here's he window 
    for (;true;_SDL_->vOSWWSwap())
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        // Process input.

        //When some change has been made 
        if (dirty){

            glClearColor(color.r,color.g,color.b,1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            dirty = false;
        
        }

        // Swap the screen buffers
        if (killmainloop) break;
    }



    return 0;

    /* _SDL_ will peacefully terminate */

}


