

#ifndef _G_H_
#define _G_H_

#include <vector>
#include <iostream>
#include <typeinfo>
#include <SDL2/SDL.h>

using namespace std;
namespace GENG
{






class GOb {

public:
	virtual void update();
	GOb(){
		cout <<"+GOb"<<endl;
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