

#ifndef _G_H_
#define _G_H_

#include <vector>
#include <iostream>
#include <typeinfo>
#include <SDL2/SDL.h>

using namespace std;
namespace GENG
{

#define GNULL nullptr

typedef Uint32 ui32;




class GOb {
	int id;
	ui32 m_ticks;
	bool m_started;
public:
	virtual void init();
	
	void _update();
	virtual void update(ui32 ui32delta);

	GOb();
	~GOb();
	


};


class GTh{
	int id;
	SDL_Thread * m_pxT;
	vector<GOb*> m_vO;

protected:
	void * m_pP;
	bool bTAlive;

public:
	void killThread(){
		bTAlive = false;
	}
	/**
	 * @brief      Determines if alive.
	 *
	 * @return     True if alive, False otherwise.
	 */
	bool isAlive(){ return bTAlive; }
	/**
	 * @brief      This function runs the thread. As long the thread is alive it must be called. The task of run is to update all the objects in m_vO.
	 *
	 * @return     The function should return 0. Otherwise will return another value.
	 */
	virtual int run();
	GTh(void * param);
	~GTh();
	void pushObject(GOb*);
};





}



#endif