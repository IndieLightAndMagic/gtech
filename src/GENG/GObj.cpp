#include "g.h"

namespace GENG{

void GOb::_update(){

	ui32 ui32delta;
	if(m_started){
		m_started = true;
		ui32delta = 0;
	}else ui32delta = SDL_GetTicks() - m_ticks;
	m_ticks += ui32delta;
	update(ui32delta);

}

void GOb::update(ui32 ui32delta){

	

}
void GOb::init(){
	m_ticks = 0;
	m_started = false;
}

};

