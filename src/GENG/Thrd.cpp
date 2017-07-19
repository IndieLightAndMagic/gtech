


#include "g.h"



namespace GENG{ 







GTh::GTh(void * param):
m_pP(param),
bTAlive(false)
{
	cout <<"+"<<typeid(this).name()<<endl; 

}
GTh::~GTh(){
	cout <<"-"<<typeid(this).name()<<endl;
}

int threadHelper(void * pv){
	GTh * pt = (GTh*)pv;
	while (pt->isAlive())
		pt->run(); 
	return 0;
}
int GTh::run(){

	/* Update the objects registered on this thread */
	for (int i = 0; i<m_vO.size(); i++){
		m_vO[i]->_update();
	}
	return 0;

}
void GTh::pushObject(GOb* pxO){


	for (int i = 0 ; i < m_vO.size() ; i++){
		if (m_vO[i] == pxO) return;
	}
	m_vO.push_back(pxO);
	
	if (!bTAlive){
		bTAlive = true;
		m_pxT = SDL_CreateThread(threadHelper,"GThThread",this);
		SDL_DetachThread(m_pxT);
	} 
}


};





