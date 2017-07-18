

#ifndef _G_H_
#define _G_H_

#include <vector>
#include <iostream>
#include <typeinfo>
#include <SDL2/SDL.h>

using namespace std;
namespace GENG
{

typedef Uint32 ui32;




class GOb {

	ui32 m_ticks;
	bool m_started;
public:
	virtual void init();
	
	void _update();
	virtual void update(ui32 ui32delta);


	

	GOb(){
		cout <<"+GOb"<<endl;
		init();
	}
	~GOb(){
		cout <<"-GOb"<<endl;
	}

};


class GTh{
	SDL_Thread * m_pxT;
	vector<GOb*> m_vO;

protected:
	void * m_pP;
	bool bTAlive;

public:
	void killThread(){
		bTAlive = false;
	}
	bool isAlive(){ return bTAlive; }
	virtual int run();
	GTh(void * param);
	~GTh();
	void pushObject(GOb*);
};





}



#endif