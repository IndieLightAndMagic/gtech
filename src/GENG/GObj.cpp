#include "g.h"

namespace GENG{
static int ids = 0;


GOb::GOb():id(GENG::ids++){
	cout <<"+ "<<typeid(this).name()<<" "<<id<<endl; 
	init();
}
GOb::~GOb(){
	cout <<"-GOb"<<endl;
}

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

